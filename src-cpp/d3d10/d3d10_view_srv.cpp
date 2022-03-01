#include "d3d10_view_srv.h"


namespace dxvk {

  HRESULT STDMETHODCALLTYPE D3D10ShaderResourceView::QueryInterface(
          REFIID                    riid,
          void**                    ppvObject) {
    if (ppvObject == nullptr)
      return E_POINTER;

    *ppvObject = nullptr;

    if (riid == __uuidof(IUnknown)
     || riid == __uuidof(ID3D10DeviceChild)
     || riid == __uuidof(ID3D10View)
     || riid == __uuidof(ID3D10ShaderResourceView)) {
      *ppvObject = ref(this);
      return S_OK;
    }

    if (riid == __uuidof(ID3D11DeviceChild)
     || riid == __uuidof(ID3D11View)
     || riid == __uuidof(ID3D11ShaderResourceView)) {
      *ppvObject = ref(m_d3d11);
      return S_OK;
    }

    Logger::warn("D3D10ShaderResourceView::QueryInterface: Unknown interface query");
    Logger::warn(str::format(riid));
    return E_NOINTERFACE;
  }


  void STDMETHODCALLTYPE D3D10ShaderResourceView::GetResource(
          ID3D10Resource**          ppResource) {
    GetD3D10ResourceFromView(m_d3d11, ppResource);
  }


  void STDMETHODCALLTYPE D3D10ShaderResourceView::GetDesc(
          D3D10_SHADER_RESOURCE_VIEW_DESC* pDesc) {
    static_assert(sizeof(D3D10_SHADER_RESOURCE_VIEW_DESC) ==
                  sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));

    m_d3d11->GetDesc(reinterpret_cast<D3D11_SHADER_RESOURCE_VIEW_DESC*>(pDesc));

    if (pDesc->ViewDimension > D3D10_SRV_DIMENSION_TEXTURECUBE)
      pDesc->ViewDimension = D3D10_SRV_DIMENSION_UNKNOWN;
  }


  void STDMETHODCALLTYPE D3D10ShaderResourceView::GetDesc1(
          D3D10_SHADER_RESOURCE_VIEW_DESC1* pDesc) {
    static_assert(sizeof(D3D10_SHADER_RESOURCE_VIEW_DESC1) ==
                  sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));

    m_d3d11->GetDesc(reinterpret_cast<D3D11_SHADER_RESOURCE_VIEW_DESC*>(pDesc));

    if (pDesc->ViewDimension > D3D10_1_SRV_DIMENSION_TEXTURECUBEARRAY)
      pDesc->ViewDimension = D3D10_1_SRV_DIMENSION_UNKNOWN;
  }

}