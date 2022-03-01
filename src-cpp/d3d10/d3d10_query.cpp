#include "d3d10_query.h"
#include "d3d10_device.h"


namespace dxvk {

  HRESULT STDMETHODCALLTYPE D3D10Query::QueryInterface(
          REFIID                    riid,
          void**                    ppvObject) {
    if (ppvObject == nullptr)
      return E_POINTER;

    *ppvObject = nullptr;

    if (riid == __uuidof(IUnknown)
     || riid == __uuidof(ID3D10DeviceChild)
     || riid == __uuidof(ID3D10Asynchronous)
     || riid == __uuidof(ID3D10Query)) {
      *ppvObject = ref(this);
      return S_OK;
    }

    if (riid == __uuidof(IUnknown)
     || riid == __uuidof(ID3D11DeviceChild)
     || riid == __uuidof(ID3D11Asynchronous)
     || riid == __uuidof(ID3D11Query)) {
      *ppvObject = ref(m_d3d11);
      return S_OK;
    }

    // if (m_desc.Query == D3D11_QUERY_OCCLUSION_PREDICATE) {
    //   if (riid == __uuidof(ID3D11Predicate)) {
    //     *ppvObject = AsPredicate(ref(this));
    //     return S_OK;
    //   }

    //   if (riid == __uuidof(ID3D10Predicate)) {
    //     *ppvObject = ref(&m_d3d10);
    //     return S_OK;
    //   }
    // }

    Logger::warn("D3D10Query: Unknown interface query");
    Logger::warn(str::format(riid));
    return E_NOINTERFACE;
  }


  void STDMETHODCALLTYPE D3D10Query::Begin() {
    Com<ID3D11DeviceContext> ctx;
    GetD3D11Context(m_d3d11, &ctx);

    ctx->Begin(m_d3d11);
  }


  void STDMETHODCALLTYPE D3D10Query::End() {
    Com<ID3D11DeviceContext> ctx;
    GetD3D11Context(m_d3d11, &ctx);

    ctx->End(m_d3d11);
  }


  HRESULT STDMETHODCALLTYPE D3D10Query::GetData(
          void*                     pData,
          UINT                      DataSize,
          UINT                      GetDataFlags) {
    Com<ID3D11DeviceContext> ctx;
    GetD3D11Context(m_d3d11, &ctx);

    return ctx->GetData(m_d3d11,
      pData, DataSize, GetDataFlags);
  }


  UINT STDMETHODCALLTYPE D3D10Query::GetDataSize() {
    return m_d3d11->GetDataSize();
  }


  void STDMETHODCALLTYPE D3D10Query::GetDesc(
          D3D10_QUERY_DESC*         pDesc) {
    D3D11_QUERY_DESC d3d11Desc;
    m_d3d11->GetDesc(&d3d11Desc);

    pDesc->Query      = D3D10_QUERY(d3d11Desc.Query);
    pDesc->MiscFlags  = d3d11Desc.MiscFlags;
  }

}