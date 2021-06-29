
#include "core.hpp"
#include "export_types.hpp"

extern "C"
{
__declspec(dllexport) int plugin_non_template();
__declspec(dllexport) int foo_class_template();
__declspec(dllexport) int foo_class_function_template();
__declspec(dllexport) int get_value();
}

int plugin_non_template()
{
    return non_template();
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
