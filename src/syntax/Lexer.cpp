#include <stdexcept>
#include <istream>

#include "Lexer.h"

namespace Sunda::Syntax {
Lexer::Lexer(std::basic_istream<char> *stream) :
    stream(stream),
    current_pos(0) {
  next_char();
}

Token Lexer::next_token() {
  printf("Char %d\n", current_char());
  switch (current_char()) {
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':consume_number();
      break;
    case '"':consume_string();
      break;
    case 'v':break;
    case '\n':column_number = 0;
      line_number++;

      next_char();
      break;
    case '\r':
      if (next_char() == '\n') {
        column_number = 0;
        line_number++;

        next_char();
      } else {
        throw std::runtime_error("Expected char \\n");
      }
      break;
    case '\0':token.type = Token::Type::EndOfFile;
      break;
    default:throw std::runtime_error("Unrecognized char");
  }
  return token;
}

void Lexer::skip_one_or_more_whitespace() {
  expect_next_char([this](char c) {
    return is_whitespace(c);
  });
  skip_whitespace();
}

void Lexer::skip_whitespace() {
  while (is_whitespace(next_char()));
}

inline char Lexer::current_char() const {
  return _current_char;
}

inline char Lexer::next_char() {
  current_pos += 1;
  _current_char = stream->get();
  return current_char();
}

inline char Lexer::peek_char() {
  return stream->peek();
}

void Lexer::expect_next_char(const std::function<bool(char)> &f) {
  if (!f(next_char())) {
    throw std::runtime_error("Expecting char");
  }
}

void Lexer::consume_ident(std::iostream::pos_type start) {
  std::string ident;

  token.type = Token::Type::Identifier;
  token.value = ident;
}

void Lexer::check_ident_or_keyword(std::iostream::pos_type start) {

}

std::string Lexer::string_range(std::iostream::pos_type start_pos) {
  return string_range(start_pos, current_pos);
}

std::string Lexer::string_range(std::iostream::pos_type start_pos, std::iostream::pos_type end) {
  stream->seekg(start_pos);
  std::string container;
  stream->read(&container[0], end - start_pos);
  return container;
}

// TODO
// Escape, UTF-8 and other thing
void Lexer::consume_string() {
  std::string string;

  while (next_char() != '"') {
    string += current_char();
  }

  next_char();

  token.type = Token::Type::String;
  token.value = string;
}

void Lexer::consume_number() {
  std::string number;
  number += current_char();

  while (is_number(next_char())) {
    number += current_char();
  }

  token.type = Token::Type::Integer;
  token.value = number;
}

bool Lexer::is_whitespace(char c) {
  switch (c) {
    case ' ':
    case '\t':return true;
    default:return false;
  }
}

inline bool Lexer::is_number(char c) {
  return isdigit(c);
}

void Lexer::expect_next_char(char c) {
  if (next_char() != c) {
    throw std::runtime_error("Expecting c");
  }
}

}
