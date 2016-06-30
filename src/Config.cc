// Copyright (c) 2010
// All rights reserved.

#include <boost/program_options.hpp>
#include <fstream>
#include <iostream>

#include "Config.hh"
#include "Log.hh"

namespace meal {

Options::Options():
    config_options_("mealConfigOptions") {
  namespace po = boost::program_options;

  config_options_.add_options()
      ("meal.xpub_addr", po::value<std::string>(&xpub_addr),
       "xpub address")
      ("meal.data_path", po::value<std::string>(&data_path),
       "path of the data")
      ("meal.file_prefix", po::value<std::string>(&file_prefix),
       "file prefix")
      ("meal.log_cfg", po::value<std::string>(&log_cfg),
         "log config file");
  return;
}

Options::~Options() {
}

po::options_description* Options::configOptions() {
  return &config_options_;
}

Config::Config(int argc, char* argv[]) {
  meal_options_.reset(new Options());

  std::unique_ptr<soil::Config> config(soil::Config::create());
  config->registerOptions(meal_options_.get());

  config->configFile() = "meal.cfg";
  config->loadConfig(argc, argv);

  // init the log
  MEAL_LOG_INIT(meal_options_->log_cfg);

  return;
}

Config::~Config() {
}

};  // namespace meal
