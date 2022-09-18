#include "pch.hpp"

#include "installer_win.hpp"

#ifdef _WIN32
namespace perfcat {
typedef BOOL(WINAPI* LPFN_ISWOW64PROCESS)(HANDLE, PBOOL);

bool InstallerWin::install(std::vector<uint8_t>& args) {
  if (!process_.start()) {
    return false;
  }

  auto process_info = process_.get_process_info();
  auto process_handle = process_info.hProcess;
  auto thread_handle = process_info.hThread;

  auto is_x64 = this->is_x64();
  std::string library_path = is_x64 ? "perfcat_hook.dll" : "perfcat_hook_x86.dll";

  auto library_path_bytesize = library_path.size() * sizeof(std::uint8_t) + 1;
  auto args_len_bytes = args.size() * sizeof(uint8_t);

  auto remote_library_path = VirtualAllocEx(
      process_handle, nullptr, library_path_bytesize, MEM_COMMIT, PAGE_READWRITE);
  auto remote_args = VirtualAllocEx(process_handle, nullptr, args_len_bytes,
                                    MEM_COMMIT, PAGE_READWRITE);

  WriteProcessMemory(process_handle, remote_library_path, library_path.c_str(),
                     library_path_bytesize, nullptr);
  WriteProcessMemory(process_handle, remote_args, args.data(), args_len_bytes,
                    nullptr);

  auto load_library =
      GetProcAddress(GetModuleHandleA("kernel32.dll"), "LoadLibraryA");
  auto remote_thread =
      CreateRemoteThread(process_handle, nullptr, 0,
                         reinterpret_cast<LPTHREAD_START_ROUTINE>(load_library),
                         remote_library_path, 0, nullptr);

  WaitForSingleObject(remote_thread, INFINITE);

  VirtualFreeEx(process_handle, remote_library_path, library_path_bytesize,
                MEM_RELEASE);
  VirtualFreeEx(process_handle, remote_args, args_len_bytes, MEM_RELEASE);

  CloseHandle(process_handle);
  CloseHandle(thread_handle);

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
