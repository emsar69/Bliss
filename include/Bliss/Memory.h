#pragma once

#include <Windows.h>
#include <Bliss/Game.h>

namespace Memory {
    inline HMODULE GameAssembly = NULL;
    inline void* Domain = nullptr;
    inline void* Assembles = nullptr;
    inline void* CSharpAssemble = nullptr;
    inline void* Hazel = nullptr;
    inline void* UnityEngine_CoreModule = nullptr; // This has UnityEngine.Camera::get_main();
    inline size_t Assemble_Count = 0;

    void Init();
    void* GetAssembleByName(const char* name);
}