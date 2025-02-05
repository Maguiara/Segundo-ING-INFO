
#include "tools.h"
#include "SafeFD.h"

int main (int argc, char* argv[]) {
 auto options = parse_args(argc, argv);
  // Analizar los errores que se puedan producir al procesar los argumentos
  if (!options.has_value()) {
    switch (options.error()){
      case ErrorCode::UNKNOWN_OPTION:
        std::cerr << "Opción desconocida\n";
        break;
      case ErrorCode::MISSING_FILE:
        std::cerr << "Falta el nombre del archivo\n";
        break;
      case ErrorCode::MISSING_ARGUMENTS:
        std::cerr << "Faltan argumentos y nombre del archivo\n";
        break;
      default:
        std::cerr << "Error desconocido\n";
        break;
    }
    std::cerr << "Use --help o -h para obtener ayuda\n";
    return EXIT_FAILURE;
  } 
  if (options.value().show_help_flag) {
    show_help();
    return EXIT_SUCCESS;
  }
  if (options.value().verbose_flag) std::cerr << "Archivo a leer: " << options.value().filename << "\n";
  std::string header;
  std::string_view body;
  std::ostringstream oss;
  std::expected<SafeMap, int> read = read_all(options.value().filename, options.value().verbose_flag);
  if (!read.has_value()) {
    switch (read.error()) {
      case EACCES:
        if (options.value().verbose_flag) std::cerr << "Permiso denegado : " << options.value().filename  << " " << strerror(read.error()) << "\n";
        header = "403 Forbidden";
        break;
      case ENOENT:
        if (options.value().verbose_flag) std::cerr << "Archivo no encontrado: " << options.value().filename  << " " << strerror(read.error()) << "\n";
        header = "404 Not Found";
        break;
      case EINVAL:
        if(options.value().verbose_flag) std::cerr << "Se intenta aceder a una zona de memorira restringida " << options.value().filename  << " " << strerror(read.error()) << "\n";
        header = "501 Invalid maping";
        break;
      default:
        if(options.value().verbose_flag) std::cerr << "Error desconocido: " << options.value().filename  << " " << strerror(read.error()) << "\n";
        header = "500 Unnknown error";
        break;
    }
    send_response(header, body);
  } else {
    // Como hemos proibido las copias, tenemos que mover el SafeMap a una variable local
    if (options.value().verbose_flag) std::cerr << "Movemos el SafeMap a una variable local\n";
    SafeMap map = std::move(read.value());
    if (options.value().verbose_flag) std::cerr << "Obtenemos el body y el header de nuestro archivo\n";
    body = map.get_sv();
    size_t length = body.size();
    oss << "Content-Length: " << length << '\n';
    header = oss.str();
    if (options.value().verbose_flag) std::cerr << "Enviamos la respuesta\n";
    send_response(header, body);
  }
  return EXIT_SUCCESS;
}
