


#include "loopsHandler.h"

void loopsHandler::StoreForLoops(const int lineNumber) {
    loops_.push_back("[Line " + std::to_string(lineNumber) + "] LOOP: for");
}

void loopsHandler::StoreWhileLoops(const int lineNumber) {
    loops_.push_back("[Line " + std::to_string(lineNumber) + "] LOOP: while");
}

void loopsHandler::PrintLoops(std::ofstream& output) {
  for (const auto& statment : loops_) {
    output << statment << std::endl;
  }
}