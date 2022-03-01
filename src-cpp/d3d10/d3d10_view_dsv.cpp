#include "d3d10_view_dsv.h"


namespace dxvk {

  HRESULT STDMETHODCALLTYPE D3D10DepthStencilView::QueryInterface(
          REFIID                    riid,
          void**                    ppvObject) {
    if (ppvObject == nullptr)
      return E_POINTER;

    *ppvObject = nullptr;

    if (riid == __uuidof(IUnknown)
     || riid == __uuidof(ID3D10DeviceChild)
     || riid == __uuidof(ID3D10View)
     || riid == __uuidof(ID3D10DepthStencilView)) {
      *ppvObject = ref(this);
      return S_OK;
    }

    if (riid == __uuidof(ID3D11DeviceChild)
     || riid == __uuidof(ID3D11View)
     || riid == __uuidof(ID3D11DepthStencilView)) {
      *ppvObject = ref(m_d3d11);
      return S_OK;
    }

    Logger::warn("D3D10DepthStencilView::QueryInterface: Unknown interface query");
    Logger::warn(str::format(riid));
    return E_NOINTERFACE;
  }


  void STDMETHODCALLTYPE D3D10DepthStencilView::GetResource(
          ID3D10Resource**          ppResource) {
    GetD3D10ResourceFromView(m_d3d11, ppResource);
  }


  void STDMETHODCALLTYPE D3D10DepthStencilView::GetDesc(
          D3D10_DEPTH_STENCIL_VIEW_DESC* pDesc) {
    D3D11_DEPTH_STENCIL_VIEW_DESC d3d11Desc;
    m_d3d11->GetDesc(&d3d11Desc);

    pDesc->ViewDimension = D3D10_DSV_DIMENSION(d3d11Desc.ViewDimension);
    pDesc->Format        = d3d11Desc.Format;

    switch (d3d11Desc.ViewDimension) {
      case D3D11_DSV_DIMENSION_UNKNOWN:
        break;

      case D3D11_DSV_DIMENSION_TEXTURE1D:
        pDesc->Texture1D.MipSlice               = d3d11Desc.Texture1D.MipSlice;
        break;

      case D3D11_DSV_DIMENSION_TEXTURE1DARRAY:
        pDesc->Texture1DArray.MipSlice          = d3d11Desc.Texture1DArray.MipSlice;
        pDesc->Texture1DArray.FirstArraySlice   = d3d11Desc.Texture1DArray.FirstArraySlice;
        pDesc->Texture1DArray.ArraySize         = d3d11Desc.Texture1DArray.ArraySize;
        break;

      case D3D11_DSV_DIMENSION_TEXTURE2D:
        pDesc->Texture2D.MipSlice               = d3d11Desc.Texture2D.MipSlice;
        break;

      case D3D11_DSV_DIMENSION_TEXTURE2DARRAY:
        pDesc->Texture2DArray.MipSlice          = d3d11Desc.Texture2DArray.MipSlice;
        pDesc->Texture2DArray.FirstArraySlice   = d3d11Desc.Texture2DArray.FirstArraySlice;
        pDesc->Texture2DArray.ArraySize         = d3d11Desc.Texture2DArray.ArraySize;
        break;

      case D3D11_DSV_DIMENSION_TEXTURE2DMS:
        break;

      case D3D11_DSV_DIMENSION_TEXTURE2DMSARRAY:
        pDesc->Texture2DMSArray.FirstArraySlice = d3d11Desc.Texture2DMSArray.FirstArraySlice;
        pDesc->Texture2DMSArray.ArraySize       = d3d11Desc.Texture2DMSArray.ArraySize;
        break;
    }
  }

}