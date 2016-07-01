// Copyright (c) 2010
// All rights reserved.

#include <stdexcept>
#include "Out.hh"
#include "SpeedOut.hh"
#include "JsonOut.hh"

namespace meal {

Out* Out::create(int type) {
  switch (type) {
    case SPEED_OUT:
      return new SpeedOut();

    case JSON_OUT:
      return new JsonOut();

    default:
      throw std::runtime_error("Not supported out type.");
  }

  return nullptr;
}


}  // namespace meal

