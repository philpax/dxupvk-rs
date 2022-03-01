#include "dxgi_factory.h"
#include "dxgi_swapchain.h"

#include "../d3d10/d3d10_device.h"
#include "../d3d10/d3d10_texture.h"

namespace dxvk {

  DxgiSwapChain::DxgiSwapChain(IDXGISwapChain* swapchain, D3D10Device* device, IDXGIFactory* factory)
  : m_swapchain(swapchain), m_device(device), m_factory(factory) {}


  DxgiSwapChain::~DxgiSwapChain() {}

  HRESULT STDMETHODCALLTYPE DxgiSwapChain::QueryInterface(REFIID riid, void** ppvObject) {
    if (ppvObject == nullptr)
      return E_POINTER;

    *ppvObject = nullptr;

    if (riid == __uuidof(IUnknown)
     || riid == __uuidof(IDXGIObject)
     || riid == __uuidof(IDXGIDeviceSubObject)
     || riid == __uuidof(IDXGISwapChain)) {
      *ppvObject = ref(this);
      return S_OK;
    }

    Logger::warn("DxgiSwapChain::QueryInterface: Unknown interface query");
    Logger::warn(str::format(riid));
    return E_NOINTERFACE;
  }


  HRESULT STDMETHODCALLTYPE DxgiSwapChain::GetParent(REFIID riid, void** ppParent) {
    return m_factory->QueryInterface(riid, ppParent);
  }


  HRESULT STDMETHODCALLTYPE DxgiSwapChain::GetDevice(REFIID riid, void** ppDevice) {
    return m_swapchain->GetDevice(riid, ppDevice);
  }


  HRESULT STDMETHODCALLTYPE DxgiSwapChain::GetBuffer(UINT Buffer, REFIID riid, void** ppSurface) {
		if (riid == __uuidof(ID3D10Texture2D)) {
			ID3D11Texture2D* pBackBuffer;
			HRESULT result = m_swapchain->GetBuffer(Buffer, __uuidof(ID3D11Texture2D), (void**)&pBackBuffer);

			*ppSurface = (void*) LookupOrCreateFromD3D11<ID3D10Texture2D, ID3D11Texture2D, D3D10Texture2D>(pBackBuffer, m_device.ptr());

			return result;
		}

    return m_swapchain->GetBuffer(Buffer, riid, ppSurface);
  }


  HRESULT STDMETHODCALLTYPE DxgiSwapChain::GetContainingOutput(IDXGIOutput** ppOutput) {
    return m_swapchain->GetContainingOutput(ppOutput);
  }


  HRESULT STDMETHODCALLTYPE DxgiSwapChain::GetDesc(DXGI_SWAP_CHAIN_DESC* pDesc) {
    return m_swapchain->GetDesc(pDesc);
  }


  HRESULT STDMETHODCALLTYPE DxgiSwapChain::GetFrameStatistics(DXGI_FRAME_STATISTICS* pStats) {
    return m_swapchain->GetFrameStatistics(pStats);
  }


  HRESULT STDMETHODCALLTYPE DxgiSwapChain::GetFullscreenState(
          BOOL*         pFullscreen,
          IDXGIOutput** ppTarget) {
    return m_swapchain->GetFullscreenState(pFullscreen, ppTarget);
  }


  HRESULT STDMETHODCALLTYPE DxgiSwapChain::GetLastPresentCount(UINT* pLastPresentCount) {
    return m_swapchain->GetLastPresentCount(pLastPresentCount);
  }


  HRESULT STDMETHODCALLTYPE DxgiSwapChain::Present(UINT SyncInterval, UINT Flags) {
    return m_swapchain->Present(SyncInterval, Flags);
  }


  HRESULT STDMETHODCALLTYPE DxgiSwapChain::ResizeBuffers(
          UINT        BufferCount,
          UINT        Width,
          UINT        Height,
          DXGI_FORMAT NewFormat,
          UINT        SwapChainFlags) {
    return m_swapchain->ResizeBuffers(BufferCount, Width, Height, NewFormat, SwapChainFlags);
  }

  HRESULT STDMETHODCALLTYPE DxgiSwapChain::ResizeTarget(
          const DXGI_MODE_DESC* pNewTargetParameters) {
    return m_swapchain->ResizeTarget(pNewTargetParameters);
  }


  HRESULT STDMETHODCALLTYPE DxgiSwapChain::SetFullscreenState(
          BOOL          Fullscreen,
          IDXGIOutput*  pTarget) {
    return m_swapchain->SetFullscreenState(Fullscreen, pTarget);
  }

}
