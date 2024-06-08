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
	swapChainDescriptor.Width = 160;
	swapChainDescriptor.Height = 144;
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


void Video::Update(uint32_t cycles)
{
	SetLCDStatus();
	char controlByte = _memoryBus->Read(0xFF40);
	LCDControlRegister* lcdControl = reinterpret_cast<LCDControlRegister*>(&controlByte);

	if (lcdControl->LCDPPUEnable)
		_scanlineCounter -= cycles;
	else
		return;

	if (_scanlineCounter <= 0)
	{
		uint8_t currentline = _memoryBus->Read(0xFF44) + 1;
		// Inc scanline counter
		_memoryBus->Write(0xFF44, currentline);

		_scanlineCounter = 456;

		if (currentline == 144) // V Blank?
			_memoryBus->RequestInterrupt(Interrupt::VBLANK);
		else if (currentline >= 153)
			_memoryBus->Write(0xFF44, 0);
		else
			DrawScanline();
	}
}

void Video::SetLCDStatus()
{
	char statusByte = _memoryBus->Read(0xFF41);
	char controlByte = _memoryBus->Read(0xFF40);

	LCDStatusRegister* lcdStatus = reinterpret_cast<LCDStatusRegister*>(&statusByte);
	LCDControlRegister* lcdControl = reinterpret_cast<LCDControlRegister*>(&controlByte);

	if (!lcdControl->LCDPPUEnable)
	{
		_scanlineCounter = 456;
		_memoryBus->Write(0xFF44, 0);
		lcdStatus->PPUMode = PPUMode::WaitingForHBlank;
		_memoryBus->Write(0xFF41, reinterpret_cast<uint8_t>(&lcdStatus));
	}

	PPUMode currentMode = lcdStatus->PPUMode;
	PPUMode newMode = PPUMode::WaitingForHBlank;

	uint8_t scanline = _memoryBus->Read(0xFF44);

	bool reqInt = false;

	if (scanline >= 144) // V BLANK
	{
		newMode = PPUMode::WaitingForVBlank;
		lcdStatus->PPUMode = PPUMode::WaitingForVBlank;
		reqInt = lcdStatus->Mode1IntSelect;
	}
	else
	{
		uint32_t mode2Bounds = 376;
		uint32_t mode3Bounds = 204;

		if (_scanlineCounter >= mode2Bounds)
		{
			newMode = PPUMode::SearchingForObjects;
			lcdStatus->PPUMode = PPUMode::SearchingForObjects;
			reqInt = lcdStatus->Mode2IntSelect;
		}
		else if (_scanlineCounter >= mode3Bounds)
		{
			newMode = PPUMode::SendingPixels;
			lcdStatus->PPUMode = PPUMode::SendingPixels;
		}
		else
		{
			newMode = PPUMode::WaitingForHBlank;
			lcdStatus->PPUMode = PPUMode::WaitingForHBlank;
			reqInt = lcdStatus->Mode0IntSelect;
		}
	}

	if (reqInt && (newMode != currentMode))
		_memoryBus->RequestInterrupt(Interrupt::LCD);

	if (_memoryBus->Read(0xFF45) == lcdStatus->LYCeqLY)
	{
		lcdStatus->LYCeqLY = true;
		if (lcdStatus->LYCIntSelect)
			_memoryBus->RequestInterrupt(Interrupt::LCD);
	}
	else
		lcdStatus->LYCeqLY = false;

	_memoryBus->Write(0xFF41, statusByte);
}

void Video::DrawScanline()
{
	char controlByte = _memoryBus->Read(0xFF40);

	LCDControlRegister* lcdControl = reinterpret_cast<LCDControlRegister*>(&controlByte);

	if (lcdControl->BGWindowEnablePriority)
	{

	}

	if (lcdControl->ObjectsEnabled)
	{

	}

	_memoryBus->RequestInterrupt(Interrupt::LCD);
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