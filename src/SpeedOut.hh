// Copyright (c) 2010
// All rights reserved.

#ifndef MEAL_SPEEDOUT_HH
#define MEAL_SPEEDOUT_HH

#include <string>
#include <fstream>
#include "Out.hh"

namespace meal {

class SpeedOut : public Out {
 public:
  SpeedOut();

  virtual ~SpeedOut();

  virtual void parse(const std::string&);

  virtual void output(std::fstream&);

 private:
  std::string update_time_;
  int update_millisec_;

  std::string timestamp_;
  std::string ts_;
};

};  // namespace meal

#endif
