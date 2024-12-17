
#include "tools.h"
#include "SafeFD.h"
#include "SafeMap.h"

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
        std::cerr << "Faltan argumentos y/o nombre del archivo\n";
        break;
      default:
        std::cerr << "Error desconocido\n";
        break;
    }
    std::cerr << "Use --help o -h para obtener ayuda\n";
    return EXIT_FAILURE;
  }
  // Mostrar la ayuda si se solicita
  if (options.value().show_help_flag) {
    show_help();
    return EXIT_SUCCESS;
  }

  // Creamos el socket
  auto socket = make_socket(static_cast<uint16_t>(options.value().port), options.value().verbose_flag);
  if (!socket.has_value()) {
    std::cerr << "Error al crear el socket: " << strerror(socket.error()) << "\n";
    return EXIT_FAILURE;
  }
  SafeFD socket_fd = std::move(socket.value());

  // Escuchar el socket
  auto listen_socket = listen_connection(socket_fd, options.value().verbose_flag);
  if (listen_socket != 0) {
    std::cerr << "Error al escuchar el socket: " << strerror(listen_socket) << "\n";
    return EXIT_FAILURE;
  }

  while (true) {
    // Aceptar la conexion del socket
    sockaddr_in client_addr{};
    auto client = accept_connection(socket_fd, client_addr, options.value().verbose_flag);
    if (!client.has_value()) {
        std::cerr << "Error al aceptar la conexión: " << strerror(client.error()) << "\n";
        return EXIT_FAILURE;
    }
    SafeFD client_fd = std::move(client.value());

    // Recibir la petición
    size_t max_size = 4096;
    auto request = receive_request(client_fd, max_size, options.value().verbose_flag);
    if (!request.has_value()) {
      if (request.error() == ECONNRESET) {
        std::cerr << "Error leve al recibir la petición: " << strerror(request.error()) << "\n";
        continue;
      } else {
        std::cerr << "Error fatal al recibir la petición: " << strerror(request.error()) << "\n";
        return EXIT_FAILURE;
      }
    }
    // Procesamos la peticion
    std::istringstream iss(request.value());
    std::string petition, path, header;
    std::string_view body;
    iss >> petition >> path;
    if (petition != "GET") {
      header = "400 Bad request";
      int result = send_response(client_fd, header, body);
      if (result == ECONNRESET) {
        std::cerr << "Error leve al enviar la respuesta: " << strerror(result) << "\n";
        continue;
      } else if (result != 0) {
        std::cerr << "Error fatal al enviar la respuesta: " << strerror(result) << "\n";
        return EXIT_FAILURE;
      }
      continue;
    }
    if (!options.value().base_path.starts_with("/") ) {
      header = "407 Bad route";
      int result = send_response(client_fd, header, body);
      if (result == ECONNRESET) {
        std::cerr << "Error leve al enviar la respuesta: " << strerror(result) << "\n";
        continue;
      } else if (result != 0) {
        std::cerr << "Error fatal al enviar la respuesta: " << strerror(result) << "\n";
        return EXIT_FAILURE;
      }
      continue;
    }

    // Buscamos el archivo
    auto file = options.value().base_path + path;
    auto file_content = read_all(file, options.value());
    if (!file_content.has_value()) {
      if (file_content.error() == EACCES || file_content.error() == ENOENT) {
        std::cerr << "Error leve al leer el archivo: " << strerror(file_content.error()) << "\n";
        continue;
      } else {
        std::cerr << "Error fatal al leer el archivo: " << strerror(file_content.error()) << "\n";
        return EXIT_FAILURE;
      }
    }
    SafeMap map = std::move(file_content.value());
    body = map.get_sv();
    std::ostringstream oss;
    oss << "Content-Length: " << body.size() << '\n';
    header = oss.str();
    int result_send = send_response(client_fd, header, body);
    if (result_send == ECONNRESET) {
      std::cerr << "Error leve al enviar la respuesta: " << strerror(result_send) << "\n";
      continue;
    } else if (result_send != 0) {
      std::cerr << "Error fatal al enviar la respuesta: " << strerror(result_send) << "\n";
      return EXIT_FAILURE;
    }
    // Cerramos la conexión, SafeFD se encarga de cerrar el descriptor
  }
  return EXIT_SUCCESS;
}
