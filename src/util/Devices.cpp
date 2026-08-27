#ifdef __WIN32__ //Disable completely if its not win32


#include <Bliss/Devices.h>
#include <Bliss/Gui.h>

bool SetupDirectX() {
	D3D_FEATURE_LEVEL levels[] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_1 };
	RECT clientRect{};
	if (!GetClientRect(Gui::window, &clientRect))
		return false;

	const UINT clientWidth = static_cast<UINT>(clientRect.right - clientRect.left);
	const UINT clientHeight = static_cast<UINT>(clientRect.bottom - clientRect.top);
	
	ZeroMemory(&Devices::g_d3dSwapChain, sizeof(Devices::g_d3dSwapChain));

	Devices::g_d3dSwapChain.BufferCount = 1;
	Devices::g_d3dSwapChain.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	Devices::g_d3dSwapChain.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	Devices::g_d3dSwapChain.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	Devices::g_d3dSwapChain.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	// This swap chain only exists long enough to obtain the DXGI vtable used by
	// the hooks. Never allow it to switch the monitor's display mode.
	Devices::g_d3dSwapChain.Flags = 0;
	Devices::g_d3dSwapChain.OutputWindow = Gui::window;
	Devices::g_d3dSwapChain.SampleDesc.Count = 1;
	Devices::g_d3dSwapChain.Windowed = TRUE;
	Devices::g_d3dSwapChain.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	Devices::g_d3dSwapChain.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	Devices::g_d3dSwapChain.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	Devices::g_d3dSwapChain.BufferDesc.Width = clientWidth > 0 ? clientWidth : 1;
	Devices::g_d3dSwapChain.BufferDesc.Height = clientHeight > 0 ? clientHeight : 1;
	Devices::g_d3dSwapChain.BufferDesc.RefreshRate.Numerator = 0;
	Devices::g_d3dSwapChain.BufferDesc.RefreshRate.Denominator = 1;

	HRESULT result = D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		0,
		levels,
		sizeof(levels) / sizeof(D3D_FEATURE_LEVEL),
		D3D11_SDK_VERSION,
		&Devices::g_d3dSwapChain,
		&Devices::g_pSwapChain,
		&Devices::g_pd3dDevice,
		nullptr,
		&Devices::g_pd3dContext
	);

	if (FAILED(result)) 
		return false;

	return true;
}

void DestroyDirectX() {
	if (Devices::g_mainTargetView) { Devices::g_mainTargetView->Release(); Devices::g_mainTargetView = nullptr; }
	if (Devices::g_pSwapChain) { Devices::g_pSwapChain->Release(); Devices::g_pSwapChain = nullptr; }
	if (Devices::g_pd3dDevice) { Devices::g_pd3dDevice->Release(); Devices::g_pd3dDevice = nullptr; }
	if (Devices::g_pd3dContext) { Devices::g_pd3dContext->Release(); Devices::g_pd3dContext = nullptr; }
}

void Devices::Init() {
	Gui::window = FindWindowA(NULL, "Among Us");
	if (Gui::window == NULL) throw std::runtime_error("Window Not Found.");

	if (!SetupDirectX())
		throw std::runtime_error("Failed to setup DirectX");
}

void Devices::Destroy() {
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	SetWindowLongPtr(
		Gui::window,
		GWLP_WNDPROC,
		reinterpret_cast<LONG_PTR>(Gui::originalWindowProcess)
	);

	DestroyDirectX();
}

#endif