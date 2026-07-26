#pragma once

#include <Windows.h>
#include <d3d11.h>
#include <stdexcept>

#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_win32.h>
#include <imgui/backends/imgui_impl_dx11.h>

namespace Devices {
	inline ID3D11Device* g_pd3dDevice = nullptr;
	inline DXGI_SWAP_CHAIN_DESC g_d3dSwapChain = {};
	inline ID3D11DeviceContext* g_pd3dContext = nullptr;
	inline IDXGISwapChain* g_pSwapChain = nullptr;
	inline ID3D11RenderTargetView* g_mainTargetView = nullptr;

    void Init();
    void Destroy();
}