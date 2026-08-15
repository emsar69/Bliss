#include <Bliss/Hooks.h>
#include <Bliss/Devices.h>
#include <Bliss/Gui.h>
#include <Bliss/Memory.h>
#include <Bliss/Offsets.h>

#include <stdexcept>
#include <cstdint>
#include <intrin.h>

#include <MinHook.h>
#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_win32.h>
#include <imgui/backends/imgui_impl_dx11.h>

void Hooks::Setup() {
	if (MH_Initialize() != MH_OK)
		throw std::runtime_error("MinHook initialization error");

	std::uintptr_t* swapChainPointer =
		static_cast<std::uintptr_t*>(static_cast<void*>(Devices::g_pSwapChain));

	std::uintptr_t* virtualTablePointer =
		reinterpret_cast<std::uintptr_t*>(swapChainPointer[0]);

	oPresent = (PresentFn)(virtualTablePointer[8]);
    oResize = (ResizeFn)(virtualTablePointer[13]);

	if (MH_CreateHook(
		reinterpret_cast<LPVOID>(virtualTablePointer[8]),
		reinterpret_cast<LPVOID>(&PresentHook),
		reinterpret_cast<LPVOID*>(&oPresent)
	)) throw std::runtime_error("unable to create PresentHook");

	if (MH_CreateHook(
		reinterpret_cast<LPVOID>(virtualTablePointer[13]),
		reinterpret_cast<LPVOID>(&ResizeHook),
		reinterpret_cast<LPVOID*>(&oResize)
	)) throw std::runtime_error("unable to create ResizeHook");

	if(MH_CreateHook(
		reinterpret_cast<LPVOID>(Offsets::PlayerControlMembers["MurderPlayer"].method_addr),
		reinterpret_cast<LPVOID>(&MurderPlayerHook),
		reinterpret_cast<LPVOID*>(&oMurderPlayer)
	)) throw std::runtime_error("unable to create PlayerMurder hook");

	if (MH_EnableHook(MH_ALL_HOOKS))
		throw std::runtime_error("Unable to enable hooks");
}

void Hooks::Destroy() {
	MH_DisableHook(MH_ALL_HOOKS);
	MH_RemoveHook(MH_ALL_HOOKS);
	MH_Uninitialize();

	// Commented out bcuz it won't work (Different threads)
	// il2cpp_Functions::il2cpp_thread_detach(Memory::il2cpp_thread);
}

HRESULT __stdcall Hooks::PresentHook(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags) noexcept {
	if (!Gui::setup) {
		pSwapChain->GetDevice(__uuidof(Devices::g_pd3dDevice), reinterpret_cast<void**>(&Devices::g_pd3dDevice));
		Devices::g_pd3dDevice->GetImmediateContext(&Devices::g_pd3dContext);

		ID3D11Texture2D* pBackBuffer;
		pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
		Devices::g_pd3dDevice->CreateRenderTargetView(pBackBuffer, NULL, &Devices::g_mainTargetView);
		pBackBuffer->Release();

		Memory::il2cpp_thread = il2cpp_Functions::il2cpp_thread_attach(Memory::Domain);

		Gui::SetupMenu(Devices::g_pd3dDevice, Devices::g_pd3dContext);
	}
	
	if (Gui::enabled){
		Gui::Render();
	}
	return oPresent(pSwapChain, SyncInterval, Flags);
}

HRESULT __stdcall Hooks::ResizeHook(IDXGISwapChain* pSwapChain, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags) noexcept
{
	if (Devices::g_mainTargetView) {
		Devices::g_pd3dContext->OMSetRenderTargets(0, 0, 0);
		Devices::g_mainTargetView->Release();
		//Devices::g_mainTargetView = nullptr;
	}

	ImGui_ImplDX11_InvalidateDeviceObjects();

	HRESULT hr = oResize(pSwapChain, BufferCount, Width, Height, NewFormat, SwapChainFlags);

	ID3D11Texture2D* pBuffer;
	if(SUCCEEDED(pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&pBuffer))){
		Devices::g_pd3dDevice->CreateRenderTargetView(pBuffer, NULL, &Devices::g_mainTargetView);
		pBuffer->Release();
	}

	Devices::g_pd3dContext->OMSetRenderTargets(1, &Devices::g_mainTargetView, NULL);
	// Set up the viewport.
	D3D11_VIEWPORT vp;
	vp.Width = Width;
	vp.Height = Height;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	Devices::g_pd3dContext->RSSetViewports(1, &vp);

	ImGui_ImplDX11_CreateDeviceObjects();
	
	return hr;
}

void __cdecl Hooks::MurderPlayerHook(void* self, void* target, int flags) noexcept {
	if(flags & 1) { // lowest bit stands for successful kill.
		PlayerControl killer(self);

		killer.state.last_kill = GetTickCount64();
	}

	oMurderPlayer(self, target, flags);
}