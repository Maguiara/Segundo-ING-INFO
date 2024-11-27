
#include "tools.h"
#include "SafeFD.h"
#include "SafeMap.h"

void show_help() {
  std::cout << "Uso: docserver [opciones] archivo\n"
            << "Opciones:\n"
            << "  -h, --help: Mostrar esta ayuda\n"
            << "  -v, --verbose: Mostrar información adicional\n"
            // Modificacio si el archivo es mayor que 1024 bytes, se considera un error fatal y se detiene la ejecucion
            << "  -x,  : Si el archivo es mayor que 1024 bytes, se detiene la ejecución\n";
}

std::expected<OpcionesAdmitidas, ErrorCode> parse_args(int argc, char* argv[]) {
  std::vector<std::string_view> arguments(argv + 1, argv + argc);
  OpcionesAdmitidas options;
  if (arguments.empty()) return std::unexpected(ErrorCode::MISSING_ARGUMENTS);
  for (auto it = arguments.begin(); it != arguments.end(); ++it) {
    if (*it == "-h" || *it == "--help") {
      options.show_help_flag = true;
    } else if (*it == "-v" || *it == "--verbose") {
      options.verbose_flag = true;
    } else if (!it->starts_with("-")) {
      options.aditional_arguments.push_back(std::string(*it));
    } else if (*it == "-x") {
      options.stop_flag = true;
    } else {
      return std::unexpected(ErrorCode::UNKNOWN_OPTION);
    }
  }
  if (options.aditional_arguments.empty()) return std::unexpected(ErrorCode::MISSING_FILE);
  else options.filename = options.aditional_arguments.front();
  
  return options;
}


std::expected<SafeMap, int> read_all(const std::string& path, bool verbose, bool stop) {
  if (verbose) std::cerr << "Intentando abrir el archivo " << path << "\n";
  std::expected<SafeFD, int> result = open_file(path, O_RDONLY);
  if (!result.has_value()) {
    if (verbose) std::cerr << "Error al abrir el archivo " << path << ": " <<   "\n";
    return std::unexpected(result.error());
  }
  if (verbose) std::cerr << "Archivo " << path << " abierto correctamente\n";
  // Como hemos proibido las copias, tenemos que mover el SafeFD a una variable local que se destruira al final del ambito
  SafeFD fd = std::move(result.value());
  if (verbose) std::cerr << "Comprobando el descriptor de archivo de " << path << " sea valido " << "\n";
  if (!fd.is_valid()) {
    if (verbose) std::cerr << "El descriptor de archivo de " << path << " no es valido\n";
    return std::unexpected(errno);
  }

  if (verbose) std::cerr << "Obteniendo la longitud del archivo " << path << "\n";
  long int length = lseek(fd.get_fd(), 0, SEEK_END);
  if (stop && length > 1024) {
    if (verbose) std::cerr << "El archivo " << path << " es mayor que 1024 bytes\n";
    return std::unexpected(1024);
  }
  if (verbose) std::cerr << "Intentando mapear el archivo " << path << " en memoria\n";
  void* mem = mmap(nullptr, static_cast<size_t>(length), PROT_READ, MAP_PRIVATE, fd.get_fd(), 0);
  if (mem == MAP_FAILED) {
    if (verbose) std::cerr << "Error al mapear el archivo " << path << ": " << strerror(errno) << "\n";
    return std::unexpected(errno);
  }
  if (verbose) std::cerr << "Archivo " << path << " mapeado correctamente\n";

  if (verbose) std::cerr << "Leyendo el archivo " << path << " en memoria\n";
  SafeMap map{static_cast<char*>(mem), static_cast<int>(length)};
  return map;
}

void send_response(std::string_view header, std::string_view body) {
  std::cout << header << "\n" << body << "\n";
}


std::string getenv(const std::string& name) {
  char* value = getenv(name.c_str());
  if (value) return std::string(value);
  else return std::string();
}










/** Por si llego a necesitarlo
 *  if (options.error() == ErrorCode::UNKNOWN_OPTION) {
      std::cerr << "Opción desconocida\n";
    } else if (options.error() == ErrorCode::MISSING_FILE) {
      std::cerr << "Falta el nombre del archivo\n";
    } else if (options.error() == ErrorCode::MISSING_ARGUMENTS) {
      std::cerr << "Faltan argumentos y/o archivos\n";
    } else if (options.error() == ErrorCode::PERMISSION_DENIED) {
      send_response("403 Forbidden", "No tienes permisos para acceder a este archivo\n");
    } else if (options.error() == ErrorCode::FILE_NOT_FOUND) {
      send_response("404 Not Found", "El archivo solicitado no existe\n");
    } else {
      send_response("500 Internal Server Error", "Error interno del servidor\n");
    }
 */