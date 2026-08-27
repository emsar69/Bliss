#pragma once

namespace Gui {
    inline bool open = true;
    inline bool enabled = true;
	inline bool setup = false;

    #if defined(__WIN32__)
        #include <d3d11.h>

        inline HWND window = NULL;
        inline WNDPROC originalWindowProcess = nullptr;

        void WinSetupMenu(ID3D11Device* device, ID3D11DeviceContext* context);
    #elif defined(__ANDROID__)
        void AndSetupMenu();
    #endif

    void Render();
}