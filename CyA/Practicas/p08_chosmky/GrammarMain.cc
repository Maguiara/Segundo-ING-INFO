#include "tools.h"
#include "Grammar.h"
#include "myAlphabet.h"

int main(int argc, char* argv[]) {
  usage(argc, argv);
  Grammar user_grammar;
  user_grammar.Transform2CFN(argv[1], argv[2]);
}