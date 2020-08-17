#include <gtest/gtest.h>

#include <syntax/Lexer.h>
#include <boost/variant/get.hpp>

TEST(LexerTest, Number) {
  std::stringstream ss("123456");
  Sunda::Syntax::Lexer lex(&ss);
  Sunda::Syntax::Token token = lex.next_token();
  ASSERT_EQ(token.type, Sunda::Syntax::Token::Type::Integer);
  ASSERT_EQ(boost::get<std::string>(token.value), "123456");
}

TEST(LexerTest, EmptyString) {
  std::stringstream ss("\"\"");
  Sunda::Syntax::Lexer lex(&ss);
  Sunda::Syntax::Token token = lex.next_token();
  ASSERT_EQ(token.type, Sunda::Syntax::Token::Type::String);
  ASSERT_EQ(boost::get<std::string>(token.value), "");
}

TEST(LexerTest, BasicASCIIString) {
  std::stringstream ss("\"123abc!@#\"");
  Sunda::Syntax::Lexer lex(&ss);
  Sunda::Syntax::Token token = lex.next_token();
  ASSERT_EQ(token.type, Sunda::Syntax::Token::Type::String);
  ASSERT_EQ(boost::get<std::string>(token.value), "123abc!@#");
}
