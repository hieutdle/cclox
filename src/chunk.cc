#include "chunk.h"

namespace cclox {

Chunk::Chunk() : code({}), count{0}, capacity(0), constants({}) {}

Chunk::~Chunk() {}

void Chunk::writeChunk(uint8_t byte, int line) {
  code.push_back(byte);
  lines.push_back(line);
}

int Chunk::addConstant(Value value) {
  constants.push_back(value);
  return constants.size() - 1;
}
}  // namespace cclox