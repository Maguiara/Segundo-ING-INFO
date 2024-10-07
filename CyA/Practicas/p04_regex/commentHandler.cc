
#include "commentHandler.h"

void commentHandler::StoreSingleLineComments(const std::string& line, const int lineNumber) {
  comments_.push_back("[Line " + std::to_string(lineNumber) + "] Comment: " + line + ";"); 
}

void commentHandler::StoreMultiLineComments(const int first_comment_line, const int last_comment_line) {
  if (first_comment_line == 1) {
    comments_.push_back("[Lines " + std::to_string(first_comment_line) + " - " + std::to_string(last_comment_line) + " ] DESCRIPTION");
  } else {
   comments_.push_back("[Lines " + std::to_string(first_comment_line) + " - " + std::to_string(last_comment_line) + " ] Multiline comment detected");
  }
}


void commentHandler::PrintComments(std::ofstream& output) {
   for (const auto& comments : comments_) {
    output << comments << std::endl;
  }
}