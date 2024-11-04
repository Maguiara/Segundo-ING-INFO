#include "tools.h"
#include "myAlphabet.h"

class Grammar {
  public:
  void Transform2CFN(const std::string& input_file, const std::string& output_file);
  void LoadInformation(const std::string& input_file);
  char GenerateNonTerminal(const char c);
  

  

 private:
  void PrimeraParte();
  void SegundaParte();
  void Write(const std::string& output_file);
  void SimplificarRepetidos();
  bool ComprobarProduccion(const std::string& production);
  void ErrorExit();
  int num_of_terminals_;
  std::set<char> terminals_;
  int num_of_non_terminals_;
  std::set<char> non_terminals_;
  int num_of_productions_;
  std::multimap<char, std::string> productions_;
  Alphabet valid_alphabet_;
};