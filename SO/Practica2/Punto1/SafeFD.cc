

#include "SafeFD.h"


/*std::expected<SafeFD, ErrorCode> open_file(const std::string& path, int flags, mode_t mode = 0) {
  int fd = open(path.c_str(), flags, mode);
  if (fd < 0) {
    if (errno == EACCES) {
      return std::unexpected(ErrorCode::PERMISSION_DENIED);
    } else if (errno == ENOENT) {
      return std::unexpected(ErrorCode::FILE_NOT_FOUND);
    } else {
      return std::unexpected(ErrorCode::OTHER_ERROR);
    }
  }
  return SafeFD{fd};
}

*/