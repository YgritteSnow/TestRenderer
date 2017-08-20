#include "Interface.h"
#include "Device.h"
#include "BaseScene.h"

const unsigned int JRenderer::WINDOW_WIDTH = 500;
const unsigned int JRenderer::WINDOW_HEIGHT = 500;

namespace JRenderer
{
	HRESULT Initialize(HWND hInst) {
		HRESULT hr = JDevice::Initialize(hInst);
		if (FAILED(hr))return hr;
		if (!SceneManager::Init())return E_FAIL;
		return hr;
	}
	void CleanupDevice()
	{
		JDevice::CleanupDevice();
		SceneManager::Uninit();
	}

	void JDevice::CleanupDevice()
	{
		if (pImmediateContext) pImmediateContext->ClearState();

		if (pRenderTargetView) pRenderTargetView->Release();
		if (pSwapChain) pSwapChain->Release();
		if (pImmediateContext) pImmediateContext->Release();
		if (pDevice) pDevice->Release();
	}

	HRESULT JDevice::Initialize(HWND hInst) {
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

		// 创建device和swap chain
		DXGI_SWAP_CHAIN_DESC desc;
		ZeroMemory(&desc, sizeof(desc));
		desc.BufferCount = 1;
		desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		desc.BufferDesc.Height = WINDOW_HEIGHT;
		desc.BufferDesc.Width = WINDOW_WIDTH;
		desc.BufferDesc.RefreshRate.Numerator = 60;
		desc.BufferDesc.RefreshRate.Denominator = 1;
		desc.BufferDesc.Scaling = DXGI_MODE_SCALING_CENTERED;
		desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		desc.OutputWindow = hInst;
		//desc.Flags = ;
		desc.Windowed = TRUE;
		desc.SampleDesc.Count = 1;
		desc.SampleDesc.Quality = 0;
		desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		if (FAILED(D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, NULL, 0,
			feature_levels, ARRAYSIZE(feature_levels), D3D11_SDK_VERSION, &desc,
			&pSwapChain, &pDevice, &featureLevel, &pImmediateContext)))
		{
			MessageBox(0, L"CreateDeviceAndSwapChain failed!", 0, 0);
			return E_FAIL;
		}

		// 创建backbuffer
		ID3D11Texture2D* pBackBuffer;
		if (FAILED(pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer)))
		{
			MessageBox(0, L"Get backbuffer failed!", 0, 0);
			return E_FAIL;
		}
		if (FAILED(pDevice->CreateRenderTargetView(pBackBuffer, NULL, &pRenderTargetView)))
		{
			MessageBox(0, L"Create render target view failed!", 0, 0);
			return E_FAIL;
		}
		pImmediateContext->OMSetRenderTargets(1, &pRenderTargetView, NULL);

		// 创建 viewport
		D3D11_VIEWPORT vp;
		ZeroMemory(&vp, sizeof(vp));
		vp.Width = WINDOW_WIDTH;
		vp.Height = WINDOW_HEIGHT;
		vp.MaxDepth = 1.0f;
		vp.MinDepth = 0.0f;
		vp.TopLeftX = 0;
		vp.TopLeftY = 0;
		pImmediateContext->RSSetViewports(1, &vp);
	}

	ID3D11Device* JDevice::pDevice = NULL;
	D3D_FEATURE_LEVEL JDevice::featureLevel = D3D_FEATURE_LEVEL_11_0;
	ID3D11DeviceContext* JDevice::pImmediateContext = NULL;
	IDXGISwapChain* JDevice::pSwapChain = NULL;
	ID3D11RenderTargetView* JDevice::pRenderTargetView = NULL;
}