#include "pch.hpp"

#include "installer_win.hpp"

#ifdef _WIN32
namespace perfcat::injector {
typedef BOOL(WINAPI* LPFN_ISWOW64PROCESS)(HANDLE, PBOOL);

bool InstallerWin::install(perfcat_hook_init_t& args) {
  if (!process_.start()) {
    return false;
  }

  auto process_info = process_.get_process_info();
  auto process_handle = process_info.hProcess;

  // LoadLibraryA
  std::string library_path =
      std::filesystem::current_path().string() +
      (this->is_x64() ? "perfcat_hook.dll" : "perfcat_hook_x86.dll");
  auto library_path_bytesize = (library_path.size() + 1) * sizeof(std::uint8_t);

  auto remote_library_path =
      VirtualAllocEx(process_handle, nullptr, library_path_bytesize, MEM_COMMIT,
                     PAGE_READWRITE);
  WriteProcessMemory(process_handle, remote_library_path, library_path.c_str(),
                     library_path_bytesize, nullptr);

  auto load_library =
      GetProcAddress(GetModuleHandleA("kernel32.dll"), "LoadLibraryA");
  auto remote_thread_load_library =
      CreateRemoteThread(process_handle, nullptr, 0,
                         reinterpret_cast<LPTHREAD_START_ROUTINE>(load_library),
                         remote_library_path, 0, nullptr);

  WaitForSingleObject(remote_thread_load_library, INFINITE);
  VirtualFreeEx(process_handle, remote_library_path, library_path_bytesize,
                MEM_RELEASE);

  // perfcat_hook_init
  args.wake_up_tid = process_info.dwThreadId; // Setup wake up thread id
  auto remote_args = VirtualAllocEx(process_handle, nullptr, sizeof(args),
                                    MEM_COMMIT, PAGE_READWRITE);
  WriteProcessMemory(process_handle, remote_args, &args, sizeof(args), nullptr);
  auto remote_thread_perfcat_init = CreateRemoteThread(
      process_handle, nullptr, 0,
      reinterpret_cast<LPTHREAD_START_ROUTINE>(GetProcAddress(
          GetModuleHandleA(library_path.c_str()), "perfcat_hook_init")),
      remote_args, 0, nullptr);

  WaitForSingleObject(remote_thread_perfcat_init, INFINITE);
  VirtualFreeEx(process_handle, remote_args, sizeof(args), MEM_RELEASE);
  return true;
}

bool InstallerWin::is_x64() const {
  LPFN_ISWOW64PROCESS fnIsWow64Process = (LPFN_ISWOW64PROCESS)GetProcAddress(
      GetModuleHandle(TEXT("kernel32")), "IsWow64Process");

  if (fnIsWow64Process == NULL) {
    return false;
  }

  HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE,
                                process_.get_process_info().dwProcessId);
  if (hProcess == NULL) {
    return false;
  }

  BOOL wow64 = FALSE;
  fnIsWow64Process(hProcess, &wow64);
  CloseHandle(hProcess);
  return !wow64;
}
} // namespace perfcat::injector
#endif
