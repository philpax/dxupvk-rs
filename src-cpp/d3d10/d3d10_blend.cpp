#include "d3d10_blend.h"

namespace dxvk {

  HRESULT STDMETHODCALLTYPE D3D10BlendState::QueryInterface(
          REFIID                    riid,
          void**                    ppvObject) {
    if (ppvObject == nullptr)
      return E_POINTER;

    *ppvObject = nullptr;

    if (riid == __uuidof(IUnknown)
     || riid == __uuidof(ID3D10DeviceChild)
     || riid == __uuidof(ID3D10BlendState)
     || riid == __uuidof(ID3D10BlendState1)) {
      *ppvObject = ref(this);
      return S_OK;
    }

    if (riid == __uuidof(ID3D11DeviceChild)
     || riid == __uuidof(ID3D11BlendState)
     || riid == __uuidof(ID3D11BlendState1)) {
      *ppvObject = ref(m_d3d11);
      return S_OK;
    }

    Logger::warn("D3D10BlendState::QueryInterface: Unknown interface query");
    Logger::warn(str::format(riid));
    return E_NOINTERFACE;
  }


  void STDMETHODCALLTYPE D3D10BlendState::GetDesc(
          D3D10_BLEND_DESC*         pDesc) {
    D3D11_BLEND_DESC d3d11Desc;
    m_d3d11->GetDesc(&d3d11Desc);

    pDesc->AlphaToCoverageEnable  = d3d11Desc.AlphaToCoverageEnable;
    pDesc->SrcBlend               = D3D10_BLEND   (d3d11Desc.RenderTarget[0].SrcBlend);
    pDesc->DestBlend              = D3D10_BLEND   (d3d11Desc.RenderTarget[0].DestBlend);
    pDesc->BlendOp                = D3D10_BLEND_OP(d3d11Desc.RenderTarget[0].BlendOp);
    pDesc->SrcBlendAlpha          = D3D10_BLEND   (d3d11Desc.RenderTarget[0].SrcBlendAlpha);
    pDesc->DestBlendAlpha         = D3D10_BLEND   (d3d11Desc.RenderTarget[0].DestBlendAlpha);
    pDesc->BlendOpAlpha           = D3D10_BLEND_OP(d3d11Desc.RenderTarget[0].BlendOpAlpha);

    for (uint32_t i = 0; i < 8; i++) {
      uint32_t srcId = d3d11Desc.IndependentBlendEnable ? i : 0;
      pDesc->BlendEnable[i]           = d3d11Desc.RenderTarget[srcId].BlendEnable;
      pDesc->RenderTargetWriteMask[i] = d3d11Desc.RenderTarget[srcId].RenderTargetWriteMask;
    }
  }


  void STDMETHODCALLTYPE D3D10BlendState::GetDesc1(
          D3D10_BLEND_DESC1*        pDesc) {
    static_assert(sizeof(D3D10_BLEND_DESC1) == sizeof(D3D11_BLEND_DESC));
    m_d3d11->GetDesc(reinterpret_cast<D3D11_BLEND_DESC*>(pDesc));
  }

}