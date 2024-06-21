#include "Video.hpp"
#include "MemoryBus.hpp"
#include "Tile.hpp"
#include <string>
#include <iostream>


constexpr uint8_t VRAM_TILE_SIZE = 16;

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


	for (int i = 0; i < FramebufferHeight * FramebufferWidth; i++)
		_frameBuffer[i] = 0x00;
}


void Video::Update(uint32_t cycles)
{
	static uint8_t* lcdControl = _memoryBus->Get(HardwareRegister::LCDC);
	//static LCDControlRegister* lcdControl = reinterpret_cast<LCDControlRegister*>(_memoryBus->Get(HardwareRegister::LCDC));
	static uint8_t& scanline = *_memoryBus->Get(HardwareRegister::LY);
	SetLCDStatus();

	if ((*lcdControl) & LCDC::LCDPPUEnable)
		_scanlineCounter -= cycles;
	else
		return;

	if (_scanlineCounter <= 0)
	{
		scanline++;

		_scanlineCounter = 456;

		if (scanline == 144) // V Blank?
			_memoryBus->RequestInterrupt(Interrupt::VBLANK);
		else if (scanline >= 153)
			scanline = 0;
		else
			DrawScanline();
	}
}

void Video::SetLCDStatus()
{
	static uint8_t lastStatus = 0;
	static uint8_t* lcdStatusbyte = _memoryBus->Get(HardwareRegister::STAT);
	static uint8_t* lcdControl = _memoryBus->Get(HardwareRegister::LCDC);

	if (lastStatus == *lcdStatusbyte)
		return; // Nothing to do

	static LCDStatusRegister* lcdStatus = reinterpret_cast<LCDStatusRegister*>(_memoryBus->Get(HardwareRegister::STAT));
	// static LCDControlRegister* lcdControl = reinterpret_cast<LCDControlRegister*>(_memoryBus->Get(HardwareRegister::LCDC));
	static uint8_t& scanline = *_memoryBus->Get(HardwareRegister::LY);
	static uint8_t& lyc = *_memoryBus->Get(HardwareRegister::LYC);

	if (((*lcdControl) & LCDC::LCDPPUEnable) == 0)
	{
		_scanlineCounter = 456;
		scanline = 0;
		lcdStatus->PPUMode = PPUMode::HBlank;
	} 
	else
	{
		PPUMode currentMode = lcdStatus->PPUMode;
		PPUMode newMode = PPUMode::HBlank;

		bool reqInt = false;

		if (scanline >= 144) // V BLANK
		{
			newMode = PPUMode::VBlank;
			lcdStatus->PPUMode = PPUMode::VBlank;
			reqInt = lcdStatus->Mode1IntSelect;
		}
		else
		{
			uint32_t mode2Bounds = 376;
			uint32_t mode3Bounds = 204;

			if (_scanlineCounter >= 376)
			{
				newMode = PPUMode::OAMScan;
				lcdStatus->PPUMode = PPUMode::OAMScan;
				reqInt = lcdStatus->Mode2IntSelect;
			}
			else if (_scanlineCounter >= 204)
			{
				newMode = PPUMode::DrawingPixels;
				lcdStatus->PPUMode = PPUMode::DrawingPixels;
			}
			else
			{
				newMode = PPUMode::HBlank;
				lcdStatus->PPUMode = PPUMode::HBlank;
				reqInt = lcdStatus->Mode0IntSelect;
			}
		}

		if (reqInt && (newMode != currentMode))
			_memoryBus->RequestInterrupt(Interrupt::LCD);

		uint8_t fuck = (*lcdStatusbyte);
		// if (lyc == lcdStatus->LYCeqLY)
		if (lyc == ((fuck & 0b00100000) != 0))
		{
			lcdStatus->LYCeqLY = true;
			if ((fuck & 0b00000010) != 0) // LYC Int Select
				_memoryBus->RequestInterrupt(Interrupt::LCD);
		}
		else
			lcdStatus->LYCeqLY = false;

		lastStatus = *lcdStatusbyte;
	}
}

void Video::DrawScanline()
{
	// std::cout << "drawing curr scanline: " << _memoryBus->Read(HardwareRegister::LY) << std::endl;
	static uint8_t* lcdControl = _memoryBus->Get(HardwareRegister::LCDC);

	if (((*lcdControl) & LCDC::BGWindowEnablePriority) != 0)
		RenderTiles();

	if ((*lcdControl) & LCDC::ObjectsEnabled)
	{

	}

	_memoryBus->RequestInterrupt(Interrupt::LCD);
}

