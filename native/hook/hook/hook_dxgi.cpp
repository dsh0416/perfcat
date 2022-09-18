#include "pch.hpp"

#include "hook_dxgi.hpp"

#ifdef _WIN32
namespace perfcat::hooks {
HookDxgi::idxgi_swapchain_present_t HookDxgi::present_{
    HookDxgi::idxgiSwapchainPresent};

HRESULT HookDxgi::idxgiSwapchainPresent(IDXGISwapChain* self,
                                        UINT sync_interval, UINT flags) {
  std::cout << "IDXGISwapChain::Present hooked" << std::endl;

  {
    HookDxgi::instance().origin_guard(
        reinterpret_cast<std::uintptr_t>(present_));
    return self->Present(sync_interval, flags);
  }
}

bool HookDxgi::attach() {
  // TODO: get a swapcahin
  IDXGISwapChain* swap_chain = nullptr;

  bool res = true;
  res &= hook_by_vtable((uintptr_t)swap_chain, 8, (uintptr_t)present_);
  return res;
}
} // namespace perfcat::hooks
#endif
