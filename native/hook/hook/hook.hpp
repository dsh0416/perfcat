#pragma once

#include "pch.hpp"

namespace perfcat::hooks {
class IHook {
public:
  IHook() = default;
  virtual ~IHook() { unload(); }
  static IHook& instance() {
    static IHook instance;
    return instance;
  }

public:
  virtual bool attach() { return false; }
  virtual bool unload() { return false; }
};

template <typename T> class hook_guard {
public:
  explicit hook_guard(T& hook, std::uintptr_t addr) : hook_(hook), addr_(addr) {
    hook_.setup_guard(addr_, hooked_);
  }
  ~hook_guard() { hook_.remove_guard(addr_, hooked_); }

private:
  std::uintptr_t hooked_ = 0;
  std::uintptr_t addr_ = 0;
  T& hook_;
};
} // namespace perfcat::hooks
