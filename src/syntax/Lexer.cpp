#include <stdexcept>
#include <istream>
#include <iostream> // debug

#include "Lexer.h"

namespace Sunda::Syntax {
Lexer::Lexer(std::basic_istream<char> *stream) :
    stream(stream),
    current_pos(-1) {
  next_char();
}

Token Lexer::next_token() {
  auto start = current_pos;

  switch (current_char()) {
    case ' ':
    case '\t':consume_whitespace();
      break;
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
      // fn
    case 'f':
      if (next_char() == 'n') {
        check_ident_or_keyword(Token::Type::Function, start);
      } else {
        consume_ident(start);
      }
      break;
    case 'm':consume_ident(start);
      break;
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
  consume_whitespace();
}

void Lexer::consume_whitespace() {
  while (is_whitespace(next_char())) {
  };
  token.type = Token::Type::Whitespace;
  token.value = nullptr;
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

inline void Lexer::move_stream_to(std::iostream::pos_type pos) {
  stream->seekg(pos);
}

void Lexer::consume_ident(std::iostream::pos_type start) {
  while (is_ident_part(current_char())) {
    next_char();
  }

  auto prev_current_pos = current_pos - (std::iostream::pos_type) 1;

  token.type = Token::Type::Identifier;
  token.value = string_range(start, prev_current_pos);
}

void Lexer::check_ident_or_keyword(Token::Type type, std::iostream::pos_type start) {
  if (is_ident_part_or_end(peek_char())) {
    consume_ident(start);
  } else {
    next_char();
    token.type = type;
    token.value = nullptr;
  }
}

std::string Lexer::string_range(std::iostream::pos_type start_pos) {
  return string_range(start_pos, current_pos);
}

std::string Lexer::string_range(std::iostream::pos_type start_pos, std::iostream::pos_type end) {
  stream->clear(); // CARE

  move_stream_to(start_pos);

  std::string container(end - start_pos + 1, '\0');
  stream->read(container.data(), end - start_pos + 1);

  move_stream_to(current_pos);

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

// TODO
// Add unicode support?
inline bool Lexer::is_ident_part_start(char c) {
  return isalpha(c) || c == '_';
}

inline bool Lexer::is_ident_part(char c) {
  return is_ident_part_start(c) || isdigit(c);
}

// TODO
// Maybe support ? or ! in the end of identifier
bool Lexer::is_ident_part_or_end(char c) {
  return is_ident_part(c);
}

}
