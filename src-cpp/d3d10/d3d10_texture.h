#pragma once

#include "d3d10_util.h"
#include "d3d10_device_child.h"

namespace dxvk {

  ///////////////////////////////////////////
  //      D 3 D 1 0 T E X T U R E 1 D
  class D3D10Texture1D : public D3D11Parent<D3D10DeviceChild<ID3D10Texture1D>, ID3D11Texture1D> {

  public:

    D3D10Texture1D(ID3D11Texture1D* d3d11, D3D10Device* device)
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
            UINT                      Subresource,
            D3D10_MAP                 MapType,
            UINT                      MapFlags,
            void**                    ppData);

    void STDMETHODCALLTYPE Unmap(
            UINT                      Subresource);

    void STDMETHODCALLTYPE GetDesc(
            D3D10_TEXTURE1D_DESC*     pDesc);

  };


  ///////////////////////////////////////////
  //      D 3 D 1 0 T E X T U R E 2 D
  class D3D10Texture2D : public D3D11Parent<D3D10DeviceChild<ID3D10Texture2D>, ID3D11Texture2D> {

  public:

    D3D10Texture2D(ID3D11Texture2D* d3d11, D3D10Device* device)
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
            UINT                      Subresource,
            D3D10_MAP                 MapType,
            UINT                      MapFlags,
            D3D10_MAPPED_TEXTURE2D*   pMappedTex2D);

    void STDMETHODCALLTYPE Unmap(
            UINT                      Subresource);

    void STDMETHODCALLTYPE GetDesc(
            D3D10_TEXTURE2D_DESC*     pDesc);

  };


  ///////////////////////////////////////////
  //      D 3 D 1 0 T E X T U R E 3 D
  class D3D10Texture3D : public D3D11Parent<D3D10DeviceChild<ID3D10Texture3D>, ID3D11Texture3D> {

  public:

    D3D10Texture3D(ID3D11Texture3D* d3d11, D3D10Device* device)
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
            UINT                      Subresource,
            D3D10_MAP                 MapType,
            UINT                      MapFlags,
            D3D10_MAPPED_TEXTURE3D*   pMappedTex3D);

    void STDMETHODCALLTYPE Unmap(
            UINT                      Subresource);

    void STDMETHODCALLTYPE GetDesc(
            D3D10_TEXTURE3D_DESC*     pDesc);

  };

}