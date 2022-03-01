#pragma once

#include "d3d10_util.h"
#include "d3d10_device_child.h"

namespace dxvk {

  class D3D10ShaderResourceView : public D3D11Parent<D3D10DeviceChild<ID3D10ShaderResourceView1>, ID3D11ShaderResourceView> {

  public:

    D3D10ShaderResourceView(ID3D11ShaderResourceView* d3d11, D3D10Device* device)
    : D3D11Parent(d3d11, device) { }

    HRESULT STDMETHODCALLTYPE QueryInterface(
            REFIID                    riid,
            void**                    ppvObject);

    void STDMETHODCALLTYPE GetResource(
            ID3D10Resource**          ppResource);

    void STDMETHODCALLTYPE GetDesc(
            D3D10_SHADER_RESOURCE_VIEW_DESC* pDesc);

    void STDMETHODCALLTYPE GetDesc1(
            D3D10_SHADER_RESOURCE_VIEW_DESC1* pDesc);

  };

}