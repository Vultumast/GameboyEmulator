#include "Video.hpp"
#include "MemoryBus.hpp"

#include <iostream>

Video::Video(MemoryBus* memoryBus, HWND hwnd)
{
	_memoryBus = memoryBus;

	uint32_t createDeviceFlags = D3D11_CREATE_DEVICE_FLAG::D3D11_CREATE_DEVICE_BGRA_SUPPORT;
	createDeviceFlags |= D3D11_CREATE_DEVICE_FLAG::D3D11_CREATE_DEVICE_DEBUG;
	D3D_FEATURE_LEVEL DeviceFeatureLevel = D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_11_0;

	if (FAILED(D3D11CreateDevice(
		nullptr,
		D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		createDeviceFlags,
		&DeviceFeatureLevel,
		1,
		D3D11_SDK_VERSION,
		&_dxDevice,
		nullptr,
		&_dxDeviceContext)))
	{
		std::cout << "[DX11] Failed to create Device and Device Context." << std::endl;
		// Log::Error("[DX11] Failed to create Device and Device Context.");
		return;
	}

	if (FAILED(_dxDevice.As(&_dxDebug)))
	{
		std::cout << "[DX11] Failed to get the debug layer from the device." << std::endl;
		// Log::Error("[DX11] Failed to get the debug layer from the device");
		return;
	}
	//else
		// Log::Debug("[DX11] Created Debug layer");


	if (FAILED(CreateDXGIFactory1(IID_PPV_ARGS(&_dxgiFactory))))
	{
		std::cout << "[DX11] Unable to create DXGI Factory." << std::endl;
		// Log::Error("[DX11] Unable to create DXGI Factory!");
		return;
	}


	DXGI_SWAP_CHAIN_DESC1 swapChainDescriptor = { };
	swapChainDescriptor.Width = 100;
	swapChainDescriptor.Height = 100;
	swapChainDescriptor.Format = DXGI_FORMAT::DXGI_FORMAT_B8G8R8A8_UNORM;
	swapChainDescriptor.SampleDesc.Count = 1;
	swapChainDescriptor.SampleDesc.Quality = 0;
	swapChainDescriptor.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDescriptor.BufferCount = 2;
	swapChainDescriptor.SwapEffect = DXGI_SWAP_EFFECT::DXGI_SWAP_EFFECT_FLIP_DISCARD;
	swapChainDescriptor.Scaling = DXGI_SCALING::DXGI_SCALING_STRETCH;
	swapChainDescriptor.Flags = {};



	DXGI_SWAP_CHAIN_FULLSCREEN_DESC swapChainFullscreenDescriptor = { };
	swapChainFullscreenDescriptor.Windowed = true;

	if (FAILED(_dxgiFactory->CreateSwapChainForHwnd(
		_dxDevice.Get(),
		hwnd,
		&swapChainDescriptor,
		&swapChainFullscreenDescriptor,
		nullptr,
		&_dxSwapChain)))
	{
		std::cout << "[DX11] Unable to create Swapchain." << std::endl;
		// Log::Error("[DX11] Unable to create Swapchain.");

		return; //false;
	}
	// else
	// 	Log::Info("[DX11] Created Swapchain");

	ComPtr<ID3D11Texture2D> backBuffer = nullptr;
	if (FAILED(_dxSwapChain->GetBuffer(0, IID_PPV_ARGS(&backBuffer))))
	{
		std::cout << "[DX11] Failed to get Buffer from SwapChain." << std::endl;
		// Log::Error("DX11: Failed to get Buffer from SwapChain.");
		return; // false;
	}

	if (FAILED(_dxDevice->CreateRenderTargetView(backBuffer.Get(), nullptr, &_dxRenderTarget)))
	{
		std::cout << "[DX11] Failed to create Render Target from Buffer." << std::endl;
		// Log::Error("[DX11] Failed to create Render Target from Buffer.");
		return; // false;
	}
	std::cout << "[DX11] Created DX Context" << std::endl;
}

void Video::Clear()
{
	std::cout << "[DX11] Clearing" << std::endl;
	float clearColor[] = { 1.0f, 0.0f, 1.0f, 1.0f };
	_dxDeviceContext->ClearRenderTargetView(_dxRenderTarget.Get(), clearColor);
}

void Video::Present()
{
	std::cout << "[DX11] Presenting" << std::endl;
	_dxSwapChain->Present(1, 0);
}