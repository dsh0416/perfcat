#include <cassert>
#include <iostream>

#include "hook/hook_win.hpp"

int function_foo(int a, int b) { return a + b; }

class HookExample : public perfcat::hooks::IHookWin {
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
    perfcat::hooks::hook_guard<HookExample> guard_foo(
        HookExample::instance(),
        reinterpret_cast<std::uintptr_t>(function_foo));

    assert(function_foo(1, 2) == 3);
  }

  assert(function_foo(1, 2) == -1);
  return 0;
}
