// Copyright (c) 2010
// All rights reserved.

#ifndef MEAL_CONFIG_HH
#define MEAL_CONFIG_HH

#include <string>
#include <memory>

#include "soil/Config.hh"

namespace meal {

namespace po = boost::program_options;

class Options : public soil::Options {
 public:
  Options();

  virtual ~Options();

  virtual po::options_description* configOptions();

  std::string xpub_addr;
  std::string data_path;
  std::string file_prefix;
  std::string log_cfg;

 private:
  boost::program_options::options_description config_options_;
};

class Config {
 public:
  explicit Config(int argc = 0, char* argv[] = nullptr);
  ~Config();

  Options* mealOptions() {
    return meal_options_.get();
  }

 private:
  std::unique_ptr<Options> meal_options_;
};

};  // namespace meal

#endif
