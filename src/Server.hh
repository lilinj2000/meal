// Copyright (c) 2010
// All rights reserved.

#ifndef MEAL_SERVER_HH
#define MEAL_SERVER_HH

#include <memory>
#include <string>
#include <map>
#include <fstream>

#include "Config.hh"
#include "zod/SubService.hh"

namespace meal {

class Server : public zod::MsgCallback {
 public:
  Server(int argc, char *argv[]);

  ~Server();

  virtual void msgCallback(const zod::Msg*);

  std::fstream* getFileStream(const std::string& instru);

  void output(std::fstream* f);

 private:
  std::unique_ptr<Config> config_;

  std::map<std::string, std::fstream*> map_fs_;

  std::unique_ptr<zod::SubService> sub_service_;
};

};  // namespace meal

#endif
