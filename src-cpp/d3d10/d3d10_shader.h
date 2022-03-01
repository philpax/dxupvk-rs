#pragma once

#include "d3d10_util.h"
#include "d3d10_device_child.h"

namespace dxvk {

  template<typename D3D10Interface, typename D3D11Interface>
  class D3D10Shader : public D3D11Parent<D3D10DeviceChild<D3D10Interface>, D3D11Interface> {
  public:

    D3D10Shader(D3D11Interface* d3d11, D3D10Device* device)
    : D3D11Parent(d3d11, device) { }


    HRESULT STDMETHODCALLTYPE QueryInterface(
            REFIID                    riid,
            void**                    ppvObject) {
      if (riid == __uuidof(IUnknown)
       || riid == __uuidof(ID3D10DeviceChild)
       || riid == __uuidof(D3D10Interface)) {
        *ppvObject = ref(this);
        return S_OK;
      }

      if (riid == __uuidof(IUnknown)
       || riid == __uuidof(ID3D11DeviceChild)
       || riid == __uuidof(D3D11Interface)) {
        *ppvObject = ref(m_d3d11);
        return S_OK;
      }
    }

  };

  using D3D10VertexShader   = D3D10Shader<ID3D10VertexShader,   ID3D11VertexShader>;
  using D3D10GeometryShader = D3D10Shader<ID3D10GeometryShader, ID3D11GeometryShader>;
  using D3D10PixelShader    = D3D10Shader<ID3D10PixelShader,    ID3D11PixelShader>;

}