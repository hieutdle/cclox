#include "compiler.h"
#include <iostream>

namespace cclox {

bool Compiler::compile(std::string_view source, Chunk* chunk) {
  scanner = Scanner(source);
  parser = Parser();
  this->compilingChunk = chunk;

  parser.hadError = false;
  parser.panicMode = false;

  advance();
  expression();
  consume(TokenType::TOKEN_EOF, "Expect end of expression.");
  return !parser.hadError;
}

void Compiler::advance() {
  parser.current = parser.previous;

  while (true) {
    parser.current = scanner.scanToken();
    if (parser.current.type != TokenType::TOKEN_ERROR) break;

    errorAtCurrent(parser.current.start);
  }
}

void Compiler::errorAtCurrent(std::string_view message) { errorAt(&parser.current, message); }
void Compiler::error(const std::string_view message) { errorAt(&parser.previous, message); }
void Compiler::errorAt(Token* token, std::string_view message) {
  if (parser.panicMode) return;
  parser.panicMode = true;
  std::cerr << "[line " << token->line << "] Error";
  if (token->type == TokenType::TOKEN_EOF) {
    std::cerr << " at end";
  } else if (token->type == TokenType::TOKEN_ERROR) {
    // Nothing.
  } else {
    std::cerr << " at '" << std::string_view(token->start, token->length) << "'";
  }
  std::cerr << ": " << message << "\n";
  parser.hadError = true;
}

void Compiler::consume(TokenType type, std::string_view message) {
  if (parser.current.type == type) {
    advance();
    return;
  }

  errorAtCurrent(message);
}

void Compiler::emitByte(uint8_t byte) { compilingChunk->writeChunk(byte, parser.previous.line); }  // namespace cclox