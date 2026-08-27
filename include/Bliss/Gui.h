#pragma once

namespace Gui {
    inline bool open = true;
    inline bool enabled = true;
	inline bool setup = false;

    #if defined(_WIN32)
        #include <d3d11.h>

        inline HWND window = NULL;
        inline WNDPROC originalWindowProcess = nullptr;

        void WinSetupMenu(ID3D11Device* device, ID3D11DeviceContext* context);
    #elif defined(__ANDROID__)
        void AndSetupMenu();
    #endif

    void Render();
}