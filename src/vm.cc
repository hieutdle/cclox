#include "vm.h"
#include <iostream>
#include <string_view>
#include "compiler.h"
#include "debug.h"

namespace cclox {
InterpretResult VM::interpret(std::string_view source) {
  Compiler compiler;
  compiler.compile(source);
  return INTERPRET_OK;
}

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
  while (true) {
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
        std::cout << "Return: " << stack.top() << std::endl;
        stack.pop();
        return INTERPRET_OK;
      case OP_ADD:
        binaryOp(std::plus<Value>());
        break;
      case OP_SUBTRACT:
        binaryOp(std::minus<Value>());
        break;
      case OP_MULTIPLY:
        binaryOp(std::multiplies<Value>());
        break;
      case OP_DIVIDE:
        binaryOp(std::divides<Value>());
        break;
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

template <typename Op>
void VM::binaryOp(Op operation) {
  Value b = stack.top();
  stack.pop();
  Value a = stack.top();
  stack.pop();
  stack.push(operation(a, b));
}

uint8_t VM::read_byte() {
  uint8_t byte = *ip;
  ip++;
  return byte;
}

Value VM::read_constant() { return this->chunk->constants[read_byte()]; }

}  // namespace cclox