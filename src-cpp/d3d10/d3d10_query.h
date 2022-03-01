#pragma once

#include "d3d10_util.h"
#include "d3d10_device_child.h"

namespace dxvk {

  class D3D10Query : public D3D11Parent<D3D10DeviceChild<ID3D10Predicate>, ID3D11Query> {

  public:

    D3D10Query(ID3D11Query* d3d11, D3D10Device* device)
    : D3D11Parent(d3d11, device) { }

    HRESULT STDMETHODCALLTYPE QueryInterface(
            REFIID                    riid,
            void**                    ppvObject);

    void STDMETHODCALLTYPE Begin();

    void STDMETHODCALLTYPE End();

    HRESULT STDMETHODCALLTYPE GetData(
            void*                     pData,
            UINT                      DataSize,
            UINT                      GetDataFlags);

    UINT STDMETHODCALLTYPE GetDataSize();

    void STDMETHODCALLTYPE GetDesc(
            D3D10_QUERY_DESC*         pDesc);

  };

}