#include "pch.hpp"

#include "hook_dxgi.hpp"

#ifdef _WIN32
namespace perfcat::hooks {
HRESULT HookDxgi::idxgi_swapchain_present(IDXGISwapChain* self,
                                          UINT sync_interval, UINT flags) {
  std::cout << "IDXGISwapChain::Present hooked" << std::endl;

  {
    hook_guard<HookDxgi> guard(
        HookDxgi::instance(),
        reinterpret_cast<std::uintptr_t>(idxgi_swapchain_present));
    return self->Present(sync_interval, flags);
  }
}

bool HookDxgi::attach() {
  // TODO: get a swapcahin
  IDXGISwapChain* swap_chain = nullptr;

  bool res = true;
  res &= hook_by_vtable((uintptr_t)swap_chain, 8,
                        (uintptr_t)idxgi_swapchain_present);
  return res;
}
} // namespace perfcat::hooks
#endif
