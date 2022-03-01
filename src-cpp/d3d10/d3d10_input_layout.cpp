#include "d3d10_input_layout.h"


namespace dxvk {

  HRESULT STDMETHODCALLTYPE D3D10InputLayout::QueryInterface(
          REFIID                    riid,
          void**                    ppvObject) {
    if (ppvObject == nullptr)
      return E_POINTER;

    *ppvObject = nullptr;

    if (riid == __uuidof(IUnknown)
     || riid == __uuidof(ID3D10DeviceChild)
     || riid == __uuidof(ID3D10InputLayout)) {
      *ppvObject = ref(this);
      return S_OK;
    }

    if (riid == __uuidof(ID3D11DeviceChild)
     || riid == __uuidof(ID3D11InputLayout)) {
      *ppvObject = ref(m_d3d11);
      return S_OK;
    }

    Logger::warn("D3D10InputLayout::QueryInterface: Unknown interface query");
    Logger::warn(str::format(riid));
    return E_NOINTERFACE;
  }

}