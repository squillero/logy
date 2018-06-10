// -*- mode: c++ -*-

// logy v1.0 -- A simplistic, light-weight, single-header C++ logger
// (!) June 2018 by Giovanni Squillero <giovanni.squillero@polito.it>
// This code has been dedicated to the public domain -- see LICENSE.md
// Project page: https://github.com/squillero/logy

#pragma once

#include <cstdio>
#include <ctime>

// helper functions

static inline void logy_header(const char* tag) {
    char timestamp[100] = "";
    std::time_t t = std::time(nullptr);
    std::strftime(timestamp, sizeof(timestamp), "[%H:%M:%S] ", std::localtime(&t));
    std::fprintf(stderr, "%s%s", timestamp, tag);
}

static inline void logy_helper() {
    std::cerr << std::endl;
}
template<typename F, typename ...R>
void logy_helper(F&& first, R&& ...rest) {
    std::cerr << " " << std::forward<F>(first);
    logy_helper(std::forward<R>(rest)...);
}

// good old printf syntax

template<typename... T>
void _Debug(T... args) {
    logy_header("DEBUG: ");
    std::fprintf(stderr, args...);
    std::fprintf(stderr, "\n");
    std::fflush(stderr);
}

template<typename... T>
void _Info(T... args) {
    logy_header("INFO: ");
    std::fprintf(stderr, args...);
    std::fprintf(stderr, "\n");
    std::fflush(stderr);
}

template<typename... T>
void _Warning(T... args) {
    logy_header("WARNING: ");
    std::fprintf(stderr, args...);
    std::fprintf(stderr, "\n");
    std::fflush(stderr);
}

// "just print it" syntax

template<typename... T>
static inline void _Debug2(T... args) {
    logy_header("DEBUG:");
    logy_helper(std::forward<T>(args)...);
}

template<typename... T>
static inline void _Info2(T... args) {
    logy_header("INFO:");
    logy_helper(std::forward<T>(args)...);
}

template<typename... T>
static inline void _Warning2(T... args) {
    logy_header("WARNING:");
    logy_helper(std::forward<T>(args)...);
}

#if defined(DEBUG)

#define Debug(args...) _Debug(args)
#define Info(args...) _Info(args)
#define Warning(args...) _Warning(args)
#define LOG_DEBUG(args...) _Debug2(args)
#define LOG_INFO(args...) _Info2(args)
#define LOG_WARNING(args...) _Warning2(args)

#elif defined(VERBOSE)

#define Debug(args...) ((void)0)
#define Info(args...) _Info(args)
#define Warning(args...) _Warning(args)
#define LOG_DEBUG(args...) ((void)0)
#define LOG_INFO(args...) _Info2(args)
#define LOG_WARNING(args...) _Warning2(args)

#else

#define Debug(args...) ((void)0)
#define Info(args...) ((void)0)
#define Warning(args...) _Warning(args)
#define LOG_DEBUG(args...) ((void)0)
#define LOG_INFO(args...) ((void)0)
#define LOG_WARNING(args...) _Warning2(args)

#endif
