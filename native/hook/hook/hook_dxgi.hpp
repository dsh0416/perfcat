#pragma once

#include "pch.hpp"

#ifdef _WIN32
#include <dxgi.h>

#include "hook_win.hpp"

namespace perfcat::hooks {
class HookDxgi : public IHookWin {
public:
  using IHookWin::IHookWin;
  static HookDxgi& instance() {
    static HookDxgi instance;
    return instance;
  }
  bool attach() override;

private:
  static HRESULT __stdcall idxgi_swapchain_present(IDXGISwapChain* self,
                                                   UINT sync_interval,
                                                   UINT flags);
};
} // namespace perfcat::hooks
#endif
