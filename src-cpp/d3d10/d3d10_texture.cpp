#include "d3d10_texture.h"
#include "d3d10_device.h"


namespace dxvk {

  HRESULT STDMETHODCALLTYPE D3D10Texture1D::QueryInterface(
          REFIID                    riid,
          void**                    ppvObject) {
    if (ppvObject == nullptr)
      return E_POINTER;

    *ppvObject = nullptr;

    if (riid == __uuidof(IUnknown)
     || riid == __uuidof(ID3D10DeviceChild)
     || riid == __uuidof(ID3D10Resource)
     || riid == __uuidof(ID3D10Texture1D)) {
      *ppvObject = ref(this);
      return S_OK;
    }

    if (riid == __uuidof(ID3D11DeviceChild)
     || riid == __uuidof(ID3D11Resource)
     || riid == __uuidof(ID3D11Texture1D)) {
      *ppvObject = ref(m_d3d11);
      return S_OK;
    }

    Logger::warn("D3D10Texture1D::QueryInterface: Unknown interface query");
    Logger::warn(str::format(riid));
    return E_NOINTERFACE;
  }


  void STDMETHODCALLTYPE D3D10Texture1D::GetType(
          D3D10_RESOURCE_DIMENSION* rType) {
    *rType = D3D10_RESOURCE_DIMENSION_TEXTURE1D;
  }


  void STDMETHODCALLTYPE D3D10Texture1D::SetEvictionPriority(
          UINT                      EvictionPriority) {
    m_d3d11->SetEvictionPriority(EvictionPriority);
  }


  UINT STDMETHODCALLTYPE D3D10Texture1D::GetEvictionPriority() {
    return m_d3d11->GetEvictionPriority();
  }


  HRESULT STDMETHODCALLTYPE D3D10Texture1D::Map(
          UINT                      Subresource,
          D3D10_MAP                 MapType,
          UINT                      MapFlags,
          void**                    ppData) {
    Com<ID3D11DeviceContext> ctx;
    GetD3D11Context(m_d3d11, &ctx);

    D3D11_MAPPED_SUBRESOURCE sr;
    HRESULT hr = ctx->Map(m_d3d11, Subresource,
      D3D11_MAP(MapType), MapFlags, &sr);

    if (FAILED(hr))
      return hr;

    if (ppData != nullptr) {
      *ppData = sr.pData;
      return S_OK;
    } return S_FALSE;
  }


  void STDMETHODCALLTYPE D3D10Texture1D::Unmap(
          UINT                      Subresource) {
    Com<ID3D11DeviceContext> ctx;
    GetD3D11Context(m_d3d11, &ctx);

    ctx->Unmap(m_d3d11, Subresource);
  }


  void STDMETHODCALLTYPE D3D10Texture1D::GetDesc(
          D3D10_TEXTURE1D_DESC*     pDesc) {
    D3D11_TEXTURE1D_DESC d3d11Desc;
    m_d3d11->GetDesc(&d3d11Desc);

    pDesc->Width           = d3d11Desc.Width;
    pDesc->MipLevels       = d3d11Desc.MipLevels;
    pDesc->ArraySize       = d3d11Desc.ArraySize;
    pDesc->Format          = d3d11Desc.Format;
    pDesc->Usage           = D3D10_USAGE(d3d11Desc.Usage);
    pDesc->BindFlags       = d3d11Desc.BindFlags;
    pDesc->CPUAccessFlags  = d3d11Desc.CPUAccessFlags;
    pDesc->MiscFlags       = ConvertD3D11ResourceFlags(d3d11Desc.MiscFlags);
  }


  HRESULT STDMETHODCALLTYPE D3D10Texture2D::QueryInterface(
          REFIID                    riid,
          void**                    ppvObject) {
    if (ppvObject == nullptr)
      return E_POINTER;

    *ppvObject = nullptr;

    if (riid == __uuidof(IUnknown)
     || riid == __uuidof(ID3D10DeviceChild)
     || riid == __uuidof(ID3D10Resource)
     || riid == __uuidof(ID3D10Texture2D)) {
      *ppvObject = ref(this);
      return S_OK;
    }

    if (riid == __uuidof(ID3D11DeviceChild)
     || riid == __uuidof(ID3D11Resource)
     || riid == __uuidof(ID3D11Texture2D)) {
      *ppvObject = ref(m_d3d11);
      return S_OK;
    }

    Logger::warn("D3D10Texture2D::QueryInterface: Unknown interface query");
    Logger::warn(str::format(riid));
    return E_NOINTERFACE;
  }


  void STDMETHODCALLTYPE D3D10Texture2D::GetType(
          D3D10_RESOURCE_DIMENSION* rType) {
    *rType = D3D10_RESOURCE_DIMENSION_TEXTURE2D;
  }


  void STDMETHODCALLTYPE D3D10Texture2D::SetEvictionPriority(
          UINT                      EvictionPriority) {
    m_d3d11->SetEvictionPriority(EvictionPriority);
  }


  UINT STDMETHODCALLTYPE D3D10Texture2D::GetEvictionPriority() {
    return m_d3d11->GetEvictionPriority();
  }


