#include <stdexcept>
#include <istream>
#include <iostream> // debug

#include "Lexer.h"
#include "../Type.h"

namespace Sunda::Syntax {
Lexer::Lexer(std::basic_istream<char> *stream) :
    stream(stream),
    current_pos(0),
    column_number(1),
    line_number(1) {
  _current_char = stream->get();
  if (stream->eof()) {
    stream->clear(std::ios_base::eofbit);
    _current_char = '\0';
  }
}

Token Lexer::next_token() {
  auto start = current_pos;

  switch (current_char()) {
    case ' ':
    case '\t': {
      consume_whitespace();
      break;
    }
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9': {
      consume_number();
      break;
    }
    case '"': {
      consume_string();
      break;
    }
      /// Regular char
      // fn
    case 'f':
      if (next_char() == 'n') {
        check_ident_or_keyword(Token::Type::Function, start);
      } else {
        consume_ident(start);
      }
      break;
      // struct
    case 's': {
      if (next_char() == 't' && next_char() == 'r' && next_char() == 'u') {
        check_ident_or_keyword(Token::Type::Struct, start);
      } else {
        consume_ident(start);
      }
      break;
    }
      // var
    case 'v': {
      if (next_char() == 'a' && next_char() == 'r') {
        check_ident_or_keyword(Token::Type::Var, start);
      } else {
        consume_ident(start);
      }
    }
    case 'a':
    case 'b':
    case 'c':
    case 'd':
    case 'e':
    case 'g':
    case 'h':
    case 'i':
    case 'j':
    case 'k':
    case 'l':
    case 'm':
    case 'n':
    case 'o':
    case 'p':
    case 'q':
    case 'r':
    case 't':
    case 'u':
    case 'w':
    case 'x':
    case 'y':
    case 'z': {
      consume_ident(start);
      break;
    }
      /// Symbol start
    case ':': {
      return single_symbol(Token::Type::Colon);
    }
    case ';': {
      return single_symbol(Token::Type::Semicolon);
    }
    case '[': {
      return single_symbol(Token::Type::OpenSquareBracket);
    }
    case ']': {
      return single_symbol(Token::Type::CloseSquareBracket);
    }
    case '{': {
      return single_symbol(Token::Type::OpenCurlyBraces);
    }
    case '}': {
      return single_symbol(Token::Type::CloseCurlyBraces);
    }
    case '(': {
      return single_symbol(Token::Type::OpenParenthesis);
    }
    case ')': {
      return single_symbol(Token::Type::CloseParenthesis);
    }
      //// Operator
    case '!': {
      return single_symbol(Token::Type::OpNegate);
    }
    case '~': {
      return single_symbol(Token::Type::OpBinNegate);
    }
    case '|': {
      return single_symbol(Token::Type::OpBinOr);
    }
    case '&': {
      return single_symbol(Token::Type::OpBinAnd);
    }
    case '^': {
      return single_symbol(Token::Type::OpBinXor);
    }
    case '*': {
      return single_symbol(Token::Type::OpMul);
    }
    case '%': {
      return single_symbol(Token::Type::OpMod);
    }
    case '/': {
      return single_symbol(Token::Type::OpDiv);
    }
    case '+': {
      // Positive number care with number
      return single_symbol(Token::Type::OpAdd);
    }
    case '-': {
      char next_char_ = next_char();
      if (next_char_ == '>') {
        return single_symbol(Token::Type::Returning);
      } else {
        switch (next_char_) {
          case '0':
          case '1':
          case '2':
          case '3':
          case '4':
          case '5':
          case '6':
          case '7':
          case '8':
          case '9':
            // Negative number
            break;
          default: {
            return single_symbol(Token::Type::OpSub);
          }
        }
      }
    }
    case '\n': {
      column_number = 0;
      line_number += 1;

      next_char();
      break;
    }
    case '\r':
      if (next_char() == '\n') {
        column_number = 0;
        line_number += 1;

        next_char();
      } else {
        throw std::runtime_error("Expected char \\n");
      }
      break;
    case '\0': {
      return single_symbol(Token::Type::EndOfFile);
    }
    default: {
      std::cout << "Char is " << current_char() << ", Ord " << (int) current_char() << ", Pos " << current_pos << '\n';
      std::cout << "Is good " << stream->good() << '\n';
      std::cout << "Is eof " << stream->eof() << '\n';
      std::cout << "Is bad " << stream->bad() << '\n';
      std::cout << "Is fail " << stream->fail() << '\n';
      throw std::runtime_error("Unrecognized char");
    }
  }
  return token;
}

Token Lexer::single_symbol(Token::Type type) {
  Token token{
      .type = type,
      .value = nullptr
  };

  next_char();

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
  column_number += 1;
  current_pos += 1;
  _current_char = stream->get();

  if (stream->eof()) {
    stream->clear(std::ios_base::eofbit);
    _current_char = '\0';
  }

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

  token.type = Token::Type::Identifier;
  token.value = string_range(start, current_pos);
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
  move_stream_to(start_pos);

  std::string container(end - start_pos, '\0');
  stream->read(container.data(), end - start_pos);

  move_stream_to(current_pos + (std::iostream::pos_type) 1);

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

//  Token token;
  token.type = Token::Type::Integer;
  token.value = number;
//  return std::move(token);
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

u32 Lexer::get_line_number() {
  return line_number;
}

u32 Lexer::get_column_number() {
  return column_number;
}

}
