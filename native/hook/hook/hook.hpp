#pragma once

#include "pch.hpp"

namespace perfcat::hooks {
class IHookOrigin {
public:
  IHookOrigin() = default;
  virtual ~IHookOrigin() = default;
};

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
  virtual IHookOrigin origin_guard() { return std::move(IHookOrigin()); }
};
} // namespace perfcat::hooks
