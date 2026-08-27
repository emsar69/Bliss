#pragma once

#ifdef __ANDROID__
	#define __cdecl
#endif

namespace Hooks {
    void Setup();
    void Destroy();

	#ifdef __WIN32__
		#include <d3d11.h>

		typedef HRESULT(__stdcall* PresentFn)(IDXGISwapChain*, UINT, UINT);
		inline PresentFn oPresent = nullptr;

		HRESULT __stdcall PresentHook(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags) noexcept;

		typedef HRESULT(__stdcall* ResizeFn)(IDXGISwapChain* pSwapChain, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags);
		inline ResizeFn oResize = nullptr;

		HRESULT __stdcall ResizeHook(IDXGISwapChain* pSwapChain, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags) noexcept;
	
	#endif

	typedef void (__cdecl* MurderPlayerFn)(void* self, void* target, int flags);
	inline MurderPlayerFn oMurderPlayer = nullptr;

	void __cdecl MurderPlayerHook(void* self, void* target, int flags) noexcept;
}