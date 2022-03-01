#pragma once

#include "d3d10_util.h"
#include "d3d10_device_child.h"

namespace dxvk {

  class D3D10InputLayout : public D3D11Parent<D3D10DeviceChild<ID3D10InputLayout>, ID3D11InputLayout> {

  public:

    D3D10InputLayout(ID3D11InputLayout* d3d11, D3D10Device* device)
    : D3D11Parent(d3d11, device) { }

    HRESULT STDMETHODCALLTYPE QueryInterface(
            REFIID                    riid,
            void**                    ppvObject);

  };

}