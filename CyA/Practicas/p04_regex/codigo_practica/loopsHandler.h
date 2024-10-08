

#ifndef LOOPSHANDLER_H
#define LOOPSHANDLER_H

#include "tools.h"

class loopsHandler {

 public:
  loopsHandler() = default;
  void StoreForLoops(const int lineNumber);
  void StoreWhileLoops(const int lineNumber); 
  void PrintLoops(std::ofstream& output); 

 private:
  std::vector<std::string> loops_;
};

#endif