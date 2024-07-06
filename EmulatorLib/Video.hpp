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

enum PPUMode : uint8_t
{
	HBlank,
	VBlank,
	OAMScan,
	DrawingPixels
};

enum LCDC : uint8_t
{
	BGWindowEnablePriority	= 0b00000001,
	ObjectsEnabled			= 0b00000010,
	ObjectBGSize			= 0b00000100,
	BGTileMapOffset			= 0b00001000,
	BGWindowTileDataOffset	= 0b00010000,
	WindowEnable			= 0b00100000,
	WindowTileMapOffset		= 0b01000000,
	LCDPPUEnable			= 0b10000000,
};

enum STAT : uint8_t
{
	PPUModeMask		= 0b00000011,
	LYCeqLY			= 0b00000100,
	Mode0IntSelect	= 0b00001000,
	Mode1IntSelect	= 0b00010000,
	Mode2IntSelect	= 0b00100000,
	LYCIntSelect	= 0b01000000,
};

#pragma pack(push, 1)
struct BackgroundDisplayInfo
{
	uint8_t ScrollY = 0;
	uint8_t ScrollX = 0;
	uint8_t WindowY = 0;
	uint8_t WindowX = 0;
};

/*
struct LCDControlRegister
{
public:
	LCDControlRegister()
	{
		LCDPPUEnable = false;
		WindowTileMapOffset = false;
		WindowEnable = false;
		BGWindowTileDataOffset = false;
		BGTileMapOffset = false;
		ObjectBigSize = false;
		ObjectsEnabled = false;
		BGWindowEnablePriority = false;
	}
	/// <summary>
	/// Bit 7
	/// </summary>
	bool BGWindowEnablePriority : 1;
	/// <summary>
	/// Bit 6
	/// </summary>
	bool ObjectsEnabled : 1;
	/// <summary>
	/// Bit 5
	/// </summary>
	bool ObjectBigSize : 1;
	/// <summary>
	/// Bit 4
	/// </summary>
	bool BGTileMapOffset : 1;
	/// <summary>
	/// Bit 3
	/// </summary>
	bool BGWindowTileDataOffset : 1;
	/// <summary>
	/// Bit 2
	/// </summary>
	bool WindowEnable : 1;
	/// <summary>
	/// Bit 1
	/// </summary>
	bool WindowTileMapOffset : 1;
	/// <summary>
	/// Bit 0
	/// </summary>
	bool LCDPPUEnable : 1;
};


struct LCDStatusRegister
{
public:
	LCDStatusRegister()
	{
		Unused = false;
		LYCIntSelect = false;
		Mode2IntSelect = false;
		Mode1IntSelect = false;
		Mode0IntSelect = false;
		LYCeqLY = false;
		PPUMode = PPUMode::HBlank;
	}
	PPUMode PPUMode : 2;
	bool LYCeqLY : 1;
	bool Mode0IntSelect : 1;
	bool Mode1IntSelect : 1;
	bool Mode2IntSelect : 1;
	bool LYCIntSelect : 1;
	bool Unused : 1;
};
*/
#pragma pack(pop)

constexpr uint8_t FramebufferWidth = 160;
constexpr uint8_t FramebufferHeight = 144;

class Video
{
private:
	int32_t _scanlineCounter = 0;

	MemoryBus* _memoryBus = nullptr;

	ComPtr<ID3D11Device> _dxDevice = nullptr;
	ComPtr<ID3D11DeviceContext> _dxDeviceContext = nullptr;
	ComPtr<IDXGIFactory2> _dxgiFactory = nullptr;

	ComPtr<ID3D11Debug> _dxDebug = nullptr;

	ComPtr<ID3D11RenderTargetView> _dxRenderTarget = nullptr;

	ComPtr<IDXGISwapChain1> _dxSwapChain = nullptr;

	uint32_t _frameBuffer[FramebufferWidth * FramebufferHeight];

public:
	Video(MemoryBus* memoryBus, HWND hwnd);

	void Update(uint32_t cycles);

	void SetLCDStatus();

	void DrawScanline();

	void RenderTiles();

	void SetPixel(uint8_t x, uint8_t y, uint8_t r, uint8_t g, uint8_t b);
	uint32_t GetPixel(uint8_t x, uint8_t y);

	void Clear();

	void Present();
};