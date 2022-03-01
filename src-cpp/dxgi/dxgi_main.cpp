#include "dxgi_factory.h"
#include "dxgi_include.h"

#include "../util/com/com_pointer.h"

extern "C" {
  DLLEXPORT HRESULT __stdcall CreateDXGIFactory(REFIID riid, void **ppFactory) {
    void* originalFactory = nullptr;
    HRESULT hr = ::CreateDXGIFactory1(riid, &originalFactory);

    if (originalFactory) {
      dxvk::Com<dxvk::DxgiFactory> factory = new dxvk::DxgiFactory((IDXGIFactory*)originalFactory);
      if (ppFactory) {
        *ppFactory = factory.ref();
      }
    }

    return hr;
  }

}