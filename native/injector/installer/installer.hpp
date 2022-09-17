#pragma once

#include "pch.hpp"

#include "injector/process/process.hpp"

namespace perfcat {
class IInstaller {
public:
  IInstaller(IProcess& process, const std::vector<std::uint8_t> library)
      : library_(library){};
  virtual ~IInstaller() = default;
  virtual bool install(const std::vector<uint8_t>& args);

protected:
  const std::vector<std::uint8_t> library_;
};
} // namespace perfcat
