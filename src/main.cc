#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include "debug.h"
#include "vm.h"

namespace cclox {
void runTest() {
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

void repl() {
  VM vm;
  std::string line;
  while (true) {
    std::cout << "> ";                    // Print prompt
    if (!std::getline(std::cin, line)) {  // Read input safely
      std::cout << std::endl;
      break;
    }
    if (line == "exit") break;
    vm.interpret(line);
    // Pass input to interpret function
  }
}

std::string readFile(const std::string& path) {
  std::ifstream file(path, std::ios::binary);  // Open file in binary mode
  if (!file) {
    std::cerr << "Could not open file \"" << path << "\".\n";
    std::exit(74);
  }

  file.seekg(0, std::ios::end);  // Move to end to get file size
  std::size_t fileSize = file.tellg();
  file.seekg(0, std::ios::beg);  // Move back to the beginning

  // Allocate memory
  std::vector<char> buffer(fileSize + 1);  // +1 for null terminator
  if (buffer.empty()) {
    std::cerr << "Not enough memory to read \"" << path << "\".\n";
    std::exit(74);
  }

  // Read file contents
  file.read(buffer.data(), fileSize);
  if (file.gcount() < static_cast<std::streamsize>(fileSize)) {
    std::cerr << "Could not read file \"" << path << "\".\n";
    std::exit(74);
  }

  buffer[fileSize] = '\0';            // Null-terminate the string
  return std::string(buffer.data());  // Convert to std::string
}

void runFile(const std::string& path) {
  std::string source = readFile(path);
  VM vm;
  InterpretResult result = vm.interpret(source);  // Assume interpret() exists

  if (result == INTERPRET_COMPILE_ERROR) {
    std::exit(65);  // Standard C++ exit
  }
  if (result == INTERPRET_RUNTIME_ERROR) {
    std::exit(70);
  }
}
}  // namespace cclox

int main(int argc, char* argv[]) {
  if (argc == 1) {
    cclox::repl();
  } else if (argc == 2) {
    if (std::strcmp(argv[1], "test") == 0) {
      cclox::runTest();
    } else {
      cclox::runFile(argv[1]);
    }
  } else {
    std::cerr << "Usage: clox [path|test]" << std::endl;
    std::exit(64);
  }
}