#pragma once

#include <d3d11.h>

namespace Hooks {
    void Setup();
    void Destroy();

    typedef HRESULT(__stdcall* PresentFn)(IDXGISwapChain*, UINT, UINT);
	inline PresentFn oPresent = nullptr;

	HRESULT __stdcall PresentHook(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags) noexcept;

	typedef HRESULT(__stdcall* ResizeFn)(IDXGISwapChain* pSwapChain, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags);
	inline ResizeFn oResize = nullptr;

	HRESULT __stdcall ResizeHook(IDXGISwapChain* pSwapChain, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags) noexcept;

	typedef void (__stdcall* MurderPlayerFn)(void* self, void* target, int flags);
	inline MurderPlayerFn oMurderPlayer = nullptr;

	void __stdcall MurderPlayerHook(void* self, void* target, int flags) noexcept;

	typedef bool (__stdcall* get_IsImpostorFn)(void* self);
	inline get_IsImpostorFn oGet_IsImpostor = nullptr;

	bool __stdcall get_IsImpostorHook(void* self) noexcept;
}