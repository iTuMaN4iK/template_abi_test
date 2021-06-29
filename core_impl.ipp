#pragma once

#define CORE_SOURCE

#include "core.hpp"

template<typename>
int get()
{
    static int val = 0;
    return ++val;
}

template<typename>
int foo::get()
{
    static int val = 0;
    return ++val;
}

template<typename T>
int foo_template<T>::get()
{
    static int val = 0;
    return ++val;
}