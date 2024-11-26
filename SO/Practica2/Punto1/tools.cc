
#include "tools.h"
#include "SafeFD.h"
#include "SafeMap.h"

void show_help() {
  std::cout << "Uso: docserver [opciones] archivo\n"
            << "Opciones:\n"
            << "  -h, --help: Mostrar esta ayuda\n"
            << "  -v, --verbose: Mostrar información adicional\n";
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
    }else {
      return std::unexpected(ErrorCode::UNKNOWN_OPTION);
    }
  }
  if (options.aditional_arguments.empty()) {
    return std::unexpected(ErrorCode::MISSING_FILE);
  } else {
    options.filename = options.aditional_arguments.front();
  }
  return options;
}

// En vez de devolver un int como error, devuelvo un ErrorCode
std::expected<std::string_view, int> read_all(const std::string& path) {
  int fd = open(path.c_str(), O_RDONLY);
  if (fd < 0) {
    return std::unexpected(errno);
  }
  // Retorna la posicion a la que se ha movido el puntero de lectura escritura
  // al ponerse al final del archivo retorna su tamaño
  long int length = lseek( fd, 0, SEEK_END );

  // Se mapea el archivo en memoria, con permisos de solo lectura,
  // de forma privada, con su descriptor de archivo 
  // y un offset de 0 para comenzar desde el principio
  void* mem = mmap(NULL, static_cast<size_t>(length), PROT_READ, MAP_PRIVATE, fd, 0);
  if (mem == MAP_FAILED) {
    close(fd);
    return std::unexpected(errno);
  }
  // Se cierra el descriptor de archivo
  close(fd);
  // Se retorna un string_view con el contenido del archivo
  return std::string_view(static_cast<char*>(mem), static_cast<size_t>(length));
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