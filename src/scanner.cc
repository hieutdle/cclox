#include "scanner.h"
#include <cstring>

namespace cclox {
Scanner::Scanner(std::string_view source) : m_start(source.data()), m_current(source.data()), line(1) {}

Token Scanner::scanToken() {
  skipWhitespace();
  this->m_start = this->m_current;
  if (isAtEnd()) {
    return makeToken(TokenType::TOKEN_EOF);
  }

  char c = advance();

  if (isDigit(c)) return number();
  if (isAlpha(c)) return identifier();

  switch (c) {
    case '(':
      return makeToken(TokenType::TOKEN_LEFT_PAREN);
    case ')':
      return makeToken(TokenType::TOKEN_RIGHT_PAREN);
    case '{':
      return makeToken(TokenType::TOKEN_LEFT_BRACE);
    case '}':
      return makeToken(TokenType::TOKEN_RIGHT_BRACE);
    case ';':
      return makeToken(TokenType::TOKEN_SEMICOLON);
    case ',':
      return makeToken(TokenType::TOKEN_COMMA);
    case '.':
      return makeToken(TokenType::TOKEN_DOT);
    case '-':
      return makeToken(TokenType::TOKEN_MINUS);
    case '+':
      return makeToken(TokenType::TOKEN_PLUS);
    case '/':
      return makeToken(TokenType::TOKEN_SLASH);
    case '*':
      return makeToken(TokenType::TOKEN_STAR);
    case '!':
      return makeToken(match('=') ? TokenType::TOKEN_BANG_EQUAL : TokenType::TOKEN_BANG);
    case '=':
      return makeToken(match('=') ? TokenType::TOKEN_EQUAL_EQUAL : TokenType::TOKEN_EQUAL);
    case '<':
      return makeToken(match('=') ? TokenType::TOKEN_LESS_EQUAL : TokenType::TOKEN_LESS);
    case '>':
      return makeToken(match('=') ? TokenType::TOKEN_GREATER_EQUAL : TokenType::TOKEN_GREATER);
    case '"':
      return string();
  }

  return errorToken("Unexpected character.");
}

bool Scanner::isAtEnd() { return *m_current == '\0'; }

Token Scanner::makeToken(TokenType type) { return Token{type, m_start, static_cast<int>(m_current - m_start), line}; }

Token Scanner::errorToken(const char* message) {
  return Token{TokenType::TOKEN_ERROR, message, static_cast<int>(strlen(message)), line};
}

char Scanner::advance() {
  m_current++;
  return m_current[-1];
}

bool Scanner::match(char expected) {
  if (isAtEnd()) return false;
  if (*m_current != expected) return false;

  m_current++;
  return true;
}

void Scanner::skipWhitespace() {
  while (true) {
    char c = peek();
    switch (c) {
      case ' ':
      case '\r':
      case '\t':
        advance();
        break;
      case '\n':
        this->line++;
        advance();
        break;
      case '/':
        if (peekNext() == '/') {
          // A comment goes until the end of the line.
          while (peek() != '\n' && !isAtEnd()) advance();
        } else {
          return;
        }
        break;
      default:
        return;
    }
  }
}

char Scanner::peek() { return *m_current; }

char Scanner ::peekNext() {
  if (isAtEnd()) return '\0';
  return m_current[1];
}

Token Scanner::string() {
  while (peek() != '"' && !isAtEnd()) {
    if (peek() == '\n') this->line++;
    advance();
  }

  if (isAtEnd()) return errorToken("Unterminated string.");

  // The closing quote.
  advance();
  return makeToken(TokenType::TOKEN_STRING);
}

bool Scanner::isDigit(char c) { return c >= '0' && c <= '9'; }

Token Scanner::number() {
  while (isDigit(peek())) advance();

  // Look for a fractional part.
  if (peek() == '.' && isDigit(peekNext())) {
    // Consume the "."
    advance();

    while (isDigit(peek())) advance();
  }

  return makeToken(TokenType::TOKEN_NUMBER);
}

bool Scanner::isAlpha(char c) { return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_'; }

Token Scanner::identifier() {
  while (isAlpha(peek()) || isDigit(peek())) advance();

  return makeToken(identifierType());
}

TokenType Scanner::identifierType() {
  switch (m_start[0]) {
    case 'a':
      return checkKeyword(1, 2, "nd", TokenType::TOKEN_AND);
    case 'c':
      return checkKeyword(1, 4, "lass", TokenType::TOKEN_CLASS);
    case 'e':
      return checkKeyword(1, 3, "lse", TokenType::TOKEN_ELSE);
    case 'f':
      if (this->m_current - this->m_start > 1) {
        switch (this->m_start[1]) {
          case 'a':
            return checkKeyword(2, 3, "lse", TokenType::TOKEN_FALSE);
          case 'o':
            return checkKeyword(2, 1, "r", TokenType::TOKEN_FOR);
          case 'u':
            return checkKeyword(2, 1, "n", TokenType::TOKEN_FUN);
        }
      }
      break;
    case 'i':
      return checkKeyword(1, 1, "f", TokenType::TOKEN_IF);
    case 'n':
      return checkKeyword(1, 2, "il", TokenType::TOKEN_NIL);
    case 'o':
      return checkKeyword(1, 1, "r", TokenType::TOKEN_OR);
    case 'p':
      return checkKeyword(1, 4, "rint", TokenType::TOKEN_PRINT);
    case 'r':
      return checkKeyword(1, 5, "eturn", TokenType::TOKEN_RETURN);
    case 's':
      return checkKeyword(1, 4, "uper", TokenType::TOKEN_SUPER);
    case 't':
      if (this->m_current - this->m_start > 1) {
        switch (this->m_start[1]) {
          case 'h':
            return checkKeyword(2, 2, "is", TokenType::TOKEN_THIS);
          case 'r':
            return checkKeyword(2, 2, "ue", TokenType::TOKEN_TRUE);
        }
      }
    case 'v':
      return checkKeyword(1, 2, "ar", TokenType::TOKEN_VAR);
    case 'w':
      return checkKeyword(1, 4, "hile", TokenType::TOKEN_WHILE);
  }

  return TokenType::TOKEN_IDENTIFIER;
}

TokenType Scanner::checkKeyword(int start, int length, const char* rest, TokenType type) {
  if (m_current - m_start == start + length && std::memcmp(m_start + start, rest, length) == 0) {
    return type;
  }

  return TokenType::TOKEN_IDENTIFIER;
}
}  // namespace cclox