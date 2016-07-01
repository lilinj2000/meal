// Copyright (c) 2010
// All rights reserved.

#include "JsonOut.hh"
#include "soil/DateTime.hh"

namespace meal {

JsonOut::JsonOut() {
}

JsonOut::~JsonOut() {
}

void JsonOut::parse(const std::string& msg) {
  json::fromString(msg, &doc_);

  if (doc_.HasMember("onReceiveMarketData")) {
    json::Value& odata = doc_["onReceiveMarketData"];

    if (odata.HasMember("MarketDataField")) {
      json::Value& mdata = odata["MarketDataField"];
      
      if (mdata.HasMember("InstrumentID")) {
        instru() = mdata["InstrumentID"].GetString();
      }
    }
  }
}

void JsonOut::output(std::fstream& f) {
  f <<json::toString(doc_) <<std::endl;
}



}  // namespace meal
