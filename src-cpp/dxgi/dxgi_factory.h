#pragma once

#include "dxgi_include.h"
#include "dxgi_object.h"

namespace dxvk {

  class DxgiFactory : public DxgiObject<IDXGIFactory> {

  public:

    DxgiFactory(IDXGIFactory* parent);
    ~DxgiFactory();

    HRESULT STDMETHODCALLTYPE QueryInterface(
            REFIID                riid,
            void**                ppvObject) final;

    HRESULT STDMETHODCALLTYPE GetParent(
            REFIID                riid,
            void**                ppParent) final;

    HRESULT STDMETHODCALLTYPE CreateSoftwareAdapter(
            HMODULE               Module,
            IDXGIAdapter**        ppAdapter) final;

    HRESULT STDMETHODCALLTYPE CreateSwapChain(
            IUnknown*             pDevice,
            DXGI_SWAP_CHAIN_DESC* pDesc,
            IDXGISwapChain**      ppSwapChain) final;

    HRESULT STDMETHODCALLTYPE EnumAdapters(
            UINT                  Adapter,
            IDXGIAdapter**        ppAdapter) final;

    HRESULT STDMETHODCALLTYPE GetWindowAssociation(
            HWND*                 pWindowHandle) final;

    HRESULT STDMETHODCALLTYPE MakeWindowAssociation(
            HWND                  WindowHandle,
            UINT                  Flags) final;

  private:

    Com<IDXGIFactory> m_factory;

  };

}
