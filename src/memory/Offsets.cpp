#include <Bliss/Offsets.h>
#include <Bliss/Memory.h>
#include <Bliss/il2cpp_Functions.h>

void FindMembersRecursive(const char* ClassName, void* klass, MemberMap& arr) {
    void* iter = nullptr;
    void* entry = nullptr;
    while((entry = il2cpp_Functions::il2cpp_class_get_fields(klass, &iter)) != nullptr){
        const char* name = il2cpp_Functions::il2cpp_field_get_name(entry);

        void* type = il2cpp_Functions::il2cpp_field_get_type(entry);
        uint32_t attr = il2cpp_Functions::il2cpp_type_get_attrs(type);

        Il2CppMemberInfo info;
        if(attr & 0x10) { // Remember that this initializes ONCE. meaning, only access if that's fixed data. like roleids or doorids.
            void* static_val;
            il2cpp_Functions::il2cpp_field_static_get_value(entry, &static_val);
            info.type = Il2CppMemberInfo::Type::STATIC_FIELD;
            info.static_field = static_val;

            printf("%s.%s = %p (static)\n", ClassName, name, static_val);
        } else {
            size_t offset = il2cpp_Functions::il2cpp_field_get_offset(entry);
            info.type = Il2CppMemberInfo::Type::FIELD;
            info.offset = offset;
            
            printf("%s.%s = 0x%02x\n", ClassName, name, offset);
        }
        arr[name] = info;
    }

    iter = nullptr;
    while((entry = il2cpp_Functions::il2cpp_class_get_methods(klass, &iter)) != nullptr){
        const char* name = il2cpp_Functions::il2cpp_method_get_name(entry);
        
        Il2CppMemberInfo info;
        info.type = Il2CppMemberInfo::Type::METHOD;
        info.method_object = entry;

        // I actually could've write this better lol but I'm too lazy to think about it since this works.
        if(strcmp(name, "Write") == 0) {
            void* param = il2cpp_Functions::il2cpp_method_get_param(entry, 0);
            std::string type(il2cpp_Functions::il2cpp_type_get_name(param));
            type = "Write"+type.substr(6);
            
            arr[type] = info;
            printf("%s.%s() = 0x%p\n", ClassName, type.c_str(), entry);
        }else{
            if(arr.contains(name)) {
                int param_count = il2cpp_Functions::il2cpp_method_get_param_count(entry);
                std::string nm(name);
                nm += "_dup_"+std::to_string(param_count); // and I don't care if there're more than 2 duplicates. too lazy + not needed
                arr[nm.c_str()] = info;
                printf("%s.%s() = 0x%p\n", ClassName, nm.c_str(), entry);
            }else{
                arr[name] = info;
                printf("%s.%s() = 0x%p\n", ClassName, name, entry);
            }
        }
    }

    void* parent = il2cpp_Functions::il2cpp_class_get_parent(klass);
    if(parent) FindMembersRecursive(ClassName, parent, arr);
}

void FindMembers(const char* ClassName, MemberMap& arr, const char* NameSpace="", void* Base = Memory::CSharpAssemble){
    void* klass = il2cpp_Functions::il2cpp_class_from_name(Base, NameSpace, ClassName);
    if(klass == nullptr) {
        printf("Couldn't find class with;\nNameSpace: %s\nName: %s\n", NameSpace, ClassName);
        return;
    }

    FindMembersRecursive(ClassName, klass, arr);
}

void Offsets::Init() {
    FindMembers("PlayerControl", PlayerControlMembers);
    FindMembers("NetworkedPlayerInfo", PlayerDataMembers);
    FindMembers("PlayerPhysics", PlayerPhysicsMembers);
    FindMembers("RoleBehaviour", RoleMembers);
    FindMembers("CosmeticsLayer", CosmeticsLayerMembers);
    FindMembers("AmongUsClient", AmongUsClientMembers);
    FindMembers("InnerNetClient", InnerNetMembers, "InnerNet");
    FindMembers("MessageWriter", WriterMembers, "Hazel", Memory::Hazel);
    FindMembers("RoleManager", RoleManager);
    FindMembers("Camera", CameraMembers, "UnityEngine", Memory::UnityEngine_CoreModule);
    FindMembers("Transform", TransformMembers, "UnityEngine", Memory::UnityEngine_CoreModule);
    FindMembers("GameObject", GameObjectMembers, "UnityEngine", Memory::UnityEngine_CoreModule);
    FindMembers("Behaviour", UnityEngineBehaviourMembers, "UnityEngine", Memory::UnityEngine_CoreModule); // That's for not typing unnecessary classes over and over again.
    FindMembers("ShipStatus", ShipStatusMembers);
    FindMembers("SystemTypes", SystemTypesMembers);
    FindMembers("GameOptionsManager", GameOptionsManagerMembers);
    FindMembers("NormalGameOptionsV10", NormalGameOptionsV10Members, "AmongUs.GameOptions");

    void* addr = WriterMembers["Write.String"].method_object;
    MEMORY_BASIC_INFORMATION mbi;
    VirtualQuery(addr, &mbi, sizeof(mbi));
    printf("Permissions for Write.String:\nReg size: 0x%X, Protect: 0x%X, State: 0x%x\n", mbi.RegionSize, mbi.Protect, mbi.State);

    Initialized = true;
}