#include "compiler.h"
#include <iomanip>
#include <iostream>
#include "scanner.h"

namespace cclox {
void Compiler::compile(std::string_view source) {
  Scanner scanner(source);
  int line = -1;
  while (true) {
    Token token = scanner.scanToken();

    if (token.line != line) {
      std::cout << std::setw(4) << token.line << " ";
      line = token.line;
    } else {
      std::cout << "   | ";
    }

    // Print token type and substring
    std::cout << std::setw(2) << token.type << " '" << std::string_view(token.start, token.length) << "'\n";

    if (token.type == TokenType::TOKEN_EOF) break;
  }
}
}  // namespace cclox