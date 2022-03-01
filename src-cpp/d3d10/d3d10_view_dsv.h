#pragma once

#include "d3d10_util.h"
#include "d3d10_device_child.h"

namespace dxvk {

  class D3D10DepthStencilView : public D3D11Parent<D3D10DeviceChild<ID3D10DepthStencilView>, ID3D11DepthStencilView> {

  public:

    D3D10DepthStencilView(ID3D11DepthStencilView* d3d11, D3D10Device* device)
    : D3D11Parent(d3d11, device) { }

    HRESULT STDMETHODCALLTYPE QueryInterface(
            REFIID                    riid,
            void**                    ppvObject);

    void STDMETHODCALLTYPE GetResource(
            ID3D10Resource**          ppResource);

    void STDMETHODCALLTYPE GetDesc(
            D3D10_DEPTH_STENCIL_VIEW_DESC* pDesc);

  };

}