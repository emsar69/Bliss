#include <Bliss/il2cpp_Functions.h>

#if defined(__ANDROID__)
    #include <dlfcn.h>
    #define Resv(addr, n) \
        n = (n##_t)dlsym(addr, #n);
#elif defined(_WIN32)
    #include <windows.h>
    #define Resv(addr, n) \
        n = (n##_t)GetProcAddress((HMODULE)addr, #n);
#endif

void il2cpp_Functions::SetupFunctions(void* addr){
    Resv(addr, il2cpp_assembly_get_image);
    Resv(addr, il2cpp_class_from_name);
    Resv(addr, il2cpp_class_get_field_from_name);
    Resv(addr, il2cpp_class_get_fields);
    Resv(addr, il2cpp_class_get_methods);
    Resv(addr, il2cpp_class_get_parent);
    Resv(addr, il2cpp_class_get_type);
    Resv(addr, il2cpp_domain_get_assemblies);
    Resv(addr, il2cpp_domain_get);
    Resv(addr, il2cpp_field_get_name);
    Resv(addr, il2cpp_field_get_offset);
    Resv(addr, il2cpp_field_get_type);
    Resv(addr, il2cpp_field_get_value);
    Resv(addr, il2cpp_field_static_get_value);
    Resv(addr, il2cpp_image_get_name);
    Resv(addr, il2cpp_method_get_name);
    Resv(addr, il2cpp_method_get_param_count);
    Resv(addr, il2cpp_method_get_param);
    Resv(addr, il2cpp_runtime_invoke);
    Resv(addr, il2cpp_string_new);
    Resv(addr, il2cpp_thread_attach);
    Resv(addr, il2cpp_thread_detach);
    Resv(addr, il2cpp_type_get_attrs);
    Resv(addr, il2cpp_type_get_name);
    Resv(addr, il2cpp_type_get_object);
}