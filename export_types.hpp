#pragma once

#include "core.hpp"

struct old{};

extern template struct foo_template<old>;
extern template int CORE_API foo::get<old>();
extern template int CORE_API get<old>();
