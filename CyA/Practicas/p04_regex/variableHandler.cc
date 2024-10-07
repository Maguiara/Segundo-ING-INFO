
#include "variableHandler.h"

void variableHandler::StoreIntVariable(const int lineNumber, const std::smatch& match ) {
  if (match[2].matched) {
    variables_.push_back("[LINE " + std::to_string(lineNumber) + "] INT: " + match[1].str() + " = " + match[2].str());
  } else {
     variables_.push_back("[LINE " + std::to_string(lineNumber) + "] INT: " + match[1].str());
  }
}

void variableHandler::StoreDoubleVariable(const int lineNumber, const std::smatch& match) {
  if (match[2].matched) {
    variables_.push_back("[LINE " + std::to_string(lineNumber) + "] DOUBLE: " + match[1].str() + " = " + match[2].str());
  } else {
     variables_.push_back("[LINE " + std::to_string(lineNumber) + "] DOUBLE: " + match[1].str());
  } 
}

void variableHandler::PrintVariables(std::ofstream& output) {
   for (const auto& variable : variables_ ) {
    output << variable << std::endl;
  }
}