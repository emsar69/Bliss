#include <Bliss/Memory.h>
#include <Bliss/il2cpp_Functions.h>
#include <Bliss/Offsets.h>

#include <cstdio>
#include <stdexcept>
#include "Memory.h"

void Memory::Init(){
    Memory::GameAssembly = GetModuleHandleA("GameAssembly.dll");

    il2cpp_Functions::SetupFunctions(GameAssembly);
    
    Domain = il2cpp_Functions::il2cpp_domain_get();
    if(Domain == nullptr) {
        throw std::runtime_error("No domain were returned.");
        return;
    }

    Assembles = il2cpp_Functions::il2cpp_domain_get_assemblies(Domain, &Assemble_Count);
    if(Assemble_Count == 0) {
        throw std::runtime_error("No assembles were returned.");
        return;
    }

    CSharpAssemble = GetAssembleByName("Assembly-CSharp.dll");
    Hazel = GetAssembleByName("Hazel.dll");
    UnityEngine_CoreModule = GetAssembleByName("UnityEngine.CoreModule.dll");
    UnityEngine_Physics2DModule = GetAssembleByName("UnityEngine.Physics2DModule.dll");

    void* cc2_klas = il2cpp_Functions::il2cpp_class_from_name(Memory::UnityEngine_Physics2DModule, "UnityEngine", "CircleCollider2D");
    void* klas_type = il2cpp_Functions::il2cpp_class_get_type(cc2_klas);
    Types::CircleCollider2D = il2cpp_Functions::il2cpp_type_get_object(klas_type);

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