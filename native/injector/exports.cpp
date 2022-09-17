#include "pch.hpp"

#include "injector/process/process.hpp"
#include "injector/process/process_win64.hpp"

#define EXPORTS_API __declspec(dllexport) __stdcall

// Assuming Win64 only

extern "C" {
bool EXPORTS_API process_create(const char* work_dir, const char* args[],
                                int args_len, void** process) {
  if (process == nullptr) {
    return false;
  }

  std::vector<std::string> args_vec;
  for (int i = 0; i < args_len; i++) {
    args_vec.push_back(args[i]);
  }

  perfcat::IProcess* p = new perfcat::ProcessWin64(work_dir, args_vec);
  *process = p;
  return true;
}

bool EXPORTS_API process_start(void* process) {
  if (process == nullptr) {
    return false;
  }

  perfcat::IProcess* p = (perfcat::IProcess*)process;
  return p->start();
}

bool EXPORTS_API process_kill(void* process) {
  if (process == nullptr) {
    return false;
  }

  perfcat::IProcess* p = (perfcat::IProcess*)process;
  return p->kill();
}

bool EXPORTS_API process_is_running(void* process) {
  if (process == nullptr) {
    return false;
  }

  perfcat::IProcess* p = (perfcat::IProcess*)process;
  return p->is_running();
}

bool EXPORTS_API process_destroy(void* process) {
  if (process == nullptr) {
    return false;
  }

  perfcat::IProcess* p = (perfcat::IProcess*)process;
  delete p;
  return true;
}
}
