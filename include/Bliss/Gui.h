#pragma once

#include <d3d11.h>

namespace Gui {
    inline bool open = true;
    inline bool enabled = true;
	inline bool setup = false;

    inline bool enable_get_is_impostor_hook = false; // I'll remove all features to single header later.

	inline HWND window = NULL;
	inline WNDPROC originalWindowProcess = nullptr;

    void SetupMenu(ID3D11Device* device, ID3D11DeviceContext* context);

    void Render();
}