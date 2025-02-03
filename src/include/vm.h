#include <stack>
#include <vector>
#include "chunk.h"
#include "value.h"

namespace cclox {

enum InterpretResult { INTERPRET_OK, INTERPRET_COMPILE_ERROR, INTERPRET_RUNTIME_ERROR };

class VM {
 public:
  InterpretResult interpret(Chunk* chunk);
  InterpretResult run();

  void printStack(std::stack<Value> stack);
  uint8_t read_byte();
  Value read_constant();

 private:
  Chunk* chunk;
  std::vector<uint8_t>::const_iterator ip;

  std::stack<Value> stack;
};

}  // namespace cclox