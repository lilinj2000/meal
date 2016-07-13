// Copyright (c) 2010
// All rights reserved.

#include <iomanip>
#include "SpeedOut.hh"
#include "json/json.hh"
#include "soil/DateTime.hh"
#include "Log.hh"

namespace meal {

SpeedOut::SpeedOut() {
}

SpeedOut::~SpeedOut() {
}

void SpeedOut::parse(const std::string& msg) {
  MEAL_TRACE <<"SpeedOut::parse()";

  json::Document doc;
  json::fromString(msg, &doc);

  if (doc.HasMember("onReceiveMarketData")) {
    json::Value& odata = doc["onReceiveMarketData"];

    if (odata.HasMember("MarketDataField")) {
      json::Value& mdata = odata["MarketDataField"];

      if (mdata.HasMember("InstrumentID")) {
        instru() = mdata["InstrumentID"].GetString();
        MEAL_DEBUG <<"instru: " <<instru();
      }

      if (mdata.HasMember("UpdateTime")) {
        update_time_ = mdata["UpdateTime"].GetString();
        MEAL_DEBUG <<"UpdateTime: " <<update_time_;
      }

      if (mdata.HasMember("UpdateMillisec")) {
        update_millisec_ = mdata["UpdateMillisec"].GetInt();
        MEAL_DEBUG <<"UpdateMillisec: " <<update_millisec_;
      }
    }

    if (odata.HasMember("timestamp")) {
      timestamp_ = odata["timestamp"].GetString();
      MEAL_DEBUG <<"timestamp: " <<timestamp_;
    }

    if (odata.HasMember("ts")) {
      ts_ = odata["ts"].GetString();
      MEAL_DEBUG <<"ts: " <<ts_;
    }
  }
}

void SpeedOut::output(std::fstream& f) {
  MEAL_TRACE <<"SpeedOut::output()";

  soil::DateTime t0_time(update_time_);
  t0_time += std::chrono::milliseconds(update_millisec_);

  soil::DateTime t1_time(ts_);
  soil::DateTime t2_time(timestamp_);

  std::chrono::system_clock::duration d1 = t1_time - t0_time;
  std::chrono::system_clock::duration d2 = t2_time - t0_time;

  f <<instru() <<"\t"
    <<update_time_ <<"." <<std::setw(3) <<std::setfill('0') <<update_millisec_ <<"\t"
    <<ts_ <<"\t"
    <<timestamp_ <<"\t"
    <<d1.count() <<"\t"
    <<d2.count() <<std::endl;
}



}  // namespace meal
