#ifndef SUNDA_LANG_SRC_LOCATION_H_
#define SUNDA_LANG_SRC_LOCATION_H_

#include <string>

#include "../Type.h"

namespace Sunda::Syntax {

class Location {
 public:
  std::string filename;
  u32 line_number;
  u32 column_number;
};

}

#endif //SUNDA_LANG_SRC_LOCATION_H_
