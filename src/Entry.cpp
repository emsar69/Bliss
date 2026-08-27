// Copyright (C) 2026 emsar69
// SPDX-License-Identifier: GPL-3.0-or-later
// See the LICENSE file for the full license text.

#include <thread>
#include <exception>
#include <Bliss/Hooks.h>
#include <Bliss/Memory.h>
#include <Bliss/Gui.h>
#include <Bliss/Logger.h>

#if defined(__ANDROID__)

void* AndEntry(void*) {
    try{
        Memory::Init();
        Hooks::Setup();
    }catch(const std::exception& e){
        Logger::Fatal("Error during setup: %s", e.what());
    }
    
    return nullptr;
}

__attribute__((constructor))
void SoMain() {
    Logger::Debug("Hello from main!");
    pthread_t thread;
    pthread_create(&thread, nullptr, AndEntry, nullptr);
    pthread_detach(thread);
}

#elif defined(_WIN32)
    
#include <Bliss/Devices.h>
#include <windows.h>


void WinEntry(HMODULE module) {
    AllocConsole();
    freopen("CONOUT$", "w", stdout);
    try{
        Devices::Init();
        Memory::Init();
        Hooks::Setup();
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
        HANDLE thread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)WinEntry, hinstDLL, 0, 0);
        if(thread) CloseHandle(thread);
    }
    return TRUE;
}

#endif