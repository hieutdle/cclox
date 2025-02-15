#pragma once

#include <string_view>
#include "token.h"

namespace cclox {
class Scanner {
 public:
  Scanner(std::string_view source);

  Token scanToken();
  bool isAtEnd();
  Token makeToken(TokenType type);
  Token errorToken(const char* message);
  char advance();
  bool match(char expected);
  void skipWhitespace();
  char peek();
  char peekNext();
  Token string();
  bool isDigit(char c);
  Token number();
  bool isAlpha(char c);
  Token identifier();
  TokenType identifierType();
  TokenType checkKeyword(int start, int length, const char* rest, TokenType type);

 private:
  /** Start of characters for the current token */
  const char* m_start{};
  /** Next character to consume */
  const char* m_current{};
  int line;
};
}  // namespace cclox