
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

#include <iostream>
#include <string>
#include <fstream>
#include <expected>
#include <unistd.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string_view>
#include <errno.h>

struct ErrorCode {
  int code;
  std::string message;
};


class SafeFD {
 public:
  explicit SafeFD(int fd) noexcept : fd_{fd} {}
  explicit SafeFD() noexcept : fd_{-1} {}
  SafeFD(const SafeFD&) = delete;
  SafeFD& operator=(const SafeFD&) = delete;
  SafeFD(SafeFD&& other) noexcept : fd_{other.fd_} { other.fd_ = -1; }
  SafeFD& operator=(SafeFD&& other) noexcept { 
    if (this != &other && fd_ != other.fd_) {
      // Cerrar el descriptor de archivo actual
      close(fd_);
      // Mover el descriptor de archivo de 'other' a este objeto
      fd_ = other.fd_;
      other.fd_ = -1;
      }
      return *this;
    }
  ~SafeFD() noexcept { if (fd_ >= 0)  close(fd_); }

  [[nodiscard]] bool is_valid() const noexcept { return fd_ >= 0; }
  [[nodiscard]] int get() const noexcept { return fd_; }
 private:
  int fd_;
};

void show_help() {
  std::cout << "MODOS DE USO: \n";
  std::cout << "docserver [archivo] \n";
  std::cout << "docserver -h | --help \n";
  std::cout << "docserver -v | --verbose\n";
}

ErrorCode parse_args(int argc, char *argv[]) {
   for (int i = 1; i < argc; i++) {
    std::string arg = argv[i];
    if (arg == "-h" | arg == "--help") {
      show_help();
      return {0, ""};
    } else if (arg == "-v" | arg == "--verbose") {
      // Verbose
    } else if (arg[0] != '-') {
      //Archivo
    } else {
      return {1, "Argumento no reconocido"};
    }
   }
   
}

std::expected<std::string_view, int> read_all(const std::string& path) {
  
}; 


int main (int argc, char *argv[]) {
  ErrorCode error_code = parse_args(argc, argv);
  if (error_code.code == 0) {
    return 0;
  } else if (error_code.code == 1) {
    std::cerr << error_code.message << std::endl;
    return error_code.code;
  }

}
