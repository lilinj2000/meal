// Copyright (c) 2010
// All rights reserved.

#include <boost/filesystem.hpp>
#include "Server.hh"
#include "Log.hh"
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
}

void Server::msgCallback(const zod::Msg* msg) {
  MEAL_TRACE <<"Server::msgCallback()";

  std::string data(
      reinterpret_cast<const char*>(msg->data_.get()),
      msg->len_);

  // createObject()
  // obj->Parse();
  // obj->output();

  json::Document doc;
  json::fromString(data, &doc);

  // instru info
  std::string instru;
  std::string update_time;
  int update_millisec = 0;

  // packet info
  std::string timestamp;
  std::string ts;

  if (doc.HasMember("onReceiveMarketData")) {
    json::Value& odata = doc["onReceiveMarketData"];

    if (odata.HasMember("MarketDataField")) {
      json::Value& mdata = odata["MarketDataField"];

      if (mdata.HasMember("InstrumentID")) {
        instru = mdata["InstrumentID"].GetString();
      }

      if (mdata.HasMember("UpdateTime")) {
        update_time = mdata["UpdateTime"].GetString();
      }

      if (mdata.HasMember("UpdateMillisec")) {
        update_millisec = mdata["UpdateMillisec"].GetInt();
      }
    }

    if (odata.HasMember("timestamp")) {
      timestamp = odata["timestamp"].GetString();
    }

    if (odata.HasMember("ts")) {
      ts = odata["ts"].GetString();
    }
  }

  std::fstream* f = getFileStream(instru);
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
                         + instru + ".data");
    map_fs_[instru] = f;
  }

  return f;
}

void Server::output(std::fstream* f) {
}

};  // namespace meal
