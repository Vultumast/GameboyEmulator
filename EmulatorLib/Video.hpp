#pragma once

#include "Constants.hpp"
#include <Windows.h>

#include <d3d11.h>
#include <dxgi1_3.h>
#include <wrl.h>
#include <d3d11shader.h>

#include <DirectXMath.h>
#include <d3dcompiler.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "dxguid.lib")

class MemoryBus;

template <typename T>
using ComPtr = Microsoft::WRL::ComPtr<T>;

class Video
{
private:
	MemoryBus* _memoryBus = nullptr;

	ComPtr<ID3D11Device> _dxDevice = nullptr;
	ComPtr<ID3D11DeviceContext> _dxDeviceContext = nullptr;
	ComPtr<IDXGIFactory2> _dxgiFactory = nullptr;

	ComPtr<ID3D11Debug> _dxDebug = nullptr;

	ComPtr<ID3D11RenderTargetView> _dxRenderTarget = nullptr;

	ComPtr<IDXGISwapChain1> _dxSwapChain = nullptr;

public:
	Video(MemoryBus* memoryBus, HWND hwnd);

	void Clear();

	void Present();
};