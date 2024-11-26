

#ifndef SAFEFD_H
#define SAFEFD_H

#include "tools.h"


class SafeFD {
 public:
  // Constructor por parametrizado y por defecto
  explicit SafeFD(int fd) noexcept : fd_{fd} {}
  explicit SafeFD() noexcept : fd_{-1} {}
  // Deshabilitar copia y asignación
  SafeFD(const SafeFD&) = delete;
  SafeFD& operator=(const SafeFD&) = delete;
  // Mover constructor y asignación
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
  // Destructor
  ~SafeFD() noexcept { if (fd_ >= 0)  close(fd_); }

  // Métodos de acceso
  [[nodiscard]] bool is_valid() const noexcept { return fd_ >= 0; }
  [[nodiscard]] int get_fd() const noexcept { return fd_; }
  // Metodos para el obeter el descriptor de archivo
 private:
  int fd_;
};

#endif