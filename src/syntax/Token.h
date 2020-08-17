#ifndef SUNDA_LANG_SRC_TOKEN_H_
#define SUNDA_LANG_SRC_TOKEN_H_

#include <string>

#include <boost/variant.hpp>

#include "../Type.h"

namespace Sunda::Syntax {
class Token {
 public:
  enum class Type {
    EndOfFile,
    Newline, // \n, \r\n
    Whitespace, //  , \t
    Comment,
    Identifier,
    OpenParenthesis,  // (
    CloseParenthesis, // )
    OpenCurlyBraces,  // {
    CloseCurlyBraces, // }

    // Keyword
    Returning, // ->
    Var,       // var
    Colon,     // :
    Semicolon, // ;
    Function,  // fn
    True,      // true
    False,     // false

    // Primitive
    Integer,
    String,

    // Op
    OpNotEq,  // !=
    OpEq,     // ==
    OpAssign, // =
    OpAdd,    // +
    OpSub,    // -
    OpMod,    // %
    OpDiv,    // /
    OpMul,    // *
    OpNot,    // !
    OpGT,     // >
    OpGTE,    // >=
    OpLT,     // <
    OpLTE,    // <=
  };

  Type type;
  boost::variant<std::string, char, nullptr_t> value;

 private:
  u32 line_number;
  u32 column_number;
  std::string filename;
};

}

#endif //SUNDA_LANG_SRC_TOKEN_H_
