// Copyright (c) 2010
// All rights reserved.

#ifndef MEAL_JSONOUT_HH
#define MEAL_JSONOUT_HH

#include <string>
#include <fstream>
#include "Out.hh"
#include "json/json.hh"

namespace meal {

class JsonOut : public Out {
 public:
  JsonOut();

  virtual ~JsonOut();

  virtual void parse(const std::string&);

  virtual void output(std::fstream&);

 private:
  json::Document doc_;
};

};  // namespace meal

#endif