void Video::RenderTiles()
{
	char controlByte = _memoryBus->Read(HardwareRegister::LCDC);
	//LCDControlRegister* lcdControl = reinterpret_cast<LCDControlRegister*>(&controlByte);
	static uint8_t* lcdControl = _memoryBus->Get(HardwareRegister::LCDC);

	// Find where to draw
	uint8_t viewportY = _memoryBus->Read(HardwareRegister::SCY);
	uint8_t viewportX = _memoryBus->Read(HardwareRegister::SCX);

	uint8_t windowY = _memoryBus->Read(HardwareRegister::WY);
	uint8_t windowX = _memoryBus->Read(HardwareRegister::WX) - 7;

	uint8_t scanline = _memoryBus->Read(HardwareRegister::LY);

	bool useWindow = (((*lcdControl) & LCDC::WindowEnable) != 0) && windowY <= scanline;
	bool unsig = (((*lcdControl) & LCDC::BGWindowTileDataOffset) != 0);

	uint16_t tileRamStart = (((*lcdControl) & LCDC::BGWindowTileDataOffset) != 0) ? 0x8000 : 0x8800;
	uint16_t bgRamStart = (((*lcdControl) & LCDC::BGTileMapOffset) != 0) ? 0x9C000 : 0x9800;


	uint8_t yPos = useWindow ? scanline - windowY : viewportY + scanline;


	uint16_t tileRow = ((uint8_t)(yPos / 8)) * 32;


	// std::cout << "rendering tiles" << std::endl;

	for (uint8_t pixel = 0; pixel < 160; pixel++)
	{
		uint8_t xPos = viewportX + pixel;

		// If needed, translate to window space
		if (useWindow && pixel >= windowX)
			xPos = pixel - windowX;

		// 1) Find the Address of the tile we want to draw
		uint16_t tileCol = xPos / 8;
		int16_t tileID = 0;

		if (unsig)
			tileID = (uint16_t)_memoryBus->Read(bgRamStart + tileRow + tileCol);
		else
			tileID = (int16_t)_memoryBus->Read(bgRamStart + tileRow + tileCol);

		uint16_t tileLocation = tileRamStart;

		if (unsig)
			tileLocation += (tileID * 16);
		else
			tileLocation += ((tileID + 128) * 16);


		// 2) Find the color data of the line we are going to render
		uint16_t tileLine = (yPos % 8) * 2;
		uint8_t lhb = _memoryBus->Read(tileLocation + tileLine);
		uint8_t msb = _memoryBus->Read(tileLocation + tileLine + 1);

		// 3) Extract the color
		uint8_t colorBit = (7 - (xPos % 8));


		uint8_t lhb2 = ((lhb & (0b1 << colorBit)) != 0) ? 0b10 : 0b00;
		uint8_t msb2 = ((msb & (0b1 << colorBit)) != 0) ? 0b01 : 0b00;

		DMGColor color = (DMGColor)(lhb2 | msb2);

		// DMGColor color = DMGColor::WHITE;

		if (scanline >= 0 && scanline <= 143 && pixel >= 0 && pixel <= 159)
		{
			byte c = 0xFF;

			switch (color)
			{
			case DMGColor::WHITE:
				c = 0xFF;
				break;
			case DMGColor::LIGHT_GREY:
				c = 0xA2;
				break;
			case DMGColor::DARK_GREY:
				c = 0x4E;
				break;
			case DMGColor::BLACK:
				c = 0x00;
				break;
			}

			// if (c != 0xFF)
			//	std::cout << "x: " << std::to_string(pixel) << " y: " << std::to_string(scanline) << "COLOR: " << std::to_string(c) << std::endl;

			SetPixel(pixel, scanline, c, c, c);
		}


	}
}

void Video::SetPixel(uint8_t x, uint8_t y, uint8_t r, uint8_t g, uint8_t b)
{
	_frameBuffer[(y * FramebufferWidth) + x] = ((uint32_t)r << 24) | ((uint32_t)g << 16) | ((uint32_t)b << 8) | 0xFF;
}
uint32_t Video::GetPixel(uint8_t x, uint8_t y)
{
	return _frameBuffer[(y * FramebufferWidth) + x];
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