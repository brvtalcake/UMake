/*
 * MIT License
 * 
 * Copyright (c) 2023 Axel PASCON
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef UMAKE_H
#define UMAKE_H

#if defined(__cplusplus)
extern "C" {
#endif

#if defined(__x86_64__) || defined(__amd64__) || defined(_M_AMD64)
    #if defined(UMAKE_ON_X86_64)
        #warning "UMAKE_ON_X86_64 is already defined, undefining it"
        #undef UMAKE_ON_X86_64
    #endif
    #define UMAKE_ON_X86_64 1
#endif
// Since x86 can also be detected by the above macros if they use the
// ILP32 data model, we need to perform both checks
// (see https://sourceforge.net/p/predef/wiki/Architectures/, the note below AMD64 section)
#if defined(__i386__) || defined(_M_IX86) || defined(_X86_)
    #if defined(UMAKE_ON_X86_64)
        #undef UMAKE_ON_X86_64
    #endif
    #if defined(UMAKE_ON_X86)
        #warning "UMAKE_ON_X86 is already defined, undefining it"
        #undef UMAKE_ON_X86
    #endif
    #define UMAKE_ON_X86 1
#else
    #if !defined(UMAKE_ON_X86_64)
        #error "Unsupported architecture"
    #endif
#endif

#if defined(_WIN32) || defined(_WIN64)
    #if defined(UMAKE_ON_WINDOWS)
        #warning "UMAKE_ON_WINDOWS is already defined, undefining it"
        #undef UMAKE_ON_WINDOWS
    #endif
    #define UMAKE_ON_WINDOWS 1
    #include <windows.h>
#elif (defined(__linux__) || defined(__unix__)) && !(defined(__APPLE__) || defined(__ANDROID__))
    #if defined(UMAKE_ON_LINUX)
        #warning "UMAKE_ON_LINUX is already defined, undefining it"
        #undef UMAKE_ON_LINUX
    #endif
    #define UMAKE_ON_LINUX 1
    #define _GNU_SOURCE 1
    #if !defined(_FORTIFY_SOURCE)
        #define _FORTIFY_SOURCE 2
    #endif
    #include <sys/types.h>
    #include <sys/stat.h>
    #include <dirent.h>
    #include <unistd.h>
#elif defined(__APPLE__)
    #if defined(UMAKE_ON_APPLE)
        #warning "UMAKE_ON_APPLE is already defined, undefining it"
        #undef UMAKE_ON_APPLE
    #endif
    #define UMAKE_ON_APPLE 1
    #define _GNU_SOURCE 1
    #if !defined(_FORTIFY_SOURCE)
        #define _FORTIFY_SOURCE 2
    #endif
    #include <sys/types.h>
    #include <sys/stat.h>
    #include <dirent.h>
    #include <unistd.h>
#else
    #error "Unsupported platform"
#endif

#if defined(C_STD)
    #undef C_STD
#endif
#if defined(CXX_STD)
    #undef CXX_STD
#endif
#if defined(__GNUC__)
    #if defined(UMAKE_WITH_GCC)
        #warning "UMAKE_WITH_GCC is already defined, undefining it"
        #undef UMAKE_WITH_GCC
    #endif
    #define UMAKE_WITH_GCC 1
#elif defined(_MSC_VER)
    #if defined(UMAKE_WITH_MSVC)
        #warning "UMAKE_WITH_MSVC is already defined, undefining it"
        #undef UMAKE_WITH_MSVC
    #endif
    #define UMAKE_WITH_MSVC 1
    #if defined(__cplusplus)
        #if _MSVC_LANG <= 199711L
            #define CXX_STD 1998
        #elif _MSVC_LANG <= 201103L
            #define CXX_STD 2011
        #elif _MSVC_LANG <= 201402L
            #define CXX_STD 2014
        #elif _MSVC_LANG <= 201703L
            #define CXX_STD 2017
        #elif _MSVC_LANG <= 202002L
            #define CXX_STD 2020
        #elif _MSVC_LANG > 202002L
            #define CXX_STD 2023
        #else
            #error "Unsupported C++ standard"
        #endif
    #endif
#elif defined(__clang__)
    #if defined(UMAKE_WITH_CLANG)
        #warning "UMAKE_WITH_CLANG is already defined, undefining it"
        #undef UMAKE_WITH_CLANG
    #endif
    #define UMAKE_WITH_CLANG 1
#else
    #error "Unsupported compiler"
#endif

#if !defined(CXX_STD)
    #if defined(__cplusplus)
        #if __cplusplus <= 199711L
            #define CXX_STD 1998
        #elif __cplusplus <= 201103L
            #define CXX_STD 2011
        #elif __cplusplus <= 201402L
            #define CXX_STD 2014
        #elif __cplusplus <= 201703L
            #define CXX_STD 2017
        #elif __cplusplus <= 202002L
            #define CXX_STD 2020
        #elif __cplusplus > 202002L
            #define CXX_STD 2023
        #else
            #error "Unsupported C++ standard"
        #endif
    #endif
#endif

#if !defined(C_STD)
    #if defined(__STDC_VERSION__)
        #if __STDC_VERSION__ <= 198901L
            #define C_STD 1989
        #elif __STDC_VERSION__ <= 199409L
            #define C_STD 1994
        #elif __STDC_VERSION__ <= 199901L
            #define C_STD 1999
        #elif __STDC_VERSION__ <= 201112L
            #define C_STD 2011
        #elif __STDC_VERSION__ <= 201710L
            #define C_STD 2017
        #elif __STDC_VERSION__ > 201710L
            #define C_STD 2023
        #else
            #error "Unsupported C standard"
        #endif
    #endif
#endif

#if defined(UMAKE_PRAGMA)
    #undef UMAKE_PRAGMA
#endif
#if defined(UMAKE_ERROR)
    #undef UMAKE_ERROR
#endif
#if defined(UMAKE_DIAG_IGNORE)
    #undef UMAKE_DIAG_IGNORE
#endif
#if defined(UMAKE_DIAG_POP)
    #undef UMAKE_DIAG_POP
#endif
#if defined(UMAKE_FUNC_WARNING)
    #undef UMAKE_FUNC_WARNING
#endif
#if defined(UMAKE_FUNC_NON_NULL)
    #undef UMAKE_FUNC_NON_NULL
#endif
#if defined(UMAKE_FUNC_MALLOC)
    #undef UMAKE_FUNC_MALLOC
#endif
#if defined(UMAKE_WITH_GCC)
    #define UMAKE_PRAGMA(...) _Pragma(UMAKE_STR(__VA_ARGS__))
    #define UMAKE_ERROR(msg) UMAKE_PRAGMA(GCC error msg)
    #define UMAKE_DIAG_IGNORE(...) UMAKE_PRAGMA(GCC diagnostic ignored __VA_ARGS__)
    #define UMAKE_DIAG_POP(...) UMAKE_PRAGMA(GCC diagnostic pop)
    #define UMAKE_FUNC_WARNING(msg) __attribute__((warning(msg)))
    #define UMAKE_FUNC_NON_NULL(...) __attribute__((nonnull(__VA_ARGS__)))
    #define UMAKE_FUNC_MALLOC __attribute__((malloc))
#elif defined(UMAKE_WITH_MSVC)
    #define UMAKE_PRAGMA(...) __pragma(__VA_ARGS__)
    #define UMAKE_ERROR(msg) UMAKE_PRAGMA(message(__FILE__ "(" UMAKE_STR(__LINE__) "): error: " msg))
    #define UMAKE_DIAG_IGNORE(...) UMAKE_PRAGMA(warning(disable: __VA_ARGS__))
    #define UMAKE_DIAG_POP(...) UMAKE_PRAGMA(warning(pop))
    #define UMAKE_FUNC_WARNING(msg) __pragma(message(__FILE__ "(" UMAKE_STR(__LINE__) "): warning: " msg))
    #define UMAKE_FUNC_NON_NULL(...)
    #define UMAKE_FUNC_MALLOC
#elif defined(UMAKE_WITH_CLANG)
    #define UMAKE_PRAGMA(...) _Pragma(UMAKE_STR(__VA_ARGS__))
    #define UMAKE_ERROR(msg) UMAKE_PRAGMA(clang error msg)
    #define UMAKE_DIAG_IGNORE(...) UMAKE_PRAGMA(clang diagnostic ignored __VA_ARGS__)
    #define UMAKE_DIAG_POP(...) UMAKE_PRAGMA(clang diagnostic pop)
    #define UMAKE_FUNC_WARNING(msg) __attribute__((warning(msg)))
    #define UMAKE_FUNC_NON_NULL(...) __attribute__((nonnull(__VA_ARGS__)))
    #define UMAKE_FUNC_MALLOC __attribute__((malloc))
#else
    #define UMAKE_PRAGMA(...) _Pragma(UMAKE_STR(__VA_ARGS__))
    #define UMAKE_ERROR(msg)
    #define UMAKE_DIAG_IGNORE(...)
    #define UMAKE_DIAG_POP(...)
    #define UMAKE_FUNC_WARNING(msg)
    #define UMAKE_FUNC_NON_NULL(...)
    #define UMAKE_FUNC_MALLOC
#endif

#if defined(UMAKE_STR)
    #undef UMAKE_STR
#endif
#define UMAKE_STR(...) UMAKE_STR_REDIRECT(__VA_ARGS__)

#if defined(UMAKE_STR_REDIRECT)
    #undef UMAKE_STR_REDIRECT
#endif
#define UMAKE_STR_REDIRECT(...) UMAKE_CONCAT(UMAKE_STR_, UMAKE_ARGC(__VA_ARGS__))(__VA_ARGS__)

#if defined(UMAKE_STR_1)
    #undef UMAKE_STR_1
#endif
#define UMAKE_STR_1(x) UMAKE_STR_1_REDIRECT(x)

#if defined(UMAKE_STR_1_REDIRECT)
    #undef UMAKE_STR_1_REDIRECT
#endif
#define UMAKE_STR_1_REDIRECT(x) #x

#if defined(UMAKE_STR_2)
    #undef UMAKE_STR_2
#endif
#define UMAKE_STR_2(x, y) UMAKE_STR_2_REDIRECT(x, y)

#if defined(UMAKE_STR_2_REDIRECT)
    #undef UMAKE_STR_2_REDIRECT
#endif
#define UMAKE_STR_2_REDIRECT(x, y) #x #y

#if defined(UMAKE_STR_3)
    #undef UMAKE_STR_3
#endif
#define UMAKE_STR_3(x, y, z) UMAKE_STR_3_REDIRECT(x, y, z)

#if defined(UMAKE_STR_3_REDIRECT)
    #undef UMAKE_STR_3_REDIRECT
#endif
#define UMAKE_STR_3_REDIRECT(x, y, z) #x #y #z

#if defined(UMAKE_STR_4)
    #undef UMAKE_STR_4
#endif
#define UMAKE_STR_4(x, y, z, w) UMAKE_STR_4_REDIRECT(x, y, z, w)

#if defined(UMAKE_STR_4_REDIRECT)
    #undef UMAKE_STR_4_REDIRECT
#endif
#define UMAKE_STR_4_REDIRECT(x, y, z, w) #x #y #z #w

#if defined(UMAKE_STR_5)
    #undef UMAKE_STR_5
#endif
#define UMAKE_STR_5(x, y, z, w, v) UMAKE_STR_5_REDIRECT(x, y, z, w, v)

#if defined(UMAKE_STR_5_REDIRECT)
    #undef UMAKE_STR_5_REDIRECT
#endif
#define UMAKE_STR_5_REDIRECT(x, y, z, w, v) #x #y #z #w #v

#if defined(UMAKE_STR_6)
    #undef UMAKE_STR_6
#endif
#define UMAKE_STR_6(x, y, z, w, v, u) UMAKE_STR_6_REDIRECT(x, y, z, w, v, u)

#if defined(UMAKE_STR_6_REDIRECT)
    #undef UMAKE_STR_6_REDIRECT
#endif
#define UMAKE_STR_6_REDIRECT(x, y, z, w, v, u) #x #y #z #w #v #u

#if defined(UMAKE_STR_7)
    #undef UMAKE_STR_7
#endif
#define UMAKE_STR_7(x, y, z, w, v, u, t) UMAKE_STR_7_REDIRECT(x, y, z, w, v, u, t)

#if defined(UMAKE_STR_7_REDIRECT)
    #undef UMAKE_STR_7_REDIRECT
#endif
#define UMAKE_STR_7_REDIRECT(x, y, z, w, v, u, t) #x #y #z #w #v #u #t

#if defined(UMAKE_STR_8)
    #undef UMAKE_STR_8
#endif
#define UMAKE_STR_8(x, y, z, w, v, u, t, s) UMAKE_STR_8_REDIRECT(x, y, z, w, v, u, t, s)

#if defined(UMAKE_STR_8_REDIRECT)
    #undef UMAKE_STR_8_REDIRECT
#endif
#define UMAKE_STR_8_REDIRECT(x, y, z, w, v, u, t, s) #x #y #z #w #v #u #t #s

#if defined(UMAKE_STR_9)
    #undef UMAKE_STR_9
#endif
#define UMAKE_STR_9(x, y, z, w, v, u, t, s, r) UMAKE_STR_9_REDIRECT(x, y, z, w, v, u, t, s, r)

#if defined(UMAKE_STR_9_REDIRECT)
    #undef UMAKE_STR_9_REDIRECT
#endif
#define UMAKE_STR_9_REDIRECT(x, y, z, w, v, u, t, s, r) #x #y #z #w #v #u #t #s #r

#if defined(UMAKE_STR_10)
    #undef UMAKE_STR_10
#endif
#define UMAKE_STR_10(x, y, z, w, v, u, t, s, r, q) UMAKE_STR_10_REDIRECT(x, y, z, w, v, u, t, s, r, q)

#if defined(UMAKE_STR_10_REDIRECT)
    #undef UMAKE_STR_10_REDIRECT
#endif
#define UMAKE_STR_10_REDIRECT(x, y, z, w, v, u, t, s, r, q) #x #y #z #w #v #u #t #s #r #q

#include <assert.h>

#if !defined(UMAKE_ASSERT)
    #define UMAKE_ASSERT assert
#endif

// TODO: Modify this horrible macro
#if (C_STD < 2011 && !defined(static_assert)) || (CXX_STD < 2011 && !defined(static_assert))
    #undef static_assert
    #define static_assert(cond, msg)                                                                    \
        char UMAKE_CONCAT(static_assertion_failed_at_line_, __LINE__)                                   \
        [(cond) ? sizeof(("static assertion failed in file" __FILE__  ": " msg)) / sizeof(char) : -1]   \
        = "static assertion failed in file" __FILE__  ": " msg;
#endif

#if defined(UMAKE_ARGC)
    #undef UMAKE_ARGC
#endif
#define UMAKE_ARGC(...)                                                          \
    UMAKE_ARGC_REDIRECT(  0, ##__VA_ARGS__, 64, 63, 62, 61, 60, 59, 58, 57, 56,  \
                          55, 54, 53, 52, 51, 50, 49, 48, 47, 46, 45, 44, 43,    \
                          42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30,    \
                          29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17,    \
                          16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4,          \
                          3, 2, 1, 0)

#if defined(UMAKE_ARGC_REDIRECT)
    #undef UMAKE_ARGC_REDIRECT
#endif
#define UMAKE_ARGC_REDIRECT(_64, _63, _62, _61, _60, _59, _58, _57, _56, _55, \
                            _54, _53, _52, _51, _50, _49, _48, _47, _46, _45, \
                            _44, _43, _42, _41, _40, _39, _38, _37, _36, _35, \
                            _34, _33, _32, _31, _30, _29, _28, _27, _26, _25, \
                            _24, _23, _22, _21, _20, _19, _18, _17, _16, _15, \
                            _14, _13, _12, _11, _10, _9, _8, _7, _6, _5, _4,  \
                            _3, _2, _1, _0, N, ...) N

#if defined(UMAKE_IDENTITY)
    #undef UMAKE_IDENTITY
#endif
#define UMAKE_IDENTITY(...) UMAKE_IDENTITY_REDIRECT(__VA_ARGS__)

#if defined(UMAKE_IDENTITY_REDIRECT)
    #undef UMAKE_IDENTITY_REDIRECT
#endif
#define UMAKE_IDENTITY_REDIRECT(...) __VA_ARGS__

#if defined(UMAKE_EAT)
    #undef UMAKE_EAT
#endif
#define UMAKE_EAT(...)

#if defined(UMAKE_IF)
    #undef UMAKE_IF
#endif
#define UMAKE_IF(cond, a, b) UMAKE_IF_REDIRECT(cond, a, b)

#if defined(UMAKE_IF_REDIRECT)
    #undef UMAKE_IF_REDIRECT
#endif
#define UMAKE_IF_REDIRECT(cond, a, b) UMAKE_CONCAT_2(UMAKE_IF_, cond)(a, b)

#if defined(UMAKE_IF_0)
    #undef UMAKE_IF_0
#endif
#define UMAKE_IF_0(a, b) b

#if defined(UMAKE_IF_1)
    #undef UMAKE_IF_1
#endif
#define UMAKE_IF_1(a, b) a

#if defined(UMAKE_VA_IF)
    #undef UMAKE_VA_IF
#endif
#define UMAKE_VA_IF(cond) UMAKE_VA_IF_REDIRECT(cond)

#if defined(UMAKE_VA_IF_REDIRECT)
    #undef UMAKE_VA_IF_REDIRECT
#endif
#define UMAKE_VA_IF_REDIRECT(cond) UMAKE_CONCAT_2(UMAKE_VA_IF_, cond)

#if defined(UMAKE_VA_IF_0)
    #undef UMAKE_VA_IF_0
#endif
#define UMAKE_VA_IF_0(...) UMAKE_IDENTITY

#if defined(UMAKE_VA_IF_1)
    #undef UMAKE_VA_IF_1
#endif
#define UMAKE_VA_IF_1(...) __VA_ARGS__ UMAKE_EAT

#if defined(UMAKE_AST_AUTO)
    #undef UMAKE_AST_AUTO
#endif
#define UMAKE_AST_AUTO(this, op, should_be, ...)                                                         \
    UMAKE_ASSERT(                                                                                        \
        (this op should_be) &&                                                                           \
        ("there should be " UMAKE_STR(should_be) " " UMAKE_STR(op) " " UMAKE_STR(this) "\t" __VA_ARGS__) \
    )

#if defined(UMAKE_AST)
    #undef UMAKE_AST
#endif
#define UMAKE_AST(this, op, should_be, ...) \
    UMAKE_ASSERT(                           \
        (this op should_be) &&              \
        (__VA_ARGS__)                       \
    )
static_assert(UMAKE_ARGC() == 0, "UMAKE_ARGC() should be 0");
static_assert(UMAKE_ARGC(a) == 1, "UMAKE_ARGC(a) should be 1");
static_assert(UMAKE_ARGC(a, b) == 2, "UMAKE_ARGC(a, b) should be 2");
static_assert(UMAKE_ARGC(a, b, c, d, e, f ,g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z) == 26, "UMAKE_ARGC(<all letters>) should be 26");

#if defined(UMAKE_UNIMPLEMENTED)
    #undef UMAKE_UNIMPLEMENTED
#endif
#if defined(__INTELLISENSE__)
    #define UMAKE_UNIMPLEMENTED(func_name) UMAKE_ASSERT(0)
#else
    #define UMAKE_UNIMPLEMENTED(func_name) UMAKE_ASSERT(0 && (func_name " is not implemented"))
#endif

#if defined(UMAKE_CONCAT_2_)
    #undef UMAKE_CONCAT_2_
#endif
#define UMAKE_CONCAT_2_(x, y) UMAKE_CONCAT_2__(x, y)

#if defined(UMAKE_CONCAT_2__)
    #undef UMAKE_CONCAT_2__
#endif
#define UMAKE_CONCAT_2__(x, y) x##y

#if defined(UMAKE_CONCAT)
    #undef UMAKE_CONCAT
#endif
#define UMAKE_CONCAT(...) UMAKE_CONCAT_REDIRECT(__VA_ARGS__)

#if defined(UMAKE_CONCAT_REDIRECT)
    #undef UMAKE_CONCAT_REDIRECT
#endif
#define UMAKE_CONCAT_REDIRECT(...) UMAKE_CONCAT_2_(UMAKE_CONCAT_, UMAKE_ARGC(__VA_ARGS__))(__VA_ARGS__)

#if defined(UMAKE_CONCAT_1)
    #undef UMAKE_CONCAT_1
#endif
#define UMAKE_CONCAT_1(x) UMAKE_IDENTITY(x)

#if defined(UMAKE_CONCAT_2)
    #undef UMAKE_CONCAT_2
#endif
#define UMAKE_CONCAT_2(x, y) UMAKE_CONCAT_2_REDIRECT(x, y)

#if defined(UMAKE_CONCAT_2_REDIRECT)
    #undef UMAKE_CONCAT_2_REDIRECT
#endif
#define UMAKE_CONCAT_2_REDIRECT(x, y) x##y

#if defined(UMAKE_CONCAT_3)
    #undef UMAKE_CONCAT_3
#endif
#define UMAKE_CONCAT_3(x, y, z) UMAKE_CONCAT_3_REDIRECT(x, y, z)

#if defined(UMAKE_CONCAT_3_REDIRECT)
    #undef UMAKE_CONCAT_3_REDIRECT
#endif
#define UMAKE_CONCAT_3_REDIRECT(x, y, z) UMAKE_CONCAT_2(x, UMAKE_CONCAT_2(y, z))

#if defined(UMAKE_CONCAT_4)
    #undef UMAKE_CONCAT_4
#endif
#define UMAKE_CONCAT_4(x, y, z, w) UMAKE_CONCAT_4_REDIRECT(x, y, z, w)

#if defined(UMAKE_CONCAT_4_REDIRECT)
    #undef UMAKE_CONCAT_4_REDIRECT
#endif
#define UMAKE_CONCAT_4_REDIRECT(x, y, z, w) UMAKE_CONCAT_2(x, UMAKE_CONCAT_3(y, z, w))

#if defined(UMAKE_CONCAT_5)
    #undef UMAKE_CONCAT_5
#endif
#define UMAKE_CONCAT_5(x, y, z, w, v) UMAKE_CONCAT_5_REDIRECT(x, y, z, w, v)

#if defined(UMAKE_CONCAT_5_REDIRECT)
    #undef UMAKE_CONCAT_5_REDIRECT
#endif
#define UMAKE_CONCAT_5_REDIRECT(x, y, z, w, v) UMAKE_CONCAT_2(x, UMAKE_CONCAT_4(y, z, w, v))

#if defined(UMAKE_CONCAT_6)
    #undef UMAKE_CONCAT_6
#endif
#define UMAKE_CONCAT_6(x, y, z, w, v, u) UMAKE_CONCAT_6_REDIRECT(x, y, z, w, v, u)

#if defined(UMAKE_CONCAT_6_REDIRECT)
    #undef UMAKE_CONCAT_6_REDIRECT
#endif
#define UMAKE_CONCAT_6_REDIRECT(x, y, z, w, v, u) UMAKE_CONCAT_2(x, UMAKE_CONCAT_5(y, z, w, v, u))

#if defined(UMAKE_CONCAT_7)
    #undef UMAKE_CONCAT_7
#endif
#define UMAKE_CONCAT_7(x, y, z, w, v, u, t) UMAKE_CONCAT_7_REDIRECT(x, y, z, w, v, u, t)

#if defined(UMAKE_CONCAT_7_REDIRECT)
    #undef UMAKE_CONCAT_7_REDIRECT
#endif
#define UMAKE_CONCAT_7_REDIRECT(x, y, z, w, v, u, t) UMAKE_CONCAT_2(x, UMAKE_CONCAT_6(y, z, w, v, u, t))

#if defined(UMAKE_CONCAT_8)
    #undef UMAKE_CONCAT_8
#endif
#define UMAKE_CONCAT_8(x, y, z, w, v, u, t, s) UMAKE_CONCAT_8_REDIRECT(x, y, z, w, v, u, t, s)

#if defined(UMAKE_CONCAT_8_REDIRECT)
    #undef UMAKE_CONCAT_8_REDIRECT
#endif
#define UMAKE_CONCAT_8_REDIRECT(x, y, z, w, v, u, t, s) UMAKE_CONCAT_2(x, UMAKE_CONCAT_7(y, z, w, v, u, t, s))

#if defined(UMAKE_CONCAT_9)
    #undef UMAKE_CONCAT_9
#endif
#define UMAKE_CONCAT_9(x, y, z, w, v, u, t, s, r) UMAKE_CONCAT_9_REDIRECT(x, y, z, w, v, u, t, s, r)

#if defined(UMAKE_CONCAT_9_REDIRECT)
    #undef UMAKE_CONCAT_9_REDIRECT
#endif
#define UMAKE_CONCAT_9_REDIRECT(x, y, z, w, v, u, t, s, r) UMAKE_CONCAT_2(x, UMAKE_CONCAT_8(y, z, w, v, u, t, s, r))

#if defined(UMAKE_CONCAT_10)
    #undef UMAKE_CONCAT_10
#endif
#define UMAKE_CONCAT_10(x, y, z, w, v, u, t, s, r, q) UMAKE_CONCAT_10_REDIRECT(x, y, z, w, v, u, t, s, r, q)

#if defined(UMAKE_CONCAT_10_REDIRECT)
    #undef UMAKE_CONCAT_10_REDIRECT
#endif
#define UMAKE_CONCAT_10_REDIRECT(x, y, z, w, v, u, t, s, r, q) UMAKE_CONCAT_2(x, UMAKE_CONCAT_9(y, z, w, v, u, t, s, r, q))

#if defined(UMAKE_EQ)
    #undef UMAKE_EQ
#endif
#define UMAKE_EQ(x, y) UMAKE_EQ_REDIRECT(x, y)

#if defined(UMAKE_EQ_REDIRECT)
    #undef UMAKE_EQ_REDIRECT
#endif
#define UMAKE_EQ_REDIRECT(x, y) UMAKE_CONCAT(UMAKE_EQ_, x, _, y)

// Contains a whole bunch of generated macros
#include "umake_generated.h"

#include <stddef.h>
#include <stdlib.h>
#if !defined(__cplusplus) && C_STD >= 1999 && C_STD < 2023
    #include <stdbool.h>
#endif
#include <string.h>
#include <threads.h>

#if defined(UMAKE_CSTR_NULL)
    #undef UMAKE_CSTR_NULL
#endif
#define UMAKE_CSTR_NULL ((UM_CStr){NULL, 0})
#if !defined(UMAKE_MALLOC)
    #define UMAKE_MALLOC malloc
#endif
#if !defined(UMAKE_FREE)
    #define UMAKE_FREE free
#endif
#if !defined(UMAKE_REALLOC)
    #define UMAKE_REALLOC realloc
#endif
#if !defined(UMAKE_CALLOC)
    #define UMAKE_CALLOC calloc
#endif

/* * * * * * * *
 * UMAKE TYPES *
 * * * * * * * */

