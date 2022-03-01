#pragma once

#include "d3d10_include.h"

#include "../util/com/com_private_data.h"

namespace dxvk {

  class D3D10Device;

  template<typename Base>
  class D3D10DeviceObject : public Base {

  public:

    D3D10DeviceObject(D3D10Device* pDevice)
    : m_parent(pDevice) {

    }

    HRESULT STDMETHODCALLTYPE GetPrivateData(
            REFGUID guid,
            UINT    *pDataSize,
            void    *pData) final {
      return m_privateData.getData(
        guid, pDataSize, pData);
    }

    HRESULT STDMETHODCALLTYPE SetPrivateData(
            REFGUID guid,
            UINT    DataSize,
      const void    *pData) final {
      return m_privateData.setData(
        guid, DataSize, pData);
    }

    HRESULT STDMETHODCALLTYPE SetPrivateDataInterface(
            REFGUID  guid,
      const IUnknown *pUnknown) final {
      return m_privateData.setInterface(
        guid, pUnknown);
    }

    void STDMETHODCALLTYPE GetDevice(
            ID3D10Device**        ppDevice) final {
      *ppDevice = ref(GetParentInterface());
    }

  protected:

    ID3D10Device* GetParentInterface() const {
      // We don't know the definition of ID3D10Device
      // here, because D3D10Device includes this file.
      return reinterpret_cast<ID3D10Device*>(m_parent);
    }

    D3D10Device* const m_parent;

  private:

    ComPrivateData m_privateData;

  };


  template<typename Base>
  class D3D10DeviceChild : public D3D10DeviceObject<ComObject<Base>> {

  public:

    D3D10DeviceChild(D3D10Device* pDevice)
    : D3D10DeviceObject<ComObject<Base>>(pDevice) {

    }

    ULONG STDMETHODCALLTYPE AddRef() {
      uint32_t refCount = this->m_refCount++;
      if (unlikely(!refCount)) {
        this->AddRefPrivate();
        this->GetParentInterface()->AddRef();
      }

      return refCount + 1;
    }

    ULONG STDMETHODCALLTYPE Release() {
      uint32_t refCount = --this->m_refCount;
      if (unlikely(!refCount)) {
        auto* parent = this->GetParentInterface();
        this->ReleasePrivate();
        parent->Release();
      }
      return refCount;
    }

  };

  template<typename Base>
  class D3D10StateObject : public D3D10DeviceObject<Base> {

  public:

    D3D10StateObject(D3D10Device* pDevice)
    : D3D10DeviceObject<Base>(pDevice) {

    }

    ULONG STDMETHODCALLTYPE AddRef() {
      uint32_t refCount = this->m_refCount++;
      if (unlikely(!refCount))
        this->GetParentInterface()->AddRef();

      return refCount + 1;
    }

    ULONG STDMETHODCALLTYPE Release() {
      uint32_t refCount = --this->m_refCount;
      if (unlikely(!refCount))
        this->GetParentInterface()->Release();

      return refCount;
    }

  private:

    std::atomic<uint32_t> m_refCount = { 0u };

  };

  template<typename Base, typename D3D11Class>
  class D3D11Parent : public Base {
  public:
    template <typename... Args>
    D3D11Parent(D3D11Class* d3d11, Args&&... args)
    : Base(std::forward<Args...>(args...)) {
      m_d3d11 = d3d11;
			m_d3d11->SetPrivateData(__uuidof(D3D10Map), sizeof(void*), this);
    }

    ULONG STDMETHODCALLTYPE AddRef() final {
      m_d3d11->AddRef();
      return Base::AddRef();
    }

    ULONG STDMETHODCALLTYPE Release() final {
      m_d3d11->Release();
      return Base::Release();
    }

    D3D11Class* GetD3D11Iface() {
      return m_d3d11;
    }

  protected:

    D3D11Class* m_d3d11 = nullptr;
  };

}
