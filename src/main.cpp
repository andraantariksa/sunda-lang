#define PROJECT_NAME "Sunda"
#define PROJECT_VERSION "0.0.1"

#include <cstdio>
#include <structopt/structopt.hpp>

#include "Type.h"
#include "syntax/Token.h"
#include "syntax/Lexer.h"

struct Args {
  std::optional<bool> version = false;
  std::vector<std::string> files;
};
STRUCTOPT (Args, version, files);

int main(int argc, char **argv) {
  try {
    auto args = structopt::app(PROJECT_NAME, PROJECT_VERSION).parse<Args>(argc, argv);
    if (args.version.has_value() && args.version.value()) {
      printf("%s %s\n", PROJECT_NAME, PROJECT_VERSION);
    } else {

    }
  } catch (structopt::exception &e) {
    printf("%s\n%s\n", e.what(), e.help());
  }
  return 0;
}
