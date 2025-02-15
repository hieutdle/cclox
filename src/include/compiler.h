#pragma once

#include <string_view>
#include "chunk.h"
#include "parser.h"
#include "scanner.h"

namespace cclox {
class Compiler {
 public:
  Parser parser;
  Scanner scanner;
  Chunk* compilingChunk;

  bool compile(std::string_view source, Chunk* chunk);
  void advance();
  void errorAtCurrent(std::string_view message);
  void error(const std::string_view message);
  void errorAt(Token* token, std::string_view message);
  void consume(TokenType type, const std::string_view message);
  void emitByte(uint8_t byte);
};
}  // namespace cclox