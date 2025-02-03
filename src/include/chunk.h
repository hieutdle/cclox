#pragma once

#include <cstdint>
#include <vector>
#include "value.h"

namespace cclox {

enum OpCode : uint8_t {
  OP_NEGATE,
  OP_CONSTANT,
  OP_RETURN,
};

class Chunk {
 public:
  Chunk();
  ~Chunk();

  void writeChunk(uint8_t byte, int line);
  int addConstant(Value value);

  std::vector<uint8_t> code;
  int count;
  int capacity;
  ValueArray constants;
  std::vector<int> lines;
};
}  // namespace cclox