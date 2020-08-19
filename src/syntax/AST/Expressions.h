#ifndef SUNDA_LANG_SRC_SYNTAX_AST_EXPRESSIONS_H_
#define SUNDA_LANG_SRC_SYNTAX_AST_EXPRESSIONS_H_

#include <vector>

#include "../AST.h"

namespace Sunda::Syntax::AST {

class Expressions {
  std::vector<Sunda::Syntax::ASTNode> expressions;
};

}

#endif //SUNDA_LANG_SRC_SYNTAX_AST_EXPRESSIONS_H_
