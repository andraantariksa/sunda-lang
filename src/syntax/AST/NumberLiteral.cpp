#include <stdexcept>
#include <boost/lexical_cast.hpp>
#include <boost/variant.hpp>

#include "../../Type.h"
#include "NumberLiteral.h"

namespace Sunda::Syntax::AST {

boost::variant<ALL_NUMBER_PRIMITIVE_TYPE> NumberLiteral::to_integer_variant() {
  boost::variant<ALL_NUMBER_PRIMITIVE_TYPE> ret;
  switch (type) {
    case Type::u8:ret = to_integer<u8>();
      break;
    case Type::u16:ret = to_integer<u16>();
      break;
    case Type::u32:ret = to_integer<u32>();
      break;
    case Type::u64:ret = to_integer<u64>();
      break;
    case Type::i8:ret = to_integer<i8>();
      break;
    case Type::i16:ret = to_integer<i16>();
      break;
    case Type::i32:ret = to_integer<i32>();
      break;
    case Type::i64:ret = to_integer<i64>();
      break;
    default:throw std::runtime_error("No such integer type exists!");
  }
  return ret;
}

template<typename T, typename>
inline T NumberLiteral::to_integer() {
  return boost::lexical_cast<T>(value);
}

}
