
#ifndef SAFEMAP_H
#define SAFEMAP_H


#include "tools.h"

class SafeMap {

  public:
    // Constructor por parametrizado y por defecto
    SafeMap(char* mem, int length) noexcept : sv_{mem, static_cast<size_t>(length)} {}
    SafeMap() noexcept : sv_{} {}
    // Deshabilitar copia y asignación
    SafeMap(const SafeMap&) = delete;
    SafeMap& operator=(const SafeMap&) = delete;
    // Mover constructor y asignación
    SafeMap(SafeMap&& other) noexcept : sv_{other.sv_} { other.sv_ = {}; }
    SafeMap& operator=(SafeMap&& other) noexcept { 
      if (this != &other && sv_ != other.sv_) {
        // Mover el string_view de 'other' a este objeto
        sv_ = other.sv_;
        other.sv_ = {};
      }
      return *this;
    }
    // Destructor
    ~SafeMap() noexcept { munmap(const_cast<char*>(sv_.data()), sv_.size()); }
    // Metodos de acceso
    [[nodiscard]] std::string_view get_sv() const noexcept { return sv_; }
private:
  std::string_view sv_;
};

#endif