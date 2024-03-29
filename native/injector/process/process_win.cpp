#include "pch.hpp"

#include "process_win.hpp"

#ifdef _WIN32
namespace perfcat::injector {
ProcessWin::~ProcessWin() {
  if (started_) {
    kill();
  }

  if (process_info_.hThread) {
    CloseHandle(process_info_.hThread);
  }

  if (process_info_.hProcess) {
    CloseHandle(process_info_.hProcess);
  }
}

bool ProcessWin::start() {
  STARTUPINFOA startup_info = {0};
  startup_info.cb = sizeof(startup_info);

  if (!CreateProcessA(NULL, ((LPSTR)cmdline().c_str()), NULL, NULL, FALSE,
                      CREATE_SUSPENDED, NULL, work_dir_.c_str(), &startup_info,
                      &process_info_)) {
    return false;
  }

  started_ = true;
  return true;
}

bool ProcessWin::kill() {
  if (!started_) {
    return false;
  }

  if (!TerminateProcess(process_info_.hProcess, 0)) {
    return false;
  }

  started_ = false;
  return true;
}

bool ProcessWin::is_running() {
  if (!started_) {
    return false;
  }

  DWORD exit_code;
  if (!GetExitCodeProcess(process_info_.hProcess, &exit_code)) {
    return false;
  }

  if (exit_code == STILL_ACTIVE) {
    return true;
  }

  started_ = false;
  return false;
}

std::string ProcessWin::cmdline() const {
  // Reference:
  // https://docs.microsoft.com/zh-cn/archive/blogs/twistylittlepassagesallalike/everyone-quotes-command-line-arguments-the-wrong-way
  // https://docs.microsoft.com/zh-cn/windows/desktop/api/shellapi/nf-shellapi-commandlinetoargvw

  std::string ret = "";

  for (auto arg : args_) {
    if (arg.empty() || arg.find_first_of(" \t\n\v\"") == std::string::npos) {
      // Do not escape the parameter
      ret += arg;
    } else {
      // escape the parameter
      ret += "\"";
      for (auto it = arg.begin();; it++) {
        uint32_t number_backslashes = 0;

        while (it != arg.end() && *it == '\\') {
          number_backslashes++;
          it++;
        }

        if (it == arg.end()) {
          // Escape all backslashes, but let the terminating double quotation
          // mark we add below be interpreted as a meta-character.
          ret.append(number_backslashes * 2, '\\');
          break;
        } else if (*it == '"') {
          // Escape all backslashes and the following double quotation mark.
          ret.append(number_backslashes * 2 + 1, '\\');
          ret.push_back(*it);
        } else {
          // Backslashes aren't special here.
          ret.append(number_backslashes, L'\\');
          ret.push_back(*it);
        }
      }
      ret += "\"";
    }

    ret += " ";
  }

  // remove trailing space
  ret.pop_back();
  return ret;
}
} // namespace perfcat::injector
#endif
