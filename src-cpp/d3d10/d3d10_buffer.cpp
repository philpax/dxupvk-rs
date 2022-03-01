#include "d3d10_buffer.h"

namespace dxvk {

  HRESULT STDMETHODCALLTYPE D3D10Buffer::QueryInterface(
          REFIID                    riid,
          void**                    ppvObject) {
    if (ppvObject == nullptr)
      return E_POINTER;

    *ppvObject = nullptr;

    if (riid == __uuidof(IUnknown)
     || riid == __uuidof(ID3D10DeviceChild)
     || riid == __uuidof(ID3D10Resource)
     || riid == __uuidof(ID3D10Buffer)) {
      *ppvObject = ref(this);
      return S_OK;
    }

    if (riid == __uuidof(ID3D11DeviceChild)
     || riid == __uuidof(ID3D11Resource)
     || riid == __uuidof(ID3D11Buffer)) {
      *ppvObject = ref(m_d3d11);
      return S_OK;
    }

    Logger::warn("D3D10Buffer::QueryInterface: Unknown interface query");
    Logger::warn(str::format(riid));
    return E_NOINTERFACE;
  }


  void STDMETHODCALLTYPE D3D10Buffer::GetType(
          D3D10_RESOURCE_DIMENSION* rType) {
    *rType = D3D10_RESOURCE_DIMENSION_BUFFER;
  }


  void STDMETHODCALLTYPE D3D10Buffer::SetEvictionPriority(
          UINT                      EvictionPriority) {
    m_d3d11->SetEvictionPriority(EvictionPriority);
  }


  UINT STDMETHODCALLTYPE D3D10Buffer::GetEvictionPriority() {
    return m_d3d11->GetEvictionPriority();
  }


  HRESULT STDMETHODCALLTYPE D3D10Buffer::Map(
          D3D10_MAP                 MapType,
          UINT                      MapFlags,
          void**                    ppData) {
    Com<ID3D11DeviceContext> ctx;
    GetD3D11Context(m_d3d11, &ctx);

    D3D11_MAPPED_SUBRESOURCE sr;
    HRESULT hr = ctx->Map(m_d3d11, 0,
      D3D11_MAP(MapType), MapFlags, &sr);

    if (FAILED(hr))
      return hr;

    if (ppData != nullptr) {
      *ppData = sr.pData;
      return S_OK;
    } return S_FALSE;
  }


  void STDMETHODCALLTYPE D3D10Buffer::Unmap() {
    Com<ID3D11DeviceContext> ctx;
    GetD3D11Context(m_d3d11, &ctx);

    ctx->Unmap(m_d3d11, 0);
  }


  void STDMETHODCALLTYPE D3D10Buffer::GetDesc(
          D3D10_BUFFER_DESC*        pDesc) {
    D3D11_BUFFER_DESC d3d11Desc;
    m_d3d11->GetDesc(&d3d11Desc);

    pDesc->ByteWidth       = d3d11Desc.ByteWidth;
    pDesc->Usage           = D3D10_USAGE(d3d11Desc.Usage);
    pDesc->BindFlags       = d3d11Desc.BindFlags;
    pDesc->CPUAccessFlags  = d3d11Desc.CPUAccessFlags;
    pDesc->MiscFlags       = ConvertD3D11ResourceFlags(d3d11Desc.MiscFlags);
  }

}
