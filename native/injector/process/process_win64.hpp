#pragma once

#include "pch.hpp"

#include "process.hpp"

#ifdef _WIN32
namespace perfcat {
class ProcessWin64 : public IProcess {
public:
  using IProcess::IProcess;
  ~ProcessWin64() = default;

public:
  bool start() override;
  bool kill() override;
  bool is_running() override;

private:
  std::string cmdline() const;

private:
  PROCESS_INFORMATION process_info_{nullptr};
};
} // namespace perfcat
#endif
