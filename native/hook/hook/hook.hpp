#pragma once

#include "pch.hpp"

namespace perfcat::hooks {
class IHook {
public:
  IHook() = default;
  virtual ~IHook() { unload(); }

public:
  virtual bool attach() { return false; }
  virtual bool unload() { return false; }

public:
  virtual void setup_guard(std::uintptr_t addr, std::uintptr_t& hooked) {}
  virtual void remove_guard(std::uintptr_t addr, std::uintptr_t hooked) {}
};

class hook_guard {
public:
  explicit hook_guard(IHook& hook, std::uintptr_t addr)
      : hook_(hook), addr_(addr) {
    hook_.setup_guard(addr_, hooked_);
  }
  ~hook_guard() { hook_.remove_guard(addr_, hooked_); }

private:
  std::uintptr_t hooked_ = 0;
  std::uintptr_t addr_ = 0;
  IHook& hook_;
};
} // namespace perfcat::hooks
