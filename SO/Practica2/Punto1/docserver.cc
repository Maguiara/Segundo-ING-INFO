
/**
 * PSEUDOCÓDIGO DE LA PRACTICA
 * parse_args(): Procesar los argumentos de la línea de comandos
    error-fatal if error al procesar los argumentos
    if las opciones contienen -h o --help
      Mostrar ayuda
      Terminar sin error
    end if
    error-fatal if NO se ha indicado un nombre de archivo en los argumentos
      read_all(): Leer archivo en memoria
      if error de permisos o archivo no encontrado
        send_response(): Mostrar mensaje de error leve
        (ver Sección 1.1.2)
        error
      elif otro error etectado
        error-fatal
      else
        send_response(): Mostrar el contenido del archivo en la salida estándar
        (ver Sección 1.1)
      end if
 * 
 */


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
    return EXIT_FAILURE;
  } 
  if (options.value().show_help_flag) {
    show_help();
    return EXIT_SUCCESS;
  }
  auto read = read_all(options.value().filename);
  if (!read.has_value()) {
    switch (read.error()) {
      case EACCES:
        send_response("403 forbbiden","");
        break;
      case ENOENT:
        send_response("404 Not Found","");
        break;
      default:
        send_response("500 Error desconocido","");
        break;
    }
  } else {
    std::string_view body = read.value();
    size_t length = body.size();
    std::ostringstream oss;
    oss << "Content-Length: " << length << '\n';
    std::string header = oss.str();
    send_response(header, body);
  }
  return EXIT_SUCCESS;
}
