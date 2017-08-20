#include "Interface.h"
#include "Device.h"

const unsigned int JRenderer::WINDOW_WIDTH = 500;
const unsigned int JRenderer::WINDOW_HEIGHT = 500;

namespace JRenderer
{
	HRESULT Initialize(HWND hInst) {
		return JDevice::Initialize();
	}

	HRESULT JDevice::Initialize() {
		D3D_FEATURE_LEVEL feature_levels[] = {
			D3D_FEATURE_LEVEL_11_0,
			D3D_FEATURE_LEVEL_10_1,
			D3D_FEATURE_LEVEL_10_0,
			D3D_FEATURE_LEVEL_9_3,
			D3D_FEATURE_LEVEL_9_2,
			D3D_FEATURE_LEVEL_9_1,
		};
		
		UINT create_flags = D3D11_CREATE_DEVICE_SINGLETHREADED;
#ifdef DEBUG
		create_flags |= D3D11_CREATE_DEVICE_DEBUG;
#endif // DEBUG

		HRESULT ret = D3D11CreateDevice(
			NULL,
			D3D_DRIVER_TYPE_HARDWARE,
			NULL,
			create_flags,
			feature_levels,
			ARRAYSIZE(feature_levels),
			D3D11_SDK_VERSION,
			&pDevice,
			&featureLevel,
			&pImmediateContext
		);
		if (FAILED(ret))
		{
			MessageBox(0, L"D3D11CreateDevice Failed!", 0, 0);
			return ret;
		}
		if (featureLevel != D3D_FEATURE_LEVEL_11_0)
		{
			MessageBox(0, L"Feature level 11 unsupported!", 0, 0);
			return E_FAIL;
		}



	}

	static ID3D11Device* pDevice = NULL;
	static D3D_FEATURE_LEVEL featureLevel = D3D_FEATURE_LEVEL_11_0;
	static ID3D11DeviceContext* pImmediateContext = NULL;
}