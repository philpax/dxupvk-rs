#pragma once

#include "d3d10_util.h"
#include "d3d10_device_child.h"

namespace dxvk {

  class D3D10RenderTargetView : public D3D11Parent<D3D10DeviceChild<ID3D10RenderTargetView>, ID3D11RenderTargetView> {

  public:

    D3D10RenderTargetView(ID3D11RenderTargetView* d3d11, D3D10Device* device)
    : D3D11Parent(d3d11, device) { }

    HRESULT STDMETHODCALLTYPE QueryInterface(
            REFIID                    riid,
            void**                    ppvObject);

    void STDMETHODCALLTYPE GetResource(
            ID3D10Resource**          ppResource);

    void STDMETHODCALLTYPE GetDesc(
            D3D10_RENDER_TARGET_VIEW_DESC* pDesc);

  };

}