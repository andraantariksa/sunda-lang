#ifndef SUNDA_LANG_SRC_SYNTAX_AST_NUMBERLITERAL_H_
#define SUNDA_LANG_SRC_SYNTAX_AST_NUMBERLITERAL_H_

#include "../../Type.h"
#include "../Token.h"
#include "../AST.h"

#define ALL_NUMBER_PRIMITIVE_TYPE_U Sunda::u8, Sunda::u16, Sunda::u32, Sunda::u64
#define ALL_NUMBER_PRIMITIVE_TYPE_I Sunda::i8, Sunda::i16, Sunda::i32, Sunda::i64
#define ALL_NUMBER_PRIMITIVE_TYPE ALL_NUMBER_PRIMITIVE_TYPE_I, ALL_NUMBER_PRIMITIVE_TYPE_U

namespace Sunda::Syntax::AST {

class NumberLiteral : Sunda::Syntax::ASTNode {
 public:
  enum class Type {
    u8,
    u16,
    u32,
    u64,
    i8,
    i16,
    i32,
    i64,
  };

  boost::variant<ALL_NUMBER_PRIMITIVE_TYPE> to_integer_variant();
  template<
      typename T,
      typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type
  >
  T to_integer();

  std::string value;
  Type type;
};

}

#endif //SUNDA_LANG_SRC_SYNTAX_AST_NUMBERLITERAL_H_
