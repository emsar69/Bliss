#include <Windows.h>
#include <thread>
#include <exception>
#include <Bliss/Devices.h>
#include <Bliss/Hooks.h>
#include <Bliss/Memory.h>
#include <Bliss/Gui.h>

void Entry(HMODULE module) {
    AllocConsole();
    freopen("CONOUT$", "w", stdout);
    try{
        Devices::Init();
        Hooks::Setup();
        Memory::Init();
    }catch(const std::exception& e){
        goto UNLOAD;
    }

    while(!GetAsyncKeyState(VK_END)){
        std::this_thread::sleep_for(std::chrono::milliseconds(128));
    }

UNLOAD:
    Gui::enabled = false;
    Hooks::Destroy();
    Devices::Destroy();
    FreeConsole();
    FreeLibraryAndExitThread(module, 0);
}

BOOL WINAPI DllMain(HMODULE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
    if(fdwReason == DLL_PROCESS_ATTACH){
        DisableThreadLibraryCalls(hinstDLL);
        HANDLE thread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Entry, hinstDLL, 0, 0);
        if(thread) CloseHandle(thread);
    }
    return TRUE;
}