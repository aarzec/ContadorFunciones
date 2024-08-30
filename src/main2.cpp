#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

// Helper function to skip whitespaces and comments
void skipWhitespaceAndComments(std::istream &input) {
    char ch;
    bool inComment = false;

    while (input.get(ch)) {
        if (inComment) {
            if (ch == '*' && input.peek() == '/') {
                input.get(); // Skip '/'
                inComment = false;
            }
        } else {
            if (ch == '/') {
                if (input.peek() == '/') {
                    // Skip single line comment
                    while (input.get(ch) && ch != '\n');
                } else if (input.peek() == '*') {
                    // Skip multi-line comment
                    input.get(); // Skip '*'
                    inComment = true;
                } else {
                    input.putback(ch);
                    break;
                }
            } else if (!std::isspace(ch)) {
                input.putback(ch);
                break;
            }
        }
    }
}

// Helper function to parse an identifier
bool parseIdentifier(std::istream &input, std::string &identifier) {
    skipWhitespaceAndComments(input);
    identifier.clear();
    char ch;
    while (input.get(ch) && (std::isalnum(ch) || ch == '_' || ch == ':')) {
        identifier += ch;
    }
    if (!identifier.empty()) {
        input.putback(ch); // Put back the non-identifier character
        return true;
    }
    return false;
}

// Check if the next non-whitespace characters are '()'
bool isFunctionDefinition(std::istream &input) {
    skipWhitespaceAndComments(input);
    char ch;
    if (input.get(ch) && ch == '(') {
        int parenDepth = 1;
        while (input.get(ch)) {
            if (ch == '(') parenDepth++;
            if (ch == ')') parenDepth--;
            if (parenDepth == 0) break;
        }
        skipWhitespaceAndComments(input);
        if (input.get(ch) && ch == '{') {
            input.putback(ch);
            return true;
        }
    }
    return false;
}

int countFunctionDefinitions(const std::string &filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return 0;
    }

    int functionCount = 0;
    std::string word;

    while (file) {
        std::string returnType, functionName;
        if (parseIdentifier(file, returnType) && parseIdentifier(file, functionName)) {
            if (isFunctionDefinition(file)) {
                functionCount++;
                std::cout << "Function: " << returnType << " " << functionName << std::endl;
                // Skip function body
                char ch;
                int braceDepth = 0;
                while (file.get(ch)) {
                    if (ch == '{') braceDepth++;
                    if (ch == '}') braceDepth--;
                    if (braceDepth == 0) break;
                }
            }
        }
    }

    return functionCount;
}

int main() {
    std::string filename = "/home/kmd/Downloads/proyecto_v21-jun/model/Nodo.cpp";
    int functionCount = countFunctionDefinitions(filename);
    std::cout << "Number of function definitions: " << functionCount << std::endl;
    return 0;
}
