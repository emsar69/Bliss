#pragma once

#include <Bliss/il2cpp_Functions.h>
#include <unordered_map>
#include <string>

struct Il2CppMemberInfo {
    enum Type {
        FIELD,
        METHOD
    };

    Type type;
    size_t offset = 0;
    size_t paramCount = 0;
    void* methodPtr = nullptr;

    Il2CppMemberInfo() : type(Type::FIELD), offset(0), paramCount(0), methodPtr(nullptr) {};
};

using MemberMap = std::unordered_map<std::string, Il2CppMemberInfo>;
struct Il2CppObject {
    void* self = nullptr;
    MemberMap* members = nullptr;

    Il2CppObject(void* inst, MemberMap* members) : self(inst), members(members) {};

    explicit operator bool() noexcept {
        return self != nullptr;
    }

protected:
    template <typename T>
    T* GetField(const char* FieldName){
        if(!members) return nullptr;
        auto it = members->find(FieldName);
        if(it == members->end()) return nullptr;
        Il2CppMemberInfo member = it->second;
        if(member.type != Il2CppMemberInfo::Type::FIELD) return nullptr;

        return reinterpret_cast<T*>((uintptr_t)self + member.offset);
    }

    template <typename T>
    T* CallMethod(const char* MethodName, void** params=nullptr){
        if(!members) return nullptr;
        auto it = members->find(MethodName);
        if(it == members->end()) return nullptr;
        Il2CppMemberInfo member = it->second;
        if(member.type != Il2CppMemberInfo::Type::METHOD) return nullptr;

        void* result = il2cpp_Functions::il2cpp_runtime_invoke(member.methodPtr, self, params, nullptr);
        return reinterpret_cast<T*>(result);
    }
};