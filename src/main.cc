#include "debug.h"

namespace cclox {
void run() {
  Chunk chunk;
  int constant = chunk.addConstant(1.2);
  chunk.writeChunk(OP_CONSTANT, 123);
  chunk.writeChunk(constant, 123);
  int second_constant = chunk.addConstant(2.5);
  chunk.writeChunk(OP_CONSTANT, 123);
  chunk.writeChunk(second_constant, 123);
  chunk.writeChunk(OP_RETURN, 123);
  disassembleChunk(&chunk, "test chunk");
}
}  // namespace cclox

int main() {
  cclox::run();
  return 0;
}
