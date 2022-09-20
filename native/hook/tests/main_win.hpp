#pragma once

#include <cassert>
#include <iostream>

#ifdef _WIN32
#include "hook/hook_win.hpp"

using namespace perfcat::hooks;

int function_foo(int a, int b) { return a + b; }

class HookExample : public IHookWin {
public:
  using IHookWin::IHookWin;
  static HookExample& instance() {
    static HookExample instance;
    return instance;
  }

  static int function_bar(int a, int b) { return a - b; }

  bool attach() override {
    return hook_by_addr(reinterpret_cast<std::uintptr_t>(function_foo),
                        reinterpret_cast<std::uintptr_t>(function_bar));
  }
};

int main() {
  assert(function_foo(1, 2) == 3);
  HookExample::instance().attach();
  assert(function_foo(1, 2) == -1);

  {
    hook_guard guard_foo(HookExample::instance(),
                         reinterpret_cast<std::uintptr_t>(function_foo));

    assert(function_foo(1, 2) == 3);
  }

  assert(function_foo(1, 2) == -1);
  return 0;
}
#endif
