#pragma once
#include <Windows.h>
#include <D3D11.h>

namespace JRenderer
{
	class JDevice
	{
	public:
		static HRESULT Initialize();
	private:
		static ID3D11Device* pDevice;
		static D3D_FEATURE_LEVEL featureLevel;
		static ID3D11DeviceContext* pImmediateContext;
	};
}