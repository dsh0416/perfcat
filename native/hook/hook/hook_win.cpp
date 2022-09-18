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

IHookOrigin IHookWin::origin_guard(std::uintptr_t addr) {
  return std::move(HookOriginWin(*this, addr));
}

bool IHookWin::hook_by_addr(std::uintptr_t original, std::uintptr_t hooked) {
  if (hooks_.find(original) != hooks_.end()) {
    return false;
  }

  jmp_t jmp = jmp_;
#ifdef _M_X64
  std::memcpy(&jmp[2], &hooked, sizeof(hooked));
#else
  std::memcpy(&jmp[1], &hooked, sizeof(hooked));
#endif

  jmp_t jmp_original;
  std::memcpy(&jmp[0], reinterpret_cast<void*>(original), jmp.size());

  DWORD protect;
  if (!VirtualProtect(reinterpret_cast<void*>(original), jmp.size(),
                      PAGE_EXECUTE_READWRITE, &protect)) {
    return false;
  }

  std::memcpy(reinterpret_cast<void*>(original), &jmp[0], jmp.size());
  VirtualProtect(reinterpret_cast<void*>(original), jmp.size(), protect,
                 &protect);

  hooks_.insert({original, {jmp_original, hooked}});
  return true;
}

bool IHookWin::remove_hook(std::uintptr_t addr) {
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

HookOriginWin::HookOriginWin(IHookWin& hook, std::uintptr_t addr)
    : IHookOrigin(), hook_(hook), addr_(addr) {
  auto it = hook_.hooks_.find(addr_);
  if (it != hook_.hooks_.end()) {
    // temporarily remove hook to use origin function
    if (hook_.remove_hook(addr_)) {
      hooked_ = it->second.second;
    };
  }
}

HookOriginWin::~HookOriginWin() {
  if (hooked_ != 0) {
    // hook the address back
    hook_.hook_by_addr(addr_, hooked_);
  }
}
} // namespace perfcat::hooks
#endif
