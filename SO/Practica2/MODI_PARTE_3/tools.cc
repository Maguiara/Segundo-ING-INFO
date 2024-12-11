
#include "tools.h"
#include "SafeFD.h"
#include "SafeMap.h"
// para poder usar los sockets


void show_help() {
  std::cout << "Uso: ./docserver [opciones] archivo\n"
            << "Opciones:\n"
            << "  -h, --help: Mostrar esta ayuda\n"
            << "  -v, --verbose: Mostrar información adicional\n"
            << "  -p <puerto>, --port <puerto>: Especificar el puerto TCP\n"
            << "  -b <ruta>, --base <ruta>: Especificar la ruta base\n"
            << "  -q <cantidad>, --quantity <cantidad>: Especificar la cantidad de bytes a leer\n";
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
    } else if (*it == "-b" || *it == "--base") {
      if (++it == arguments.end()) return std::unexpected(ErrorCode::MISSING_ARGUMENTS);
      options.base_path = std::string(*it);
      options.base_path_flag = true;
    } else if (*it == "-q" || *it == "--quantity") {
      if (++it == arguments.end()) return std::unexpected(ErrorCode::MISSING_ARGUMENTS);
      options.valor = std::stoi(std::string(*it));
      options.valor_flag = true;
    } else if (!it->starts_with("-")) {
      options.filename = std::string(*it);
    } else {
      return std::unexpected(ErrorCode::UNKNOWN_OPTION);
    }
  }

  if (!options.base_path_flag) {
    const char* env_base_path = std::getenv("DOCSERVER_BASEDIR");
    if (env_base_path) {
      options.base_path = std::string(env_base_path);
    } else {
      char cwd[PATH_MAX];
      if (getcwd(cwd, sizeof(cwd)) != nullptr) {
        options.base_path = std::string(cwd);
      } else {
        return std::unexpected(ErrorCode::MISSING_ARGUMENTS);
      }
    }
  }

  return options;
}



std::expected<SafeMap, int> read_all(const std::string& path, const OpcionesAdmitidas& options) {
  std::string relative_path = path;
  if (path.starts_with("/")) {
    if (options.verbose_flag) std::cerr << "Transformando la ruta absoluta " << path << " en ruta relativa\n";
    // PATH MAX es una constante que indica el tamaño maximo de una ruta en el sistema
    char cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd)) != nullptr) {
      std::string current_dir(cwd);
      if (path.find(current_dir) == 0) {
        relative_path = path.substr(current_dir.length() + 1);
      } else {
        if (options.verbose_flag) std::cerr << "La ruta absoluta no contiene el directorio actual\n";
        return std::unexpected(errno);
      }
    } else {
      if (options.verbose_flag) std::cerr << "Error obteniendo el directorio actual\n";
      return std::unexpected(errno);
    }
  }

  if (options.verbose_flag) std::cerr << "Intentando abrir el archivo " << relative_path << "\n";
  std::expected<SafeFD, int> result = open_file(relative_path, O_RDONLY);
  if (!result.has_value()) {
    if (options.verbose_flag) std::cerr << "Error al abrir el archivo " << relative_path << ": " << strerror(result.error()) << "\n";
    return std::unexpected(result.error());
  }
  if (options.verbose_flag) std::cerr << "Archivo " << relative_path << " abierto correctamente\n";
  // Como hemos proibido las copias, tenemos que mover el SafeFD a una variable local
  SafeFD fd = std::move(result.value());
  if (options.verbose_flag) std::cerr << "Comprobando el descriptor de archivo de " << relative_path << " sea valido " << "\n";
  if (!fd.is_valid()) {
    if (options.verbose_flag) std::cerr << "El descriptor de archivo de " << relative_path << " no es valido\n";
    return std::unexpected(errno);
  }

  if (options.verbose_flag) std::cerr << "Obteniendo la longitud del archivo " << relative_path << "\n";
  long int length = lseek(fd.get_fd(), 0, SEEK_END);
  if (options.valor_flag) {
    length = options.valor;
  }

  if (options.verbose_flag) std::cerr << "Intentando mapear el archivo " << relative_path << " en memoria\n";
  void* mem = mmap(nullptr, static_cast<size_t>(length), PROT_READ, MAP_PRIVATE, fd.get_fd(), 0);
  if (mem == MAP_FAILED) {
    if (options.verbose_flag) std::cerr << "Error al mapear el archivo " << relative_path << ": " << strerror(errno) << "\n";
    return std::unexpected(errno);
  }

  if (options.verbose_flag) std::cerr << "Archivo " << relative_path << " mapeado correctamente\n";
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

std::expected<std::string, int> receive_request(const SafeFD& socket, size_t max_size, const bool verbose) {
  std::string buffer(max_size, 0);
  if (verbose) std::cerr << "Recibiendo la petición\n";
  ssize_t bytes_received = recv(socket.get_fd(), &buffer[0], max_size, 0);
  if (bytes_received < 0) {
    if (verbose) std::cerr << "Error recibiendo la petición\n";
    return std::unexpected(errno);
  }
  if (verbose) std::cerr << "Petición recibida correctamente\n";
  buffer.resize(static_cast<std::string::size_type>(bytes_received));
  return buffer;
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
  else return std::string();
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