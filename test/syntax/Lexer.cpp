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

TEST(LexerTest, Keyword_fn) {
  std::stringstream ss("fn main");
  Sunda::Syntax::Lexer lex(&ss);
  Sunda::Syntax::Token token1 = lex.next_token();
  ASSERT_EQ(token1.type, Sunda::Syntax::Token::Type::Function);
  ASSERT_EQ(boost::get<nullptr_t>(token1.value), nullptr);

  Sunda::Syntax::Token token2 = lex.next_token();
  ASSERT_EQ(token2.type, Sunda::Syntax::Token::Type::Whitespace);
  ASSERT_EQ(boost::get<nullptr_t>(token2.value), nullptr);

  Sunda::Syntax::Token token3 = lex.next_token();
  ASSERT_EQ(token3.type, Sunda::Syntax::Token::Type::Identifier);
  ASSERT_EQ(boost::get<std::string>(token3.value), "main");
}

TEST(LexerTest, Identifier_fna) {
  std::stringstream ss("fna");
  Sunda::Syntax::Lexer lex(&ss);
  Sunda::Syntax::Token token = lex.next_token();
  ASSERT_EQ(token.type, Sunda::Syntax::Token::Type::Identifier);
  ASSERT_EQ(boost::get<std::string>(token.value), "fna");
}

TEST(LexerTest, Identifier_fga) {
  std::stringstream ss("fga");
  Sunda::Syntax::Lexer lex(&ss);
  Sunda::Syntax::Token token = lex.next_token();
  ASSERT_EQ(token.type, Sunda::Syntax::Token::Type::Identifier);
  ASSERT_EQ(boost::get<std::string>(token.value), "fga");
}
