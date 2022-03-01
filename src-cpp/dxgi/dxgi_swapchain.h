#pragma once

#include <memory>
#include <mutex>

#include "dxgi_object.h"

#include "../util/util_time.h"

namespace dxvk {

  class DxgiDevice;
  class DxgiFactory;
  class DxgiOutput;
  class D3D10Device;

  class DxgiSwapChain : public DxgiObject<IDXGISwapChain> {

  public:

    DxgiSwapChain(IDXGISwapChain* swapchain, D3D10Device* device, IDXGIFactory* factory);

    ~DxgiSwapChain();

    HRESULT STDMETHODCALLTYPE QueryInterface(
            REFIID                    riid,
            void**                    ppvObject) final;

    HRESULT STDMETHODCALLTYPE GetParent(
            REFIID                    riid,
            void**                    ppParent) final;

    HRESULT STDMETHODCALLTYPE GetDevice(
            REFIID                    riid,
            void**                    ppDevice) final;

    HRESULT STDMETHODCALLTYPE GetBuffer(
            UINT                      Buffer,
            REFIID                    riid,
            void**                    ppSurface) final;

    HRESULT STDMETHODCALLTYPE GetContainingOutput(
            IDXGIOutput**             ppOutput) final;

    HRESULT STDMETHODCALLTYPE GetDesc(
            DXGI_SWAP_CHAIN_DESC*     pDesc) final;

    HRESULT STDMETHODCALLTYPE GetFullscreenState(
            BOOL*                     pFullscreen,
            IDXGIOutput**             ppTarget) final;
    HRESULT STDMETHODCALLTYPE GetFrameStatistics(
            DXGI_FRAME_STATISTICS*    pStats) final;

    HRESULT STDMETHODCALLTYPE GetLastPresentCount(
            UINT*                     pLastPresentCount) final;

    HRESULT STDMETHODCALLTYPE Present(
            UINT                      SyncInterval,
            UINT                      Flags) final;

    HRESULT STDMETHODCALLTYPE ResizeBuffers(
            UINT                      BufferCount,
            UINT                      Width,
            UINT                      Height,
            DXGI_FORMAT               NewFormat,
            UINT                      SwapChainFlags) final;

    HRESULT STDMETHODCALLTYPE ResizeTarget(
      const DXGI_MODE_DESC*           pNewTargetParameters) final;

    HRESULT STDMETHODCALLTYPE SetFullscreenState(
            BOOL                      Fullscreen,
            IDXGIOutput*              pTarget) final;

  private:

    Com<IDXGISwapChain>             m_swapchain;
    Com<D3D10Device>                m_device;
    Com<IDXGIFactory>               m_factory;

  };

}
