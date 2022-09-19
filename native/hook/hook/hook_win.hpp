#pragma once

#include "pch.hpp"

#include "hook.hpp"

#ifdef _WIN32
namespace perfcat::hooks {
class IHookWin : public IHook {
public:
  IHookWin() = default;
  static IHookWin& instance() {
    static IHookWin instance;
    return instance;
  }

public:
  bool unload() override;

public:
  void setup_guard(std::uintptr_t addr, std::uintptr_t& hooked) override {
    auto it = hooks_.find(addr);
    if (it != hooks_.end()) {
      // temporarily remove hook to use origin function
      hooked = it->second.second;
      if (!remove_hook(addr)) {
        hooked = 0;
      };
    }
  }
  void remove_guard(std::uintptr_t addr, std::uintptr_t hooked) override {
    if (hooked != 0) {
      hook_by_addr(addr, hooked);
    }
  }

protected:
  bool hook_by_addr(std::uintptr_t original, std::uintptr_t hooked);
  bool hook_by_name(const std::string& module, const std::string& original,
                    std::uintptr_t hooked);
  bool hook_by_vtable(std::uintptr_t klass, std::size_t index,
                      std::uintptr_t hooked);
  bool remove_hook(std::uintptr_t addr);

protected:
#ifdef _M_X64
  using jmp_t = std::array<std::uint8_t, 13>;
  const jmp_t jmp_{
      0x49, 0xBA, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, // mov r10, addr
      0x41, 0xFF,
      0xE2 // jmp r10
  };
#else
  using jmp_t = std::array<std::uint8_t, 5>;
  const jmp_t jmp_{
      0xE9, 0x0, 0x0, 0x0, 0x0 // jmp addr
  };
#endif
  std::unordered_map<std::uintptr_t, std::pair<jmp_t, std::uintptr_t>>
      hooks_; // addr, {original, hooked}
};
} // namespace perfcat::hooks
#endif
