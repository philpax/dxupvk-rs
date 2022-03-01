#pragma once

#include "d3d10_util.h"
#include "d3d10_device_child.h"

namespace dxvk {

  class D3D10BlendState : public D3D11Parent<D3D10StateObject<ID3D10BlendState1>, ID3D11BlendState> {

  public:

    D3D10BlendState(ID3D11BlendState* d3d11, D3D10Device* device)
    : D3D11Parent(d3d11, device) { }

    HRESULT STDMETHODCALLTYPE QueryInterface(
            REFIID                    riid,
            void**                    ppvObject);

    void STDMETHODCALLTYPE GetDesc(
            D3D10_BLEND_DESC*         pDesc);

    void STDMETHODCALLTYPE GetDesc1(
            D3D10_BLEND_DESC1*        pDesc);

  };

}