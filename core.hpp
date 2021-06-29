#pragma once

#ifdef _WIN32
#if defined(BUILD_DLL)
#define CORE_API __declspec(dllexport)
#else
#define CORE_API __declspec(dllimport)
#endif
#else
#define CORE_API
#endif

#if defined(_WIN32)
#if defined(DYN_LINK)
#if defined(CORE_SOURCE)
#define CORE_DECL __declspec(dllexport)
#else
#define CORE_DECL __declspec(dllimport)
#endif
#endif
#endif

#ifndef CORE_DECL
#define CORE_DECL
#endif

template<typename>
struct CORE_API foo_template {
    CORE_DECL static int get();
};

struct CORE_API foo {
    template<typename>
    CORE_DECL static int get();
};

template<typename>
CORE_DECL inline int get();
