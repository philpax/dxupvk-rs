#pragma once

#include "d3d10_util.h"
#include "d3d10_device_child.h"

namespace dxvk {

  class D3D10DepthStencilState : public D3D11Parent<D3D10StateObject<ID3D10DepthStencilState>, ID3D11DepthStencilState> {

  public:

    D3D10DepthStencilState(ID3D11DepthStencilState* d3d11, D3D10Device* device)
    : D3D11Parent(d3d11, device) { }

    HRESULT STDMETHODCALLTYPE QueryInterface(
            REFIID                    riid,
            void**                    ppvObject);

    void STDMETHODCALLTYPE GetDesc(
            D3D10_DEPTH_STENCIL_DESC* pDesc);

  };

}