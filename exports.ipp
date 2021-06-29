#pragma once

#include "core_impl.ipp"
#include "export_types.hpp"

template struct foo_template<old>;
template int foo::get<old>();
template int get<old>();

#ifdef NEXT_VERSION

struct new_0 {
};
template struct foo_template<new_0>;
template int foo::get<new_0>();
template int get<new_0>();

struct new_1 {
};
template struct foo_template<new_1>;
template int foo::get<new_1>();
template int get<new_1>();

struct new_2 {
};
template struct foo_template<new_2>;
template int foo::get<new_2>();
template int get<new_2>();

struct new_3 {
};
template struct foo_template<new_3>;
template int foo::get<new_3>();
template int get<new_3>();
#endif
