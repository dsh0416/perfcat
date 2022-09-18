#pragma once

#include "pch.hpp"

#include "process/process.hpp"

namespace perfcat {
class IInstaller {
public:
  IInstaller(IProcess& process){};
  virtual ~IInstaller() = default;
  virtual bool install(std::vector<uint8_t>& args) { return false; };
};
} // namespace perfcat
