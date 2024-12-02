
#include "tools.h"
#include "SafeFD.h"
#include "SafeMap.h"
// para poder usar los sockets


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
      options.verbose_flag = true;
    } else if (*it == "-p" || *it == "--port") {
      if (++it == arguments.end()) return std::unexpected(ErrorCode::MISSING_ARGUMENTS);
      options.port = std::stoi(std::string(*it));
      options.port_flag = true;
      std::cout << "Puerto: " << options.port << "\n";
    } else if (!it->starts_with("-")) {
      options.aditional_arguments.push_back(std::string(*it));
    } else {
      return std::unexpected(ErrorCode::UNKNOWN_OPTION);
    }
  }
  if (options.aditional_arguments.empty()) return std::unexpected(ErrorCode::MISSING_FILE);
  else options.filename = options.aditional_arguments.front();

  if (!options.port_flag) {
    std::string port;
    port = getenv("DOCSERVER_PORT");
    if (!port.empty()) options.port = std::stoi(port);
  }
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

std::expected<SafeFD, int> make_socket(uint16_t port) {
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  std::cout << "Socket: " << sockfd << "\n";
  if (sockfd < 0) {
    std::cout << "Fallo del socket\n";
    return std::unexpected(errno);
  }
  SafeFD socket(sockfd);

  // Configuracion el socket
  sockaddr_in serv_addr;
  // Pone todos los bytes a 0 en la estructura serv_addr
  std::memset(&serv_addr, 0, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  serv_addr.sin_port = htons(port);

  int bind_socket = bind(socket.get_fd(), reinterpret_cast<sockaddr*>(&serv_addr), sizeof(serv_addr));
  std::cout << "Bind: " << bind_socket << "\n";
  if (bind_socket < 0) {
    std::cout << "Fallo del bind\n";
    return std::unexpected(errno);
  }

  // Settear el socket en modo no bloqueante, si no se hacen estas lineas el codigo no furula
  int flags = fcntl(socket.get_fd(), F_GETFL, 0);
  if (flags == -1) {
    std::cout << "Error al obtener flags del socket\n";
    return std::unexpected(errno);
  }
  if (fcntl(socket.get_fd(), F_SETFL, flags | O_NONBLOCK) == -1) {
    std::cout << "Error al establecer el socket en modo no bloqueante\n";
    return std::unexpected(errno);
  }

  return socket;
}

int listen_connection(const SafeFD& socket) {
  int conection = listen(socket.get_fd(), 10);
  std::cout << "Listen: " << conection << "\n";
  if (conection < 0) {
    return errno;
  }
  return 0;
}

std::expected<SafeFD, int> accept_connection(const SafeFD& socket, sockaddr_in& client_addr) {
  socklen_t client_addr_len = sizeof(client_addr);
  std::cout << "Esperando conexión\n"; // deppuración
  int client_fd = accept(socket.get_fd(), reinterpret_cast<sockaddr*>(&client_addr), &client_addr_len);
  std::cout << "Accept: " << client_fd << "\n";
  if (client_fd < 0) {
    return std::unexpected(errno);
  }
  return SafeFD(client_fd);
}


void send_response(std::string_view header, std::string_view body) {
  std::cout << header << "\n" << body;
}



std::string getenv(const std::string& name) {
  char* value = std::getenv(name.c_str());
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