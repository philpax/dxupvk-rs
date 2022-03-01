#include "d3d10_sampler.h"


namespace dxvk {

  HRESULT STDMETHODCALLTYPE D3D10SamplerState::QueryInterface(
          REFIID                    riid,
          void**                    ppvObject) {
    if (ppvObject == nullptr)
      return E_POINTER;

    *ppvObject = nullptr;

    if (riid == __uuidof(IUnknown)
     || riid == __uuidof(ID3D10DeviceChild)
     || riid == __uuidof(ID3D10SamplerState)) {
      *ppvObject = ref(this);
      return S_OK;
    }

    if (riid == __uuidof(ID3D11DeviceChild)
     || riid == __uuidof(ID3D11SamplerState)) {
      *ppvObject = ref(m_d3d11);
      return S_OK;
    }

    Logger::warn("D3D10SamplerState::QueryInterface: Unknown interface query");
    Logger::warn(str::format(riid));
    return E_NOINTERFACE;
  }


  void STDMETHODCALLTYPE D3D10SamplerState::GetDesc(
          D3D10_SAMPLER_DESC*       pDesc) {
    D3D11_SAMPLER_DESC d3d11Desc;
    m_d3d11->GetDesc(&d3d11Desc);

    pDesc->Filter            = D3D10_FILTER(d3d11Desc.Filter);
    pDesc->AddressU          = D3D10_TEXTURE_ADDRESS_MODE(d3d11Desc.AddressU);
    pDesc->AddressV          = D3D10_TEXTURE_ADDRESS_MODE(d3d11Desc.AddressV);
    pDesc->AddressW          = D3D10_TEXTURE_ADDRESS_MODE(d3d11Desc.AddressW);
    pDesc->MipLODBias        = d3d11Desc.MipLODBias;
    pDesc->MaxAnisotropy     = d3d11Desc.MaxAnisotropy;
    pDesc->ComparisonFunc    = D3D10_COMPARISON_FUNC(d3d11Desc.ComparisonFunc);
    pDesc->MinLOD            = d3d11Desc.MinLOD;
    pDesc->MaxLOD            = d3d11Desc.MaxLOD;

    for (uint32_t i = 0; i < 4; i++)
      pDesc->BorderColor[i] = d3d11Desc.BorderColor[i];
  }

}