

#ifndef COMMENTHANDLER_H
#define COMMENTHANDLER_H

#include "tools.h"


class commentHandler {

 public:
  commentHandler() = default;
  void StoreSingleLineComments(const std::string& line, const int lineNumber);
  void StoreMultiLineComments(const int firts_comment_line, const int last_comment_line);
  void PrintComments(std::ofstream& output);

 private:
  std::vector<std::string> comments_;
};

#endif