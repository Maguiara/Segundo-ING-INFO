

#include "structHandler.h"


void structHandler::StoreDefinition(const std::string& line, const std::smatch& match, const int lineNumber) {
    structs_.push_back("[LINE " + std::to_string(lineNumber) + "] DEFINITION: " + match[0].str());
}


void structHandler::StoreDeclaration(const std::string& line, const std::smatch& match, const int lineNumber) {
    structs_.push_back("[LINE " + std::to_string(lineNumber) + "] DECLARATION VARIABLE: " + match[0].str());
}

void structHandler::PrintStructs(std::ofstream& output) {
    for (const auto& structs : structs_) {
        output << structs << std::endl; 
    }
}