
#include "tools.h"
#include "SafeFD.h"
#include "SafeMap.h"
// para poder usar los sockets


void show_help() {
  std::cout << "Uso: ./docserver [opciones] archivo\n"
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
      return options;
    } else if (*it == "-v" || *it == "--verbose") {
      options.verbose_flag = true;
    } else if (*it == "-p" || *it == "--port") {
      if (++it == arguments.end()) return std::unexpected(ErrorCode::MISSING_ARGUMENTS);
      options.port = std::stoi(std::string(*it));
      options.port_flag = true;
    } else if (!it->starts_with("-")) {
      options.aditional_arguments.push_back(std::string(*it));
    } else {
      return std::unexpected(ErrorCode::UNKNOWN_OPTION);
    }
  }
  if (options.aditional_arguments.empty()) return std::unexpected(ErrorCode::MISSING_FILE);
  else options.filename = options.aditional_arguments.front();

  // Revisar bien cuando no exista la variable de entorno
   if (!options.port_flag) {
     const char* port_env = std::getenv("DOCSERVER_PORT");
     if (port_env != nullptr) options.port = std::stoi(port_env);
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

std::expected<SafeFD, int> make_socket(uint16_t port, const bool verbose) {
  if (verbose) std::cerr << "Creando el socket\n";
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (verbose) std::cerr << "Socket creado correctamente\n";
  if (sockfd < 0) {
    if (verbose) std::cerr << "Error creando el socket\n";
    return std::unexpected(errno);
  }
  SafeFD socket(sockfd);

  if (verbose) std::cerr << "Configurando el socket\n";
  // Configuracion el socket
  sockaddr_in serv_addr;
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  serv_addr.sin_port = htons(port);
  if (verbose) std::cerr << "Socket configurado correctamente\n";

  if (verbose) std::cerr << "Enlazando el socket\n";
  int bind_socket = bind(socket.get_fd(), reinterpret_cast<sockaddr*>(&serv_addr), sizeof(serv_addr));
  if (verbose) std::cerr << "Socket enlazado correctamente\n";
  if (bind_socket < 0) {
    if (verbose) std::cerr << "Error enlazando el socket\n";
    return std::unexpected(errno);
  }
  return socket;
}

int listen_connection(const SafeFD& socket, const bool verbose) {
  if (verbose) std::cerr << "Escuchando el socket\n";
  int conection = listen(socket.get_fd(), 5);
  if (verbose) std::cerr << "Socket escuchando correctamente\n";
  if (conection < 0) {
    if (verbose) std::cerr << "Error escuchando el socket\n";
    return errno;
  }
  return 0;
}

std::expected<SafeFD, int> accept_connection(const SafeFD& socket, sockaddr_in& client_addr, const bool verbose) {
  if (verbose) std::cerr << "Esperando la conexión\n";
  socklen_t client_addr_len = sizeof(client_addr);
  int client_fd = accept(socket.get_fd(), reinterpret_cast<sockaddr*>(&client_addr), &client_addr_len);
  if (verbose) std::cerr << "Conexión aceptada correctamente\n";
  if (client_fd < 0) {
    if (verbose) std::cerr << "Error aceptando la conexión\n";
    return std::unexpected(errno);
  }
  return SafeFD(client_fd);
}


int send_response(const SafeFD& socket, std::string_view header, std::string_view body) {
  std::string response = std::string(header) + "\r\n" + std::string(body) + "\r\n";
  ssize_t bytes_sent = send(socket.get_fd(), response.c_str(), response.size(), 0);
  if (bytes_sent < 0) {
    return errno;
  }
  return 0;
}


std::string getenv(const std::string& name) {
  const char* value = std::getenv(name.c_str());
  if (value) return std::string(value);
  else return "";
}

//############################################################################################################
// NO HACER CASO A ESTO, GUARDADO PARA ESTUDIO PERSONAL DEL CODIGO
//############################################################################################################

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


  // Estas lineas son para setear el socket en modo no bloqueante, no necesario para esta practica
  // int flags = fcntl(socket.get_fd(), F_GETFL, 0);
  // if (flags == -1) {
  //   std::cout << "Error al obtener flags del socket\n";
  //   return std::unexpected(errno);
  // }
  // if (fcntl(socket.get_fd(), F_SETFL, flags | O_NONBLOCK) == -1) {
  //   std::cout << "Error al establecer el socket en modo no bloqueante\n";
  //   return std::unexpected(errno);
  // }