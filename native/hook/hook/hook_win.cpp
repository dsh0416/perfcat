#include "pch.hpp"

#include "hook_win.hpp"

#ifdef _WIN32
namespace perfcat::hooks {
bool IHookWin::unload() {
  bool res = true;
  std::vector<std::uintptr_t> addrs;
  for (auto& [addr, _] : hooks_) {
    addrs.push_back(addr);
  }

  for (auto& addr : addrs) {
    res &= remove_hook(addr);
  }

  return res;
}

bool IHookWin::hook_by_addr(std::uintptr_t original, std::uintptr_t hooked) {
  std::lock_guard lock(hooks_mutex_);

  if (hooks_.find(original) != hooks_.end()) {
    return false;
  }

  jmp_t jmp = jmp_;
#ifdef _M_X64
  std::memcpy(&jmp[2], &hooked, sizeof(hooked));
#else
  std::memcpy(&jmp[1], &hooked, sizeof(hooked));
#endif

  jmp_t jmp_original{0};

  DWORD protect;
  if (!VirtualProtect(reinterpret_cast<void*>(original), jmp.size(),
                      PAGE_EXECUTE_READWRITE, &protect)) {
    return false;
  }

  std::memcpy(&jmp_original[0], reinterpret_cast<void*>(original), jmp.size());
  std::memcpy(reinterpret_cast<void*>(original), &jmp[0], jmp.size());

  VirtualProtect(reinterpret_cast<void*>(original), jmp.size(), protect,
                 &protect);

  hooks_.insert({original, {jmp_original, hooked}});
  return true;
}

bool IHookWin::hook_by_name(const std::string& module,
                            const std::string& original,
                            std::uintptr_t hooked) {
  auto addr = reinterpret_cast<std::uintptr_t>(
      GetProcAddress(GetModuleHandleA(module.c_str()), original.c_str()));
  if (!addr) {
    return false;
  }

  return hook_by_addr(addr, hooked);
}

bool IHookWin::hook_by_vtable(std::uintptr_t klass, std::size_t index,
                              std::uintptr_t hooked) {
  auto vtable = *reinterpret_cast<std::uintptr_t**>(klass);
  return hook_by_addr(vtable[index], hooked);
}

bool IHookWin::remove_hook(std::uintptr_t addr) {
  std::lock_guard lock(hooks_mutex_);

  if (hooks_.find(addr) == hooks_.end()) {
    return false;
  }

  auto& [jmp_original, hooked] = hooks_[addr];

  DWORD protect;
  if (!VirtualProtect(reinterpret_cast<void*>(addr), jmp_original.size(),
                      PAGE_EXECUTE_READWRITE, &protect)) {
    return false;
  }
  std::memcpy(reinterpret_cast<void*>(addr), &jmp_original[0],
              jmp_original.size());
  VirtualProtect(reinterpret_cast<void*>(addr), jmp_original.size(), protect,
                 &protect);

  hooks_.erase(addr);
  return true;
}
} // namespace perfcat::hooks
#endif
