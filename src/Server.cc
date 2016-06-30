// Copyright (c) 2010
// All rights reserved.

#include "Server.hh"
#include "Log.hh"
#include "json/json.hh"
#include "soil/DateTime.hh"

namespace meal {

Server::Server(int argc, char* argv[]) {
  MEAL_TRACE <<"Server::Server()";

  config_.reset(new Config(argc, argv));

  sub_service_.reset(
      zod::SubService::create(
          config_->mealOptions()->xpub_addr, this));
}

Server::~Server() {
  MEAL_TRACE <<"Server::~Server()";
}

void Server::msgCallback(const zod::Msg* msg) {
  MEAL_TRACE <<"Server::msgCallback()";

  std::string data(
      reinterpret_cast<const char*>(msg->data_.get()),
      msg->len_);

  MEAL_CUSTOM <<data;
}

};  // namespace meal
