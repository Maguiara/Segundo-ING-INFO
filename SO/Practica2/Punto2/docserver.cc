
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
        std::cerr << "Faltan argumentos y/o nombre del archivo\n";
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
   auto socket = make_socket(static_cast<uint16_t>(options.value().port));
   if (!socket.has_value()) {
    std::cerr << "Error al crear el socket: " << strerror(socket.error()) << "\n";
    return EXIT_FAILURE;
   }
    auto listen_socket = listen_connection(socket.value());
    if (listen_socket != 0) {
      std::cerr << "Error al escuchar el socket: " << strerror(listen_socket) << "\n";
      return EXIT_FAILURE;
    }

    auto client = accept_connection(socket.value());
    if (!client.has_value()) {
      std::cerr << "Error al aceptar la conexión: " << strerror(client.error()) << "\n";
      return EXIT_FAILURE;
    }

  return EXIT_SUCCESS;
}
