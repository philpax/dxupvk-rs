#include <d3d11.h>
#include <d3d10_1.h>

#include "../dxgi/dxgi_include.h"
#include "d3d10_device.h"

extern "C" {
  using namespace dxvk;

	static D3D_FEATURE_LEVEL featureLevel[] =
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
		D3D_FEATURE_LEVEL_9_3,
		D3D_FEATURE_LEVEL_9_2,
		D3D_FEATURE_LEVEL_9_1,
	};

  DLLEXPORT HRESULT __stdcall D3D10CoreCreateDevice(
          IDXGIFactory*           pFactory,
          IDXGIAdapter*           pAdapter,
          UINT                    Flags,
          D3D_FEATURE_LEVEL       FeatureLevel,
          ID3D10Device**          ppDevice) {
    InitReturnPtr(ppDevice);

    Com<ID3D11Device> d3d11Device;

    HRESULT hr = pAdapter->CheckInterfaceSupport(
      __uuidof(ID3D10Device), nullptr);

    if (FAILED(hr))
      return hr;

		D3D_FEATURE_LEVEL level = D3D_FEATURE_LEVEL_11_1;

    hr = D3D11CreateDevice(pAdapter, pAdapter ? D3D_DRIVER_TYPE_UNKNOWN : D3D_DRIVER_TYPE_HARDWARE, 0, Flags, featureLevel, 6, D3D11_SDK_VERSION, &d3d11Device, &level, nullptr);

    if (FAILED(hr))
      return hr;

    Com<ID3D10Multithread> multithread;
    d3d11Device->QueryInterface(__uuidof(ID3D10Multithread), reinterpret_cast<void**>(&multithread));
    multithread->SetMultithreadProtected(!(Flags & D3D10_CREATE_DEVICE_SINGLETHREADED));

    Com<ID3D11DeviceContext> deviceContext;
    d3d11Device->GetImmediateContext(&deviceContext);
    *ppDevice = new D3D10Device(d3d11Device.ref(), deviceContext.ref());

    return S_OK;
  }


  UINT64 STDMETHODCALLTYPE D3D10CoreGetVersion() {
    // Match the Windows 10 return value, but we
    // don't know the exact function signature
    return 0xa000100041770ull;
  }


  HRESULT STDMETHODCALLTYPE D3D10CoreRegisterLayers() {
    return E_NOTIMPL;
  }

}
