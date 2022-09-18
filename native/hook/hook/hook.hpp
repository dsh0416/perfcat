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
} // namespace perfcat::hooks
