// -*- mode: c++ -*-

// logy v1.01 -- A simplistic, light-weight, single-header C++ logger
// (!) Summer 2018 by Giovanni Squillero <giovanni.squillero@polito.it>
// This code has been dedicated to the public domain (see LICENSE.md)
// Project page: https://github.com/squillero/logy

#pragma once

#include <iostream>
#include <string>
#include <cstdio>
#include <ctime>

// helper functions

static inline void logy_header(const char* tag) {
    char timestamp[100] = "";
    std::time_t t = std::time(nullptr);
    std::strftime(timestamp, sizeof(timestamp), "[%H:%M:%S]", std::localtime(&t));
    std::fprintf(stderr, "%s%s", timestamp, tag);
}

static inline void logy_helper() {
    std::cerr << std::endl;
}
template<typename F, typename... R>
void logy_helper(F&& first, R&&... rest) {
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

template<typename... T>
void _Silent(T... args) {
    logy_header(" ");
    std::fprintf(stderr, args...);
    std::fprintf(stderr, "\n");
    std::fflush(stderr);
}

// redundant, strictly speaking, but avoids the unaesthetic format-string-is-not-a-literal warning
static void _Debug(const char *arg) {
    logy_header("DEBUG: ");
    std::fprintf(stderr, "%s\n", arg);
    std::fflush(stderr);
}
static void _Info(const char *arg) {
    logy_header("INFO: ");
    std::fprintf(stderr, "%s\n", arg);
    std::fflush(stderr);
}
static void _Warning(const char *arg) {
    logy_header("WARNING: ");
    std::fprintf(stderr, "%s\n", arg);
    std::fflush(stderr);
}
static void _Silent(const char *arg) {
    logy_header(" ");
    std::fprintf(stderr, "%s\n", arg);
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

template<typename... T>
static inline void _Silent2(T... args) {
    logy_header("");
    logy_helper(std::forward<T>(args)...);
}

#if defined(DEBUG) or defined(LOGGING_DEBUG)

#define Debug(...) _Debug(__VA_ARGS__)
#define Info(...) _Info(__VA_ARGS__)
#define Warning(...) _Warning(__VA_ARGS__)
#define LOG_DEBUG(...) _Debug2(__VA_ARGS__)
#define LOG_INFO(...) _Info2(__VA_ARGS__)
#define LOG_WARNING(...) _Warning2(__VA_ARGS__)

#elif defined(VERBOSE) or defined(LOGGING_VERBOSE)

#define Debug(...) ((void)0)
#define Info(...) _Info(__VA_ARGS__)
#define Warning(...) _Warning(__VA_ARGS__)
#define LOG_DEBUG(...) ((void)0)
#define LOG_INFO(...) _Info2(__VA_ARGS__)
#define LOG_WARNING(...) _Warning2(__VA_ARGS__)

#else

#define Debug(...) ((void)0)
#define Info(...) ((void)0)
#define Warning(...) _Warning(__VA_ARGS__)
#define LOG_DEBUG(...) ((void)0)
#define LOG_INFO(...) ((void)0)
#define LOG_WARNING(...) _Warning2(__VA_ARGS__)

#endif

#define Log(...) _Silent(__VA_ARGS__)
#define LOG_BARE(...) _Silent2(__VA_ARGS__)
