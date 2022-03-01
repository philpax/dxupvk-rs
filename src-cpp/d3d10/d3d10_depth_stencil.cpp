#include "d3d10_depth_stencil.h"


namespace dxvk {

  HRESULT STDMETHODCALLTYPE D3D10DepthStencilState::QueryInterface(
          REFIID                    riid,
          void**                    ppvObject) {
    if (ppvObject == nullptr)
      return E_POINTER;

    *ppvObject = nullptr;

    if (riid == __uuidof(IUnknown)
     || riid == __uuidof(ID3D11DeviceChild)
     || riid == __uuidof(ID3D11DepthStencilState)) {
      *ppvObject = ref(this);
      return S_OK;
    }

    if (riid == __uuidof(ID3D10DeviceChild)
     || riid == __uuidof(ID3D10DepthStencilState)) {
      *ppvObject = ref(this);
      return S_OK;
    }

    Logger::warn("D3D10DepthStencilState::QueryInterface: Unknown interface query");
    Logger::warn(str::format(riid));
    return E_NOINTERFACE;
  }


  void STDMETHODCALLTYPE D3D10DepthStencilState::GetDesc(
          D3D10_DEPTH_STENCIL_DESC* pDesc) {
    static_assert(sizeof(D3D10_DEPTH_STENCIL_DESC) == sizeof(D3D11_DEPTH_STENCIL_DESC));
    m_d3d11->GetDesc(reinterpret_cast<D3D11_DEPTH_STENCIL_DESC*>(pDesc));
  }

}