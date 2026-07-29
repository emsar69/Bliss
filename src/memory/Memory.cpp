#include <Bliss/Memory.h>
#include <Bliss/il2cpp_Functions.h>
#include <Bliss/Offsets.h>

#include <cstdio>
#include "Memory.h"

void Memory::Init(){
    Memory::GameAssembly = GetModuleHandleA("GameAssembly.dll");

    il2cpp_Functions::SetupFunctions(GameAssembly);
    
    Domain = il2cpp_Functions::il2cpp_domain_get();
    Assembles = il2cpp_Functions::il2cpp_domain_get_assemblies(Domain, &Assemble_Count);
    CSharpAssemble = GetAssembleByName("Assembly-CSharp.dll");
    Hazel = GetAssembleByName("Hazel.dll");
    UnityEngine_CoreModule = GetAssembleByName("UnityEngine.CoreModule.dll");

    Offsets::Init();
}

void *Memory::GetAssembleByName(const char *name) {
    for(size_t i = 0; i < Assemble_Count-1; i++){
        void* assemble = ((void**)Assembles)[i];
        void* img = il2cpp_Functions::il2cpp_assembly_get_image(assemble);
        const char* img_name = il2cpp_Functions::il2cpp_image_get_name(img);

        if(strcmp(img_name, name) == 0) return img;
    }
    return nullptr;
}