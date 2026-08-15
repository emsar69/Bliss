#pragma once

#include <Windows.h>

#define IL2CPP_CALLING_CONVENTION __cdecl

using il2cpp_assembly_get_image_t = void*(IL2CPP_CALLING_CONVENTION*)(void*);
using il2cpp_class_from_name_t = void*(IL2CPP_CALLING_CONVENTION*)(void*, const char*, const char*);
using il2cpp_class_get_field_from_name_t = void*(IL2CPP_CALLING_CONVENTION*)(void*, const char*);
using il2cpp_class_get_fields_t = void*(IL2CPP_CALLING_CONVENTION*)(void*, void**);
using il2cpp_class_get_methods_t = void*(IL2CPP_CALLING_CONVENTION*)(void*, void**);
using il2cpp_class_get_parent_t = void*(IL2CPP_CALLING_CONVENTION*)(void*);
using il2cpp_class_get_type_t = void*(IL2CPP_CALLING_CONVENTION*)(void*);
using il2cpp_domain_get_assemblies_t = void*(IL2CPP_CALLING_CONVENTION*)(void* a1, size_t* a2);
using il2cpp_domain_get_t = void*(IL2CPP_CALLING_CONVENTION*)();
using il2cpp_field_get_name_t = const char*(IL2CPP_CALLING_CONVENTION*)(void*);
using il2cpp_field_get_offset_t = size_t(IL2CPP_CALLING_CONVENTION*)(void*);
using il2cpp_field_get_type_t = void*(IL2CPP_CALLING_CONVENTION*)(void*);
using il2cpp_field_get_value_t = void(IL2CPP_CALLING_CONVENTION*)(void*, void*, void*);
using il2cpp_field_static_get_value_t = void(IL2CPP_CALLING_CONVENTION*)(void*, void*);
using il2cpp_image_get_name_t = const char*(IL2CPP_CALLING_CONVENTION*)(void*);
using il2cpp_method_get_name_t = const char*(IL2CPP_CALLING_CONVENTION*)(void*);
using il2cpp_method_get_param_count_t = size_t(IL2CPP_CALLING_CONVENTION*)(void*);
using il2cpp_method_get_param_t = void*(IL2CPP_CALLING_CONVENTION*)(void*, int);
using il2cpp_runtime_invoke_t = void*(IL2CPP_CALLING_CONVENTION*)(void*, void*, void**, void**);
using il2cpp_string_new_t = void*(IL2CPP_CALLING_CONVENTION*)(const char*);
using il2cpp_thread_attach_t = void*(IL2CPP_CALLING_CONVENTION*)(void*);
using il2cpp_thread_detach_t = void*(IL2CPP_CALLING_CONVENTION*)(void*);
using il2cpp_type_get_attrs_t = int(IL2CPP_CALLING_CONVENTION*)(void*);
using il2cpp_type_get_name_t = const char*(IL2CPP_CALLING_CONVENTION*)(void*);
using il2cpp_type_get_object_t = void*(IL2CPP_CALLING_CONVENTION*)(void*);

namespace il2cpp_Functions {
    inline il2cpp_assembly_get_image_t il2cpp_assembly_get_image;
    inline il2cpp_class_from_name_t il2cpp_class_from_name;
    inline il2cpp_class_get_field_from_name_t il2cpp_class_get_field_from_name;
    inline il2cpp_class_get_fields_t il2cpp_class_get_fields;
    inline il2cpp_class_get_methods_t il2cpp_class_get_methods;
    inline il2cpp_class_get_parent_t il2cpp_class_get_parent;
    inline il2cpp_class_get_type_t il2cpp_class_get_type;
    inline il2cpp_domain_get_assemblies_t il2cpp_domain_get_assemblies;
    inline il2cpp_domain_get_t il2cpp_domain_get;
    inline il2cpp_field_get_name_t il2cpp_field_get_name;
    inline il2cpp_field_get_offset_t il2cpp_field_get_offset;
    inline il2cpp_field_get_type_t il2cpp_field_get_type;
    inline il2cpp_field_get_value_t il2cpp_field_get_value;
    inline il2cpp_field_static_get_value_t il2cpp_field_static_get_value;
    inline il2cpp_image_get_name_t il2cpp_image_get_name;
    inline il2cpp_method_get_name_t il2cpp_method_get_name;
    inline il2cpp_method_get_param_count_t il2cpp_method_get_param_count;
    inline il2cpp_method_get_param_t il2cpp_method_get_param;
    inline il2cpp_runtime_invoke_t il2cpp_runtime_invoke;
    inline il2cpp_string_new_t il2cpp_string_new;
    inline il2cpp_thread_attach_t il2cpp_thread_attach;
    inline il2cpp_thread_detach_t il2cpp_thread_detach;
    inline il2cpp_type_get_attrs_t il2cpp_type_get_attrs;
    inline il2cpp_type_get_name_t il2cpp_type_get_name;
    inline il2cpp_type_get_object_t il2cpp_type_get_object;

    void SetupFunctions(HMODULE il2cpp_addr);
}