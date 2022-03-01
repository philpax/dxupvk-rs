#include "d3d10_view_rtv.h"


namespace dxvk {

  HRESULT STDMETHODCALLTYPE D3D10RenderTargetView::QueryInterface(
          REFIID                    riid,
          void**                    ppvObject) {
    if (ppvObject == nullptr)
      return E_POINTER;

    *ppvObject = nullptr;

    if (riid == __uuidof(IUnknown)
     || riid == __uuidof(ID3D10DeviceChild)
     || riid == __uuidof(ID3D10View)
     || riid == __uuidof(ID3D10RenderTargetView)) {
      *ppvObject = ref(this);
      return S_OK;
    }

    if (riid == __uuidof(ID3D11DeviceChild)
     || riid == __uuidof(ID3D11View)
     || riid == __uuidof(ID3D11RenderTargetView)) {
      *ppvObject = ref(m_d3d11);
      return S_OK;
    }

    Logger::warn("D3D10RenderTargetView::QueryInterface: Unknown interface query");
    Logger::warn(str::format(riid));
    return E_NOINTERFACE;
  }


  void STDMETHODCALLTYPE D3D10RenderTargetView::GetResource(
          ID3D10Resource**          ppResource) {
    GetD3D10ResourceFromView(m_d3d11, ppResource);
  }


  void STDMETHODCALLTYPE D3D10RenderTargetView::GetDesc(
          D3D10_RENDER_TARGET_VIEW_DESC* pDesc) {
    static_assert(sizeof(D3D10_RENDER_TARGET_VIEW_DESC) ==
                  sizeof(D3D11_RENDER_TARGET_VIEW_DESC));

    m_d3d11->GetDesc(reinterpret_cast<D3D11_RENDER_TARGET_VIEW_DESC*>(pDesc));
  }

}