#pragma once

#include <Bliss/il2cpp_Functions.h>
#include <Bliss/Logger.h>
#include <unordered_map>
#include <string>

struct Il2CppMemberInfo {
    enum Type {
        FIELD,
        STATIC_FIELD,
        METHOD
    };

    Type type;
    size_t offset = 0;
    size_t paramCount = 0;
    void* static_field = nullptr;
    void* method_object = nullptr;
    void* method_addr = nullptr;

    Il2CppMemberInfo() : type(Type::FIELD), offset(0), paramCount(0), method_object(nullptr), method_addr(nullptr) {};
};

using MemberMap = std::unordered_map<std::string, Il2CppMemberInfo>;
struct Il2CppObject {
    void* self = nullptr;
    MemberMap* members = nullptr;

    Il2CppObject(void* inst, MemberMap* members) : self(inst), members(members) {};

    void* GetComponent(void* type) {
        void* params[1];
        params[0] = type;

        return CallMethod<void>("GetComponent", params);
    }

    explicit operator bool() noexcept { //turns out not all objects have m_CachedPtr.
        if(self == nullptr) return false;
        if(members->find("m_CachedPtr") == members->end()) return true; //return true because it has no m_CachedPtr and self is valid.

        void** ptr = GetField<void*>("m_CachedPtr");
        if(ptr == nullptr) return false;
        if(*ptr == nullptr) return false;

        return true;
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
    T* CallStaticMethod(const char* MethodName, void** params=nullptr, void* inst=nullptr){
        if(!members) return nullptr;
        auto it = members->find(MethodName);
        if(it == members->end()) {
            Logger::Warn("Attempted to access invalid method name: %s\n", MethodName);
            return nullptr;
        }
        Il2CppMemberInfo member = it->second;
        if(member.type != Il2CppMemberInfo::Type::METHOD) {
            Logger::Warn("%s is NOT a method.\n", MethodName);
            return nullptr;
        }

        void* exp = nullptr;
        void* result = il2cpp_Functions::il2cpp_runtime_invoke(member.method_object, inst, params, &exp);

        if(exp) {
            Logger::Error("EXCEPTION IN CALL METHOD!!!!\n\nMETHOD NAME: %s\nINSTANCE: %p\n", MethodName, inst);
            return nullptr;
        }

        return reinterpret_cast<T*>(result);
    }

    template <typename T>
    T* CallMethod(const char* MethodName, void** params=nullptr){
        if(self == nullptr) {
            Logger::Warn("Tried to call instance method where instance is NOT DEFINED PROPERLY.\n\nMethod Name: %s\n", MethodName);
            return nullptr;
        }
        return CallStaticMethod<T>(MethodName, params, self);
    }
};