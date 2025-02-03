#pragma once

#include <string_view>
#include "chunk.h"

namespace cclox {

void disassembleChunk(Chunk* chunk, std::string_view name);
int disassembleInstruction(Chunk* chunk, int offset);
}  // namespace cclox