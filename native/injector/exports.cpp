#include "pch.hpp"

#include "installer/installer.hpp"
#include "installer/installer_win.hpp"
#include "process/process.hpp"
#include "process/process_win.hpp"

#ifdef _WIN32
#define EXPORTS_API __declspec(dllexport) __cdecl
#else
#define EXPORTS_API
#endif

extern "C" {
bool EXPORTS_API perfcat_installer_create(void* process, void** installer) {
  if (!process || !installer) {
    return false;
  }

#ifdef _WIN32
  auto process_win = reinterpret_cast<perfcat::injector::ProcessWin*>(process);
  auto installer_win = new perfcat::injector::InstallerWin(*process_win);
#else
  return false;
#endif
  *installer = installer_win;
  return true;
}

bool EXPORTS_API perfcat_installer_destroy(void* installer) {
  if (!installer) {
    return false;
  }

  delete reinterpret_cast<perfcat::injector::IInstaller*>(installer);
  return true;
}

bool EXPORTS_API perfcat_installer_install(void* installer,
                                           perfcat_hook_init_t* args) {
  if (!installer || !args) {
    return false;
  }

  auto installer_ptr =
      reinterpret_cast<perfcat::injector::IInstaller*>(installer);
  return installer_ptr->install(*args);
}

bool EXPORTS_API perfcat_process_create(const char* work_dir,
                                        const char* args[], int args_len,
                                        void** process) {
  if (process == nullptr) {
    return false;
  }

  std::vector<std::string> args_vec;
  for (int i = 0; i < args_len; i++) {
    args_vec.push_back(args[i]);
  }

#ifdef _WIN32
  perfcat::injector::IProcess* p =
      new perfcat::injector::ProcessWin(work_dir, args_vec);
#else
  return false;
#endif

  *process = p;
  return true;
}

bool EXPORTS_API perfcat_process_destroy(void* process) {
  if (process == nullptr) {
    return false;
  }

  perfcat::injector::IProcess* p =
      reinterpret_cast<perfcat::injector::IProcess*>(process);
  delete p;
  return true;
}

bool EXPORTS_API perfcat_process_start(void* process) {
  if (process == nullptr) {
    return false;
  }

  perfcat::injector::IProcess* p =
      reinterpret_cast<perfcat::injector::IProcess*>(process);
  return p->start();
}

bool EXPORTS_API perfcat_process_kill(void* process) {
  if (process == nullptr) {
    return false;
  }

  perfcat::injector::IProcess* p =
      reinterpret_cast<perfcat::injector::IProcess*>(process);
  return p->kill();
}

bool EXPORTS_API perfcat_process_is_running(void* process) {
  if (process == nullptr) {
    return false;
  }

  perfcat::injector::IProcess* p =
      reinterpret_cast<perfcat::injector::IProcess*>(process);
  return p->is_running();
}
}
