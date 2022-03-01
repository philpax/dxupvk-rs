#include "dxgi_adapter.h"

namespace dxvk {

  DxgiAdapter::DxgiAdapter(IDXGIAdapter* adapter, IDXGIFactory* factory)
  : m_adapter(adapter), m_factory(factory) {

  }


  DxgiAdapter::~DxgiAdapter() {

  }


  HRESULT STDMETHODCALLTYPE DxgiAdapter::GetParent(REFIID riid, void** ppParent) {
    return m_factory->QueryInterface(riid, ppParent);
  }


  HRESULT STDMETHODCALLTYPE DxgiAdapter::QueryInterface(REFIID riid, void** ppvObject) {
    if (ppvObject == nullptr)
      return E_POINTER;

    *ppvObject = nullptr;

    if (riid == __uuidof(IUnknown)
    || riid == __uuidof(IDXGIObject)
    || riid == __uuidof(IDXGIDeviceSubObject)
    || riid == __uuidof(IDXGIAdapter)
    || riid == __uuidof(DxgiAdapter)) {
      *ppvObject = ref(this);
      return S_OK;
    }

    Logger::warn("DxgiAdapter::QueryInterface: Unknown interface query");
    Logger::warn(str::format(riid));
    return E_NOINTERFACE;
  }


  HRESULT STDMETHODCALLTYPE DxgiAdapter::GetDesc(DXGI_ADAPTER_DESC* pDesc) {
    HRESULT hr = m_adapter->GetDesc(pDesc);
    // empty out the VendorId so that JC2 doesn't do any vendor-specific hacks
    if (pDesc)
      pDesc->VendorId = 0;
    return hr;
  }


  HRESULT STDMETHODCALLTYPE DxgiAdapter::CheckInterfaceSupport(REFGUID InterfaceName, LARGE_INTEGER* pUMDVersion) {
    return m_adapter->CheckInterfaceSupport(InterfaceName, pUMDVersion);
  }


  HRESULT STDMETHODCALLTYPE DxgiAdapter::EnumOutputs(UINT Output, IDXGIOutput** pStats) {
    return m_adapter->EnumOutputs(Output, pStats);
  }

}