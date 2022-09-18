#include "pch.hpp"

#include "hook/hook_dxgi.hpp"

#ifdef _WIN32
#define EXPORTS_API __declspec(dllexport) __cdecl
#else
#define EXPORTS_API
#endif

extern "C" {
void EXPORTS_API perfcat_hook_init(perfcat::perfcat_hook_init_t args) {
#ifdef _WIN32
  perfcat::hooks::HookDxgi::instance().attach();
#endif

#ifdef _WIN32
  auto wake_up_tid = args.wake_up_tid;
  auto wake_up_handle =
      OpenThread(THREAD_ALL_ACCESS, FALSE, static_cast<DWORD>(wake_up_tid));
  if (wake_up_handle == nullptr) {
    return;
  }
  ResumeThread(wake_up_handle);
  CloseHandle(wake_up_handle);
#endif
  return;
}
}
