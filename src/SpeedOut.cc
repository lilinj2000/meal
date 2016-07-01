// Copyright (c) 2010
// All rights reserved.

#include "SpeedOut.hh"
#include "json/json.hh"
#include "soil/DateTime.hh"

namespace meal {

SpeedOut::SpeedOut() {
}

SpeedOut::~SpeedOut() {
}

void SpeedOut::parse(const std::string& msg) {
  json::Document doc;
  json::fromString(msg, &doc);

  if (doc.HasMember("onReceiveMarketData")) {
    json::Value& odata = doc["onReceiveMarketData"];

    if (odata.HasMember("MarketDataField")) {
      json::Value& mdata = odata["MarketDataField"];
      
      if (mdata.HasMember("InstrumentID")) {
        instru() = mdata["InstrumentID"].GetString();
      }

      if (mdata.HasMember("UpdateTime")) {
        update_time_ = mdata["UpdateTime"].GetString();
      }

      if (mdata.HasMember("UpdateMillisec")) {
        update_millisec_ = mdata["UpdateMillisec"].GetInt();
      }
    }

    if (odata.HasMember("timestamp")) {
      timestamp_ = odata["timestamp"].GetString();
    }

    if (odata.HasMember("ts")) {
      ts_ = odata["ts"].GetString();
    }
  }
}

void SpeedOut::output(std::fstream& f) {
  soil::DateTime t0_time(update_time_);
  t0_time += std::chrono::milliseconds(update_millisec_);

  soil::DateTime t1_time(ts_);
  soil::DateTime t2_time(timestamp_);

  std::chrono::system_clock::duration d1 = t1_time - t0_time;
  std::chrono::system_clock::duration d2 = t2_time - t0_time;
  
  f <<instru() <<"\t"
    <<update_time_ <<"." <<update_millisec_ <<"\t"
    <<ts_ <<"\t"
    <<timestamp_ <<"\t"
    <<d1.count() <<"\t"
    <<d2.count() <<std::endl;
}



}  // namespace meal
