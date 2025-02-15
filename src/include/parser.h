#pragma once

#include "token.h"

namespace cclox {
class Parser {
 public:
  Token current;
  Token previous;
  bool hadError;
  bool panicMode;
};
}  // namespace cclox