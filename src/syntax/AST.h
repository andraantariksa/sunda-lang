#ifndef SUNDA_LANG_SRC_AST_H_
#define SUNDA_LANG_SRC_AST_H_

#include <optional>

#include "Location.h"

namespace Sunda::Syntax {

class ASTNode {
 public:
  std::optional<std::string> get_doc();
  void set_doc(std::optional<std::string> doc);

 private:
  Location location_start;
  Location location_end;
  std::optional<std::string> doc;
};

}

#endif //SUNDA_LANG_SRC_AST_H_
