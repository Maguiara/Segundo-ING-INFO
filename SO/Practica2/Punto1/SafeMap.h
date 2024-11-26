
#ifndef SAFEMAP_H
#define SAFEMAP_H


#include "tools.h"

class SafeMap {

  public:
    // Constructor por parametrizado
    SafeMap(char* mem, int length) noexcept : sv_{mem, static_cast<size_t>(length)} {}

    ~SafeMap() {
      if (!sv_.empty()) {
        munmap(const_cast<char*>(sv_.data()), sv_.size());
      }
    }
    // Metodos de acceso
    [[nodiscard]] std::string_view get_sv() const noexcept { return sv_; }
private:
  std::string_view sv_;
};

#endif