/**
 * @brief Basic "string" type.
 */
typedef struct UMake_C_String 
{
    char *data;
    size_t length;
} UM_CStr;

/**
 * @brief Basic "file" type.
 */
typedef struct UMake_File
{
    UM_CStr path;
} UM_File;

/* * * * * * * * * *
 * UMAKE FUNCTIONS *
 * * * * * * * * * */

UMAKE_FUNC_NON_NULL(1)
static UM_CStr umake_cstr_new(const char *str);
static void umake_cstr_free(UM_CStr *cstr);
UMAKE_FUNC_NON_NULL(3)
static UM_File* umake_get_files(const UM_CStr *paths, size_t path_count, size_t* file_count);
UMAKE_FUNC_NON_NULL(1)
static char* umake_get_superdir(const char* path);

UMAKE_FUNC_NON_NULL(1)
static UM_CStr umake_cstr_new(const char *str)
{
#if !defined(UMAKE_WITH_MSVC)
    UMAKE_DIAG_IGNORE("-Wnonnull-compare")
#endif
    if (!str) return UMAKE_CSTR_NULL;
#if !defined(UMAKE_WITH_MSVC)
    UMAKE_DIAG_POP()
#endif
    UM_CStr result;
    result.length = strlen(str);
    result.data = UMAKE_MALLOC(result.length + 1);
    if (!result.data) return UMAKE_CSTR_NULL;
    memcpy(result.data, str, result.length);
    result.data[result.length] = '\0';
    return result;
}

