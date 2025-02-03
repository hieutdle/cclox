#include "debug.h"
#include "vm.h"

namespace cclox {
void run() {
  VM vm;
  Chunk chunk;
  int constant = chunk.addConstant(1.2);
  chunk.writeChunk(OP_CONSTANT, 123);
  chunk.writeChunk(constant, 123);
  constant = chunk.addConstant(3.4);
  chunk.writeChunk(OP_CONSTANT, 123);
  chunk.writeChunk(constant, 123);

  chunk.writeChunk(OP_ADD, 123);

  constant = chunk.addConstant(5.6);
  chunk.writeChunk(OP_CONSTANT, 123);
  chunk.writeChunk(constant, 123);

  chunk.writeChunk(OP_DIVIDE, 123);
  chunk.writeChunk(OP_NEGATE, 123);
  chunk.writeChunk(OP_RETURN, 123);
  disassembleChunk(&chunk, "test chunk");
  vm.interpret(&chunk);
}
}  // namespace cclox

int main() {
  cclox::run();
  return 0;
}
