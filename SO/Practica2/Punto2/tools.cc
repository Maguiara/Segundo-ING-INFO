
#include "tools.h"
#include "SafeFD.h"
#include "SafeMap.h"

void show_help() {
  std::cout << "Uso: docserver [opciones] archivo\n"
            << "Opciones:\n"
            << "  -h, --help: Mostrar esta ayuda\n"
            << "  -v, --verbose: Mostrar información adicional\n"
            << "  -p <puerto>, --port <puerto>: Especificar el puerto TCP\n";
}

std::expected<OpcionesAdmitidas, ErrorCode> parse_args(int argc, char* argv[]) {
  std::vector<std::string_view> arguments(argv + 1, argv + argc);
  OpcionesAdmitidas options;
  if (arguments.empty()) return std::unexpected(ErrorCode::MISSING_ARGUMENTS);
  for (auto it = arguments.begin(); it != arguments.end(); ++it) {
    if (*it == "-h" || *it == "--help") {
      options.show_help_flag = true;
    } else if (*it == "-v" || *it == "--verbose") {
    } else if (*it == "-p" || *it == "--port") {
      if (++it == arguments.end()) return std::unexpected(ErrorCode::MISSING_ARGUMENTS);
      options.port = std::stoi(std::string(*it));
    } else if (!it->starts_with("-")) {
    } else if (!it->starts_with("-")) {
      options.aditional_arguments.push_back(std::string(*it));
  if (options.aditional_arguments.empty()) return std::unexpected(ErrorCode::MISSING_FILE);
  if (options.port == 0) options.port = 8080; // Default port
      return std::unexpected(ErrorCode::UNKNOWN_OPTION);
    }
  }
  if (options.aditional_arguments.empty()) return std::unexpected(ErrorCode::MISSING_FILE);
  else options.filename = options.aditional_arguments.front();
  
  return options;
}


std::expected<SafeMap, int> read_all(const std::string& path, bool verbose) {
  if (verbose) std::cerr << "Intentando abrir el archivo " << path << "\n";
  std::expected<SafeFD, int> result = open_file(path, O_RDONLY);
  if (!result.has_value()) {
    if (verbose) std::cerr << "Error al abrir el archivo " << path << ": " <<   "\n";
    return std::unexpected(result.error());
  }
  if (verbose) std::cerr << "Archivo " << path << " abierto correctamente\n";
  // Como hemos proibido las copias, tenemos que mover el SafeFD a una variable local
  SafeFD fd = std::move(result.value());
  if (verbose) std::cerr << "Comprobando el descriptor de archivo de " << path << " sea valido " << "\n";
  if (!fd.is_valid()) {
    if (verbose) std::cerr << "El descriptor de archivo de " << path << " no es valido\n";
    return std::unexpected(errno);
  }

  if (verbose) std::cerr << "Obteniendo la longitud del archivo " << path << "\n";
  long int length = lseek(fd.get_fd(), 0, SEEK_END);

  if (verbose) std::cerr << "Intentando mapear el archivo " << path << " en memoria\n";
  void* mem = mmap(nullptr, static_cast<size_t>(length), PROT_READ, MAP_PRIVATE, fd.get_fd(), 0);
  if (mem == MAP_FAILED) {
    if (verbose) std::cerr << "Error al mapear el archivo " << path << ": " << strerror(errno) << "\n";
    return std::unexpected(errno);
  }
  if (verbose) std::cerr << "Archivo " << path << " mapeado correctamente\n";
  SafeMap map{static_cast<char*>(mem), static_cast<int>(length)};
  return map;
}

void start_server(int port, const std::string& filepath, bool verbose) {
  int server_fd, new_socket;
  struct sockaddr_in address{};
  int opt = 1;
  int addrlen = sizeof(address);
  if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
    perror("socket failed");
    exit(EXIT_FAILURE);
  }
  if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
    perror("setsockopt");
    exit(EXIT_FAILURE);
  }
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(port);
  if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
    perror("bind failed");
    exit(EXIT_FAILURE);
  }
  if (listen(server_fd, 3) < 0) {
    perror("listen");
    exit(EXIT_FAILURE);
  }
  while (true) {
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
      perror("accept");
      continue;
    }
    // Leer el contenido del archivo
    auto result = read_all(filepath, verbose);
    if (!result) {
      int err = result.error();
      std::string response;
      if (err == EACCES) {
        response = "HTTP/1.1 403 Forbidden\n\n";
      } else if (err == ENOENT) {
        response = "HTTP/1.1 404 Not Found\n\n";
      } else {
        response = "HTTP/1.1 500 Internal Server Error\n\n";
      }
      send(new_socket, response.c_str(), response.size(), 0);
    } else {
      SafeMap file_map = result.value();
      std::ostringstream response;
      response << "HTTP/1.1 200 OK\n" << "Content-Length: " << file_map.get().size() << "\n\n" << file_map.get();
      std::string response_str = response.str();
      send(new_socket, response_str.c_str(), response_str.size(), 0);
    }
    close(new_socket);
  }
}

std::string get_env(const std::string& name) {
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