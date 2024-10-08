
#include "tools.h"

class structHandler{
 public:
  void StoreDefinition(const std::string& line, const std::smatch& match, const int lineNumber);
  void StoreDeclaration(const std::string& line, const std::smatch& match, const int lineNumber);
  void PrintStructs(std::ofstream& output);

 private:
  std::vector<std::string> structs_;
};