#pragma once

#include "core.hpp"

struct old{};

extern template struct foo_template<old>;
extern template int foo::get<old>();
extern template int get<old>();
