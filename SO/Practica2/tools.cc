
#include "tools.h"

struct ErrorCode {
  int code;
  std::string message;
};

void show_help() {
  std::cout << "MODOS DE USO: \n";
  std::cout << "docserver [archivo] \n";
  std::cout << "docserver -h | --help \n";
  std::cout << "docserver -v | --verbose\n";
}

std::expected<std::string_view, int> read_all(const std::string& path) {
  int fd = open(path.c_str(), O_RDONLY);
  if (fd < 0) {
    return std::unexpected(errno);
  }
  

}; 

ErrorCode parse_args(int argc, char *argv[]) {
   for (int i = 1; i < argc; i++) {
    std::string arg = argv[i];
    if (arg == "-h" | arg == "--help") {
      show_help();
      return {0, ""};
    } else if (arg == "-v" | arg == "--verbose") {
      // Verbose
    } else if (arg[0] != '-') {
      auto result = read_all(arg);
      if (!result) {
        int error_code = result.error().value();
        switch (error_code) {
          case EACCES: 
            return {403, "Forbidden (Acceso denegado)"};
          case ENOENT:
            return {404, "Not Found (Archivo no encontrado)"};
          default:
            return {500, "Error desconocido"};
        }
      }
    } else {
      return {1, "Argumento no reconocido"};
    }
   }
   return {0, ""};
}