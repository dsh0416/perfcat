#pragma once

#include "pch.hpp"

#ifdef _WIN32
#include <dxgi.h>

#include "hook_win.hpp"

namespace perfcat::hooks {
class HookDxgi : public IHookWin {
public:
  using IHookWin::IHookWin;
  bool attach() override;

private:
  using idxgi_swapchain_present_t = HRESULT(__stdcall*)(IDXGISwapChain*, UINT,
                                                        UINT);
  static HRESULT __stdcall idxgiSwapchainPresent(IDXGISwapChain* self,
                                                 UINT sync_interval,
                                                 UINT flags);
  static idxgi_swapchain_present_t present_;
};
} // namespace perfcat::hooks
#endif
