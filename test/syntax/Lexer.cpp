#include <iostream>
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

TEST(LexerTest, EmptyStringLiteral) {
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

TEST(LexerTest, Function) {
  std::stringstream ss("fn main() -> () {}");
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

  Sunda::Syntax::Token token4 = lex.next_token();
  ASSERT_EQ(token4.type, Sunda::Syntax::Token::Type::OpenParenthesis);
  ASSERT_EQ(boost::get<nullptr_t>(token4.value), nullptr);

  Sunda::Syntax::Token token5 = lex.next_token();
  ASSERT_EQ(token5.type, Sunda::Syntax::Token::Type::CloseParenthesis);
  ASSERT_EQ(boost::get<nullptr_t>(token5.value), nullptr);

  lex.next_token(); // ws

  Sunda::Syntax::Token token6 = lex.next_token();
  ASSERT_EQ(token6.type, Sunda::Syntax::Token::Type::Returning);
  ASSERT_EQ(boost::get<nullptr_t>(token6.value), nullptr);

  lex.next_token(); // ws
  lex.next_token(); // (
  lex.next_token(); // )
  lex.next_token(); // ws

  Sunda::Syntax::Token token7 = lex.next_token();
  ASSERT_EQ(token7.type, Sunda::Syntax::Token::Type::OpenCurlyBraces);
  ASSERT_EQ(boost::get<nullptr_t>(token7.value), nullptr);

  Sunda::Syntax::Token token8 = lex.next_token();
  ASSERT_EQ(token8.type, Sunda::Syntax::Token::Type::CloseCurlyBraces);
  ASSERT_EQ(boost::get<nullptr_t>(token8.value), nullptr);
}

TEST(LexerTest, Keyword_fn_incomplete) {
  std::stringstream ss("f");
  Sunda::Syntax::Lexer lex(&ss);
  Sunda::Syntax::Token token1 = lex.next_token();
  ASSERT_EQ(token1.type, Sunda::Syntax::Token::Type::Identifier);
  ASSERT_EQ(boost::get<std::string>(token1.value), "f");

  Sunda::Syntax::Token token2 = lex.next_token();
  ASSERT_EQ(token2.type, Sunda::Syntax::Token::Type::EndOfFile);
  ASSERT_EQ(boost::get<nullptr_t>(token2.value), nullptr);
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

TEST(LexerTest, ColumnNumber) {
  std::stringstream ss("12345     gx");
  Sunda::Syntax::Lexer lex(&ss);
  lex.next_token();
  lex.next_token();
  ASSERT_EQ(lex.get_column_number(), 11);
  ASSERT_EQ(lex.get_line_number(), 1);
}

TEST(LexerTest, EmptyInput) {
  std::stringstream ss("");
  Sunda::Syntax::Lexer lex(&ss);
  ASSERT_EQ(lex.get_column_number(), 1);
  ASSERT_EQ(lex.get_line_number(), 1);
  Sunda::Syntax::Token token = lex.next_token();
  ASSERT_EQ(token.type, Sunda::Syntax::Token::Type::EndOfFile);
  ASSERT_EQ(token.type, Sunda::Syntax::Token::Type::EndOfFile);
}

TEST(LexerTest, LineNumber) {
  std::stringstream ss("\n\r\n\n");
  Sunda::Syntax::Lexer lex(&ss);
  lex.next_token();
  lex.next_token();
  lex.next_token();
  ASSERT_EQ(lex.get_column_number(), 1);
  ASSERT_EQ(lex.get_line_number(), 4);
}
