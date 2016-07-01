// Copyright (c) 2010
// All rights reserved.

#ifndef MEAL_OUT_HH
#define MEAL_OUT_HH

#include <string>
#include <fstream>

namespace meal {

enum {
  SPEED_OUT = 1,
  JSON_OUT
};

class Out {
 public:
  virtual ~Out() {}

  virtual void parse(const std::string&) = 0;

  virtual void output(std::fstream&) = 0;

  static Out* create(int);

  std::string& instru() {
    return instru_;
  }

 private:
  std::string instru_;
};

};  // namespace meal

#endif
