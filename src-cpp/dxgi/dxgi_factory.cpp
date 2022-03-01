#include "dxgi_factory.h"
#include "dxgi_swapchain.h"
#include "dxgi_adapter.h"

#include "../d3d10/d3d10_device.h"

namespace dxvk {

  DxgiFactory::DxgiFactory(IDXGIFactory* factory)
    : m_factory(factory) { }


  DxgiFactory::~DxgiFactory() {

  }


  HRESULT STDMETHODCALLTYPE DxgiFactory::QueryInterface(REFIID riid, void** ppvObject) {
    if (ppvObject == nullptr)
      return E_POINTER;

    *ppvObject = nullptr;

    if (riid == __uuidof(IUnknown)
     || riid == __uuidof(IDXGIObject)
     || riid == __uuidof(IDXGIFactory)) {
      *ppvObject = ref(this);
      return S_OK;
    }

    Logger::warn("DxgiFactory::QueryInterface: Unknown interface query");
    Logger::warn(str::format(riid));
    return E_NOINTERFACE;
  }


  HRESULT STDMETHODCALLTYPE DxgiFactory::GetParent(REFIID riid, void** ppParent) {
    InitReturnPtr(ppParent);

    Logger::warn("DxgiFactory::GetParent: Unknown interface query");
    return E_NOINTERFACE;
  }


  HRESULT STDMETHODCALLTYPE DxgiFactory::CreateSoftwareAdapter(
          HMODULE         Module,
          IDXGIAdapter**  ppAdapter) {
    InitReturnPtr(ppAdapter);

    if (ppAdapter == nullptr)
      return DXGI_ERROR_INVALID_CALL;

    Logger::err("DXGI: CreateSoftwareAdapter: Software adapters not supported");
    return DXGI_ERROR_UNSUPPORTED;
  }


  HRESULT STDMETHODCALLTYPE DxgiFactory::CreateSwapChain(
          IUnknown*             pDevice,
          DXGI_SWAP_CHAIN_DESC* pDesc,
          IDXGISwapChain**      ppSwapChain) {
    if (ppSwapChain == nullptr || pDesc == nullptr || pDevice == nullptr)
      return DXGI_ERROR_INVALID_CALL;

    Com<D3D10Device> device = static_cast<D3D10Device*>(pDevice);
    IDXGISwapChain* originalSwapchain = nullptr;
    HRESULT hr = m_factory->CreateSwapChain(device->GetD3D11Iface(), pDesc, &originalSwapchain);

    if (originalSwapchain) {
      auto* ourSwapchain = new DxgiSwapChain(ref(originalSwapchain), device.ref(), this);
      if (ppSwapChain)
        *ppSwapChain = ourSwapchain;
    }

    return hr;
  }


  HRESULT STDMETHODCALLTYPE DxgiFactory::EnumAdapters(
          UINT            Adapter,
          IDXGIAdapter**  ppAdapter) {
    if (ppAdapter)
      *ppAdapter = nullptr;

    IDXGIAdapter* originalAdapter = nullptr;
    HRESULT hr = m_factory->EnumAdapters(Adapter, &originalAdapter);
    if (originalAdapter) {
      Com<IDXGIAdapter> ourAdapter = new DxgiAdapter(originalAdapter, this);
      if (ppAdapter)
        *ppAdapter = ourAdapter.ref();
    }
    return hr;
  }


  HRESULT STDMETHODCALLTYPE DxgiFactory::GetWindowAssociation(HWND *pWindowHandle) {
    return m_factory->GetWindowAssociation(pWindowHandle);
  }


  HRESULT STDMETHODCALLTYPE DxgiFactory::MakeWindowAssociation(HWND WindowHandle, UINT Flags) {
    return m_factory->MakeWindowAssociation(WindowHandle, Flags);
  }


}