  HRESULT STDMETHODCALLTYPE D3D10Texture2D::Map(
          UINT                      Subresource,
          D3D10_MAP                 MapType,
          UINT                      MapFlags,
          D3D10_MAPPED_TEXTURE2D*   pMappedTex2D) {
    Com<ID3D11DeviceContext> ctx;
    GetD3D11Context(m_d3d11, &ctx);

    D3D11_MAPPED_SUBRESOURCE sr;
    HRESULT hr = ctx->Map(m_d3d11, Subresource,
      D3D11_MAP(MapType), MapFlags, &sr);

    if (FAILED(hr))
      return hr;

    if (pMappedTex2D != nullptr) {
      pMappedTex2D->pData    = sr.pData;
      pMappedTex2D->RowPitch = sr.RowPitch;
      return S_OK;
    } return S_FALSE;
  }


  void STDMETHODCALLTYPE D3D10Texture2D::Unmap(
          UINT                      Subresource) {
    Com<ID3D11DeviceContext> ctx;
    GetD3D11Context(m_d3d11, &ctx);

    ctx->Unmap(m_d3d11, Subresource);
  }


  void STDMETHODCALLTYPE D3D10Texture2D::GetDesc(
          D3D10_TEXTURE2D_DESC*     pDesc) {
    D3D11_TEXTURE2D_DESC d3d11Desc;
    m_d3d11->GetDesc(&d3d11Desc);

    pDesc->Width           = d3d11Desc.Width;
    pDesc->Height          = d3d11Desc.Height;
    pDesc->MipLevels       = d3d11Desc.MipLevels;
    pDesc->ArraySize       = d3d11Desc.ArraySize;
    pDesc->Format          = d3d11Desc.Format;
    pDesc->SampleDesc      = d3d11Desc.SampleDesc;
    pDesc->Usage           = D3D10_USAGE(d3d11Desc.Usage);
    pDesc->BindFlags       = d3d11Desc.BindFlags;
    pDesc->CPUAccessFlags  = d3d11Desc.CPUAccessFlags;
    pDesc->MiscFlags       = ConvertD3D11ResourceFlags(d3d11Desc.MiscFlags);
  }


  HRESULT STDMETHODCALLTYPE D3D10Texture3D::QueryInterface(
          REFIID                    riid,
          void**                    ppvObject) {
    if (ppvObject == nullptr)
      return E_POINTER;

    *ppvObject = nullptr;

    if (riid == __uuidof(IUnknown)
     || riid == __uuidof(ID3D10DeviceChild)
     || riid == __uuidof(ID3D10Resource)
     || riid == __uuidof(ID3D10Texture3D)) {
      *ppvObject = ref(this);
      return S_OK;
    }

    if (riid == __uuidof(ID3D11DeviceChild)
     || riid == __uuidof(ID3D11Resource)
     || riid == __uuidof(ID3D11Texture3D)) {
      *ppvObject = ref(m_d3d11);
      return S_OK;
    }

    Logger::warn("D3D10Texture3D::QueryInterface: Unknown interface query");
    Logger::warn(str::format(riid));
    return E_NOINTERFACE;
  }


  void STDMETHODCALLTYPE D3D10Texture3D::GetType(
          D3D10_RESOURCE_DIMENSION* rType) {
    *rType = D3D10_RESOURCE_DIMENSION_TEXTURE3D;
  }


  void STDMETHODCALLTYPE D3D10Texture3D::SetEvictionPriority(
          UINT                      EvictionPriority) {
    m_d3d11->SetEvictionPriority(EvictionPriority);
  }


  UINT STDMETHODCALLTYPE D3D10Texture3D::GetEvictionPriority() {
    return m_d3d11->GetEvictionPriority();
  }


  HRESULT STDMETHODCALLTYPE D3D10Texture3D::Map(
          UINT                      Subresource,
          D3D10_MAP                 MapType,
          UINT                      MapFlags,
          D3D10_MAPPED_TEXTURE3D*   pMappedTex3D) {
    Com<ID3D11DeviceContext> ctx;
    GetD3D11Context(m_d3d11, &ctx);

    D3D11_MAPPED_SUBRESOURCE sr;
    HRESULT hr = ctx->Map(m_d3d11, Subresource,
      D3D11_MAP(MapType), MapFlags, &sr);

    if (FAILED(hr))
      return hr;

    if (pMappedTex3D != nullptr) {
      pMappedTex3D->pData      = sr.pData;
      pMappedTex3D->RowPitch   = sr.RowPitch;
      pMappedTex3D->DepthPitch = sr.DepthPitch;
      return S_OK;
    } return S_FALSE;
  }


  void STDMETHODCALLTYPE D3D10Texture3D::Unmap(
          UINT                      Subresource) {
    Com<ID3D11DeviceContext> ctx;
    GetD3D11Context(m_d3d11, &ctx);

    ctx->Unmap(m_d3d11, Subresource);
  }


  void STDMETHODCALLTYPE D3D10Texture3D::GetDesc(
          D3D10_TEXTURE3D_DESC*     pDesc) {
    D3D11_TEXTURE3D_DESC d3d11Desc;
    m_d3d11->GetDesc(&d3d11Desc);

    pDesc->Width           = d3d11Desc.Width;
    pDesc->Height          = d3d11Desc.Height;
    pDesc->Depth           = d3d11Desc.Depth;
    pDesc->MipLevels       = d3d11Desc.MipLevels;
    pDesc->Format          = d3d11Desc.Format;
    pDesc->Usage           = D3D10_USAGE(d3d11Desc.Usage);
    pDesc->BindFlags       = d3d11Desc.BindFlags;
    pDesc->CPUAccessFlags  = d3d11Desc.CPUAccessFlags;
    pDesc->MiscFlags       = ConvertD3D11ResourceFlags(d3d11Desc.MiscFlags);
  }

}