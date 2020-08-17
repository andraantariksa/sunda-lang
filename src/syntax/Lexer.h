#ifndef SUNDA_LANG_LEXER_H
#define SUNDA_LANG_LEXER_H

#include <memory>
#include <functional>
#include <istream>

#include "Token.h"

namespace Sunda::Syntax {

class Lexer {
 public:
  Lexer(std::basic_istream<char> *stream);
  Token next_token();

  void skip_one_or_more_whitespace();

  [[nodiscard]] char current_char() const;
  char next_char();
  char peek_char();
  void move_stream_to(std::iostream::pos_type pos);

  void expect_next_char(const std::function<bool(char)> &f);
  void expect_next_char(char c);
  void check_ident_or_keyword(Token::Type type, std::iostream::pos_type start);
  std::string string_range(std::iostream::pos_type start);
  std::string string_range(std::iostream::pos_type start, std::iostream::pos_type end);

  void consume_whitespace();
  void consume_ident(std::iostream::pos_type start);
  void consume_number();
  void consume_string();

  bool is_whitespace(char c);
  bool is_number(char c);
  bool is_ident_part(char c);
  bool is_ident_part_start(char c);
  bool is_ident_part_or_end(char c);

 private:
  Token token;
  char _current_char;
  u32 line_number{};
  u32 column_number{};
  std::iostream::pos_type current_pos;
  std::string filename;
  std::basic_istream<char> *stream;
};

}

#endif //SUNDA_LANG_LEXER_H
