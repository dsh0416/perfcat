#pragma once

#include "pch.hpp"

namespace perfcat::injector {
class IProcess {
public:
  IProcess(const std::string work_dir, const std::vector<std::string> args)
      : work_dir_(work_dir), args_(args){};
  virtual ~IProcess() = default;

public:
  virtual bool start() { return false; };
  virtual bool kill() { return false; };
  virtual bool is_running() { return false; };

protected:
  const std::string work_dir_;
  const std::vector<std::string> args_;

protected:
  bool started_ = false;
};
} // namespace perfcat::injector
