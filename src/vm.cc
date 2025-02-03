#include "vm.h"
#include <iostream>
#include "debug.h"

namespace cclox {
InterpretResult VM::interpret(Chunk* chunk) {
  this->chunk = chunk;
  this->ip = this->chunk->code.begin();
  return run();
}

void VM::printStack(std::stack<Value> stack) {
  std::vector<Value> temp;

  while (!stack.empty()) {
    temp.push_back(stack.top());
    stack.pop();
  }

  std::cout << "          ";

  // Print elements in original order
  for (auto it = temp.rbegin(); it != temp.rend(); ++it) {  // Reverse iterate
    std::cout << "[ ";
    std::cout << *it;
    std::cout << " ]";
  }

  std::cout << std::endl;
}

InterpretResult VM::run() {
  for (;;) {
#ifdef DEBUG_TRACE_EXECUTION
    std::cout << "Debug trace: " << std::endl;
    printStack(stack);
    disassembleInstruction(this->chunk, ip - this->chunk->code.begin());
#endif

    uint8_t instruction = read_byte();
    switch (instruction) {
      case OP_NEGATE: {
        Value value = stack.top();
        stack.pop();
        stack.push(-value);
        break;
      }
      case OP_RETURN:
        stack.pop();
        return INTERPRET_OK;
      case OP_CONSTANT: {
        Value constant = read_constant();
        stack.push(constant);
        break;
      }
      default:
        std::cout << "Unknown opcode " << static_cast<int>(instruction) << std::endl;
        return INTERPRET_RUNTIME_ERROR;
    }
  }
}

uint8_t VM::read_byte() {
  uint8_t byte = *ip;
  ip++;
  return byte;
}

Value VM::read_constant() { return this->chunk->constants[read_byte()]; }

}  // namespace cclox