#include "debug.h"
#include <iomanip>
#include <iostream>

namespace cclox {

void disassembleChunk(Chunk* chunk, std::string_view name) {
  std::cout << "=== " << name << " ===" << std::endl;
  for (int offset = 0; offset < chunk->code.size();) {
    offset = disassembleInstruction(chunk, offset);
  }
}

static int simpleInstruction(std::string_view name, int offset) {
  std::cout << name << std::endl;
  return offset + 1;
}

static int constantInstruction(std::string_view name, Chunk* chunk, int offset) {
  int constant = chunk->code[offset + 1];
  std::cout << name << " " << constant << " '" << chunk->constants[constant] << "'" << std::endl;
  return offset + 2;
}

int disassembleInstruction(Chunk* chunk, int offset) {
  std::cout << std::setw(4) << std::setfill('0') << offset << " ";

  if (offset > 0 && chunk->lines[offset] == chunk->lines[offset - 1]) {
    std::cout << "  | ";
  } else {
    std::cout << chunk->lines[offset] << " ";
  }

  uint8_t instruction = chunk->code[offset];

  switch (instruction) {
    case OP_ADD:
      return simpleInstruction("OP_ADD", offset);
    case OP_SUBTRACT:
      return simpleInstruction("OP_SUBTRACT", offset);
    case OP_MULTIPLY:
      return simpleInstruction("OP_MULTIPLY", offset);
    case OP_DIVIDE:
      return simpleInstruction("OP_DIVIDE", offset);
    case OP_NEGATE:
      return simpleInstruction("OP_NEGATE", offset);
    case OP_RETURN:
      return simpleInstruction("OP_RETURN", offset);
    case OP_CONSTANT:
      return constantInstruction("OP_CONSTANT", chunk, offset);
    default:
      std::cout << "Unknown opcode " << static_cast<int>(instruction) << std::endl;
      return offset + 1;
  }
}

}  // namespace cclox
