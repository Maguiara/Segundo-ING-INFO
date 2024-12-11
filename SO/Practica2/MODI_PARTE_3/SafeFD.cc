

#include "SafeFD.h"


std::expected<SafeFD, int> open_file(const std::string& path, int flags, mode_t mode) {
  int fd = open(path.c_str(), flags, mode);
  if (fd == -1) {

    return std::unexpected(errno);
  }
  return SafeFD{fd};
}
