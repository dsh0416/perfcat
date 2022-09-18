#pragma once

#include "pch.hpp"

#include "installer.hpp"

#include "process/process_win.hpp"

#ifdef _WIN32
namespace perfcat {
class InstallerWin : public IInstaller {
public:
  InstallerWin(ProcessWin& process) : process_(process), IInstaller(process){};
  bool install(perfcat_hook_init_t& args) override;

private:
  bool is_x64() const;

private:
  ProcessWin& process_;
};
} // namespace perfcat
#endif
