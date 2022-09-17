#pragma once

#include "pch.hpp"

#include "process.hpp"

#ifdef _WIN32
namespace perfcat {
class ProcessWin : public IProcess {
public:
  using IProcess::IProcess;
  ~ProcessWin() = default;

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
