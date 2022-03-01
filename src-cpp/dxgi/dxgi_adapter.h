#pragma once

#include <memory>
#include <mutex>

#include "dxgi_object.h"

#include "../util/util_time.h"

namespace dxvk {

  class DECLSPEC_UUID("61125e1b-c083-4e5f-a582-5c5a11a61575")
  DxgiAdapter : public DxgiObject<IDXGIAdapter> {

  public:

    DxgiAdapter(IDXGIAdapter* adapter, IDXGIFactory* factory);

    ~DxgiAdapter();

    HRESULT STDMETHODCALLTYPE QueryInterface(
            REFIID                    riid,
            void**                    ppvObject) final;

    HRESULT STDMETHODCALLTYPE GetParent(
            REFIID                    riid,
            void**                    ppParent) final;

    HRESULT STDMETHODCALLTYPE CheckInterfaceSupport(
            REFGUID                   InterfaceName,
            LARGE_INTEGER*            pUMDVersion) final;

    HRESULT STDMETHODCALLTYPE EnumOutputs(
            UINT                      Output,
            IDXGIOutput**             pStats) final;

    HRESULT STDMETHODCALLTYPE GetDesc(
            DXGI_ADAPTER_DESC*        pDesc) final;

    IDXGIAdapter* GetOriginalAdapter() { return m_adapter.ref(); }

  private:

    Com<IDXGIAdapter>             m_adapter;
    Com<IDXGIFactory>               m_factory;

  };

}
