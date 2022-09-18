#include "pch.hpp"

#include "installer_win.hpp"

#ifdef _WIN32
namespace perfcat {
typedef BOOL(WINAPI* LPFN_ISWOW64PROCESS)(HANDLE, PBOOL);

bool InstallerWin::install(perfcat_hook_init_t& args) {
  if (!process_.start()) {
    return false;
  }

  auto process_info = process_.get_process_info();
  auto process_handle = process_info.hProcess;

  // LoadLibraryA
  auto is_x64 = this->is_x64();
  std::string library_path =
      is_x64 ? "perfcat_hook.dll" : "perfcat_hook_x86.dll";
  auto library_path_bytesize = library_path.size() * sizeof(std::uint8_t) + 1;

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
  auto args_len_bytes = sizeof(args);
  auto remote_args = VirtualAllocEx(process_handle, nullptr, args_len_bytes,
                                    MEM_COMMIT, PAGE_READWRITE);
  auto remote_thread_perfcat_init = CreateRemoteThread(
      process_handle, nullptr, 0,
      reinterpret_cast<LPTHREAD_START_ROUTINE>(GetProcAddress(
          GetModuleHandleA(library_path.c_str()), "perfcat_hook_init")),
      remote_args, 0, nullptr);

  WaitForSingleObject(remote_thread_perfcat_init, INFINITE);

  WriteProcessMemory(process_handle, remote_args, ((void*)args),
                     args_len_bytes, nullptr);

  VirtualFreeEx(process_handle, remote_args, args_len_bytes, MEM_RELEASE);
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
  if (!fnIsWow64Process(hProcess, &wow64)) {
    CloseHandle(hProcess);
    return false;
  }

  CloseHandle(hProcess);
  return !wow64;
}
} // namespace perfcat
#endif
