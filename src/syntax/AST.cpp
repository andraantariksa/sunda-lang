#include <optional>
#include <utility>

#include "AST.h"

namespace Sunda::Syntax {

inline std::optional<std::string> ASTNode::get_doc() {
  return doc;
}

inline void ASTNode::set_doc(std::optional<std::string> new_doc) {
  doc = std::move(new_doc);
}

}
