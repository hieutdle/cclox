#include <string>

namespace cclox {
class Compiler {
 public:
  void compile(std::string_view source);
};
}  // namespace cclox