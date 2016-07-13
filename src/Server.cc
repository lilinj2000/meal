// Copyright (c) 2010
// All rights reserved.

#include <boost/filesystem.hpp>
#include "Server.hh"
#include "Log.hh"
#include "Out.hh"
#include "json/json.hh"
#include "soil/DateTime.hh"
#include "soil/FileSystem.hh"

namespace meal {

Server::Server(int argc, char* argv[]) {
  MEAL_TRACE <<"Server::Server()";

  config_.reset(new Config(argc, argv));

  soil::checkPath(config_->mealOptions()->data_path);

  sub_service_.reset(
      zod::SubService::create(
          config_->mealOptions()->xpub_addr, this));
}

Server::~Server() {
  MEAL_TRACE <<"Server::~Server()";

  for (auto f : map_fs_) {
    delete f.second;
  }
}

void Server::msgCallback(const zod::Msg* msg) {
  MEAL_TRACE <<"Server::msgCallback()";

  std::string data(
      reinterpret_cast<const char*>(msg->data_.get()),
      msg->len_);

  std::unique_ptr<Out> out(Out::create(config_->mealOptions()->out_type));

  out->parse(data);

  std::fstream* f = getFileStream(out->instru());

  out->output(*f);
}

std::fstream* Server::getFileStream(const std::string& instru) {
  std::fstream* f = nullptr;
  auto i_iter = map_fs_.find(instru);
  if (i_iter != map_fs_.end()) {
    f = i_iter->second;
  } else {
    f = new std::fstream(config_->mealOptions()->data_path
                         + boost::filesystem::path::preferred_separator
                         + config_->mealOptions()->file_prefix
                         + instru + ".data", std::fstream::out);
    map_fs_[instru] = f;
  }

  return f;
}

};  // namespace meal
