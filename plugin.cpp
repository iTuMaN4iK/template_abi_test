
#include "core.hpp"
#include "export_types.hpp"

#ifdef _WIN32
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT
#endif

extern "C"
{
DLL_EXPORT int foo_class_template();
DLL_EXPORT int foo_class_function_template();
DLL_EXPORT int get_value();
}

int foo_class_template()
{
    return foo_template<old>::get();
}

int foo_class_function_template()
{
    return foo::get<old>();
}

int get_value()
{
    return get<old>();
}