static void umake_cstr_free(UM_CStr *cstr)
{
    if (!cstr) return;
    UMAKE_FREE(cstr->data);
    cstr->data = NULL;
    cstr->length = 0;
}

UMAKE_FUNC_NON_NULL(3)
static UM_File* umake_get_files(const UM_CStr *paths, size_t path_count, size_t* file_count)
{
#if !defined(UMAKE_WITH_MSVC)
    UMAKE_DIAG_IGNORE("-Wnonnull-compare")
#endif
    if (!paths || !file_count || !path_count) return NULL;
#if !defined(UMAKE_WITH_MSVC)
    UMAKE_DIAG_POP()
#endif
    *file_count = 0;
    size_t glob_count[path_count];
    size_t* glob_positions[path_count];
    memset(glob_count, 0, sizeof(glob_count));
    memset(glob_positions, 0, sizeof(glob_positions));

    for (size_t i = 0; i < path_count; ++i)
    {
        size_t curr_ch_pos = 0;
        char* curr_ch = paths[i].data;
        while (curr_ch_pos <= paths[i].length && (curr_ch = strchr(curr_ch, '*')))
        {
            ++glob_count[i];
            curr_ch_pos = (size_t) (curr_ch - paths[i].data);
            glob_positions[i] = UMAKE_REALLOC(glob_positions[i], sizeof(size_t) * glob_count[i]);
            if (!glob_positions[i]) return NULL;
            glob_positions[i][glob_count[i] - 1] = curr_ch_pos;
            ++curr_ch;
        }
    }

    UMAKE_UNIMPLEMENTED(__func__);
}

UMAKE_FUNC_NON_NULL(1)
static char* umake_get_superdir(const char* path)
{
#if !defined(UMAKE_WITH_MSVC)
    UMAKE_DIAG_IGNORE("-Wnonnull-compare")
#endif
    if (!path) return NULL;
#if !defined(UMAKE_WITH_MSVC)
    UMAKE_DIAG_POP()
#endif
    char* where_to_cut = strrchr(path, '/');
    if (!where_to_cut) where_to_cut = strrchr(path, '\\');
    if (!where_to_cut) 
    {
        // Get full path, and then cut
#if defined(UMAKE_ON_WINDOWS)
        UMAKE_UNIMPLEMENTED(__func__);
        return NULL;
#else
        UMAKE_UNIMPLEMENTED(__func__);
        return NULL;
#endif
    }
    UMAKE_UNIMPLEMENTED(__func__);
}

#if defined(__cplusplus)
}
#endif

#endif

