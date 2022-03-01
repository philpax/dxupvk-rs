#pragma once

#include "d3d10_util.h"
#include "d3d10_device_child.h"

namespace dxvk {

  class D3D10Buffer : public D3D11Parent<D3D10DeviceChild<ID3D10Buffer>, ID3D11Buffer> {

  public:

    D3D10Buffer(ID3D11Buffer* d3d11, D3D10Device* device)
    : D3D11Parent(d3d11, device) { }

    HRESULT STDMETHODCALLTYPE QueryInterface(
            REFIID                    riid,
            void**                    ppvObject);

    void STDMETHODCALLTYPE GetType(
            D3D10_RESOURCE_DIMENSION* rType);

    void STDMETHODCALLTYPE SetEvictionPriority(
            UINT                      EvictionPriority);

    UINT STDMETHODCALLTYPE GetEvictionPriority();

    HRESULT STDMETHODCALLTYPE Map(
            D3D10_MAP                 MapType,
            UINT                      MapFlags,
            void**                    ppData);

    void STDMETHODCALLTYPE Unmap();

    void STDMETHODCALLTYPE GetDesc(
            D3D10_BUFFER_DESC*        pDesc);

  };

}