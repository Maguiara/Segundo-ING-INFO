
#ifndef VARIABLEHANDLER_H
#define  VARIABLE_H

#include "tools.h"

class variableHandler {

public:
  variableHandler() = default; 
  void StoreIntVariable(const int linenumber, const std::smatch& match);
  void StoreDoubleVariable(const int linenumber, const std::smatch& match);

  void PrintVariables(std::ofstream& output);

 private:
  std::vector<std::string> variables_;
};

#endif