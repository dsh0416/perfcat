#include "pch.hpp"

#include "injector/installer/installer.hpp"
#include "injector/installer/installer_win.hpp"
#include "injector/process/process.hpp"
#include "injector/process/process_win.hpp"

#ifdef _WIN32
#define EXPORTS_API __declspec(dllexport) __cdecl
#else
#define EXPORTS_API
#endif

extern "C" {
bool EXPORTS_API installer_create(void* process, void** installer) {
  if (!process || !installer) {
    return false;
  }

#ifdef _WIN32
  auto process_win = reinterpret_cast<perfcat::ProcessWin*>(process);
  auto installer_win = new perfcat::InstallerWin(*process_win);
#else
  return false;
#endif
  *installer = installer_win;
  return true;
}

bool EXPORTS_API installer_destroy(void* installer) {
  if (!installer) {
    return false;
  }

  delete reinterpret_cast<perfcat::IInstaller*>(installer);
  return true;
}

bool EXPORTS_API installer_install(void* installer, const uint8_t* args,
                                   size_t args_size) {
  if (!installer || !args || !args_size) {
    return false;
  }

  auto installer_ptr = reinterpret_cast<perfcat::IInstaller*>(installer);
  std::vector<uint8_t> args_vec(args, args + args_size);
  return installer_ptr->install(args_vec);
}

bool EXPORTS_API process_create(const char* work_dir, const char* args[],
                                int args_len, void** process) {
  if (process == nullptr) {
    return false;
  }

  std::vector<std::string> args_vec;
  for (int i = 0; i < args_len; i++) {
    args_vec.push_back(args[i]);
  }

#ifdef _WIN32
  perfcat::IProcess* p = new perfcat::ProcessWin(work_dir, args_vec);
#else
  return false;
#endif

  *process = p;
  return true;
}

bool EXPORTS_API process_destroy(void* process) {
  if (process == nullptr) {
    return false;
  }

  perfcat::IProcess* p = reinterpret_cast<perfcat::IProcess*>(process);
  delete p;
  return true;
}

bool EXPORTS_API process_start(void* process) {
  if (process == nullptr) {
    return false;
  }

  perfcat::IProcess* p = reinterpret_cast<perfcat::IProcess*>(process);
  return p->start();
}

bool EXPORTS_API process_kill(void* process) {
  if (process == nullptr) {
    return false;
  }

  perfcat::IProcess* p = reinterpret_cast<perfcat::IProcess*>(process);
  return p->kill();
}

bool EXPORTS_API process_is_running(void* process) {
  if (process == nullptr) {
    return false;
  }

  perfcat::IProcess* p = reinterpret_cast<perfcat::IProcess*>(process);
  return p->is_running();
}
}
