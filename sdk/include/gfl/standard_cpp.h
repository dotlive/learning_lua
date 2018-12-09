#ifndef _GFL_STANDARD_CPP_H_
#define _GFL_STANDARD_CPP_H_

/*
#define CPLUSPLUS98_SUPPORT 1   // C++98
#define CPLUSPLUS03_SUPPORT 1   // C++03
#define CPLUSPLUS11_SUPPORT 1   // C++11, C++0x
#define CPLUSPLUS14_SUPPORT 0   // C++14, C++1y
#define CPLUSPLUS17_SUPPORT 0   // C++17, C++1z
#define CPLUSPLUS20_SUPPORT 0   // C++20
*/

// 概念库
#ifdef CPLUSPLUS20_SUPPORT
#include <concepts>             // 基础库概念
#endif // CPLUSPLUS20_SUPPORT

// 工具库
#include <cstdlib>              // 通用工具：程序控制、动态内存分配、随机数、排序与查找
#include <csignal>              // 信号管理的函数与宏常量
#include <csetjmp>              // 保存到执行环境的宏，及跳到执行环境的函数
#include <cstdarg>              // 变长参数列表的处理
#include <typeinfo>             // 运行时类型信息工具
#include <bitset>               // std::bitset 类模板
#include <functional>           // 函数对象、函数调用、绑定操作、引用包装
#include <utility>              // 多种工具组件
#include <ctime>                // C 风格时间/日期工具
#include <cstddef>              // 标准宏和类型定义
#ifdef CPLUSPLUS11_SUPPORT
    #include <typeindex>            // std::type_index
    #include <type_traits>          // 编译时类型信息
    #include <chrono>               // C++ 时间工具
    #include <initializer_list>     // std::initializer_list 类模板
    #include <tuple>                // std::tuple 类模板
    #ifdef CPLUSPLUS17_SUPPORT
        #include <any>                  // std::any 类
        #include <optional>             // std::optional 类模板
        #include <variant>              // std::variant 类模板
        #ifdef CPLUSPLUS20_SUPPORT
            #include <compare>              // 三路比较运算符支持
            #include <version>              // 提供依赖实现的库信息
        #endif // CPLUSPLUS20_SUPPORT
    #endif // CPLUSPLUS17_SUPPORT
#endif // CPLUSPLUS11_SUPPORT

// 动态内存管理
#include <new>                  // 低层内存管理工具
#include <memory>               // 高层内存管理工具
#ifdef CPLUSPLUS11_SUPPORT
    #include <scoped_allocator>     // 嵌套分配器类
    #ifdef CPLUSPLUS17_SUPPORT
        #include <memory_resource>      // 多态分配器及内存资源
    #endif // CPLUSPLUS17_SUPPORT
#endif // CPLUSPLUS11_SUPPORT

// 数值极限
#include <climits>              // 整数类型极限
#include <cfloat>               // 浮点类型极限
#include <limits>               // 查询算术类型属性的标准化方式
#ifdef CPLUSPLUS11_SUPPORT
    #include <cstdint>              // 定长整数及其他类型的极限
    #include <cinttypes>            // 格式化宏、 intmax_t 及 uintmax_t 数学工具及转换
#endif // CPLUSPLUS11_SUPPORT

// 错误处理
#include <exception>            // 异常处理工具
#include <stdexcept>            // 标准异常对象
#include <cassert>              // 将其参数与零比较的条件性编译宏
#include <cerrno>               // 含有最近一次错误号的宏
#ifdef CPLUSPLUS11_SUPPORT
    #include <system_error>         // 定义 std::error_code，依赖平台的错误码
    #ifdef CPLUSPLUS20_SUPPORT
        #include <contract>             // 契约违规信息
    #endif // CPLUSPLUS20_SUPPORT
#endif // CPLUSPLUS11_SUPPORT

// 字符串库
#include <cctype>               // 确定字符数据中所含类型的函数
#include <cwctype>              // 确定宽字符数据中所含类型的函数
#include <cstring>              // 多种窄字符串处理函数
#include <cwchar>               // 多种宽及多字节字符串处理函数
#include <string>               // std::basic_string 类模板
#ifdef CPLUSPLUS11_SUPPORT
    #include <cuchar>               // C 风格 Unicode 字符转换函数
    #ifdef CPLUSPLUS17_SUPPORT
        #include <string_view>          // std::basic_string_view 类模板
        #include <charconv>             // std::to_chars 与 std::from_chars
    #endif // CPLUSPLUS20_SUPPORT
#endif // CPLUSPLUS11_SUPPORT

// 容器库
#include <vector>               // std::vector 容器
#include <deque>                // std::deque 容器
#include <list>                 // std::list 容器
#include <set>                  // std::set 及 std::multiset 关联容器
#include <map>                  // std::map 及 std::multimap 关联容器
#include <stack>                // std::stack 容器适配器
#include <queue>                // std::queue 及 std::priority_queue 容器适配器
#ifdef CPLUSPLUS11_SUPPORT
    #include <array>                // std::array 容器
    #include <forward_list>         // std::forward_list 容器
    #include <unordered_set>        // std::unordered_set 及 std::unordered_multiset 无序关联容器
    #include <unordered_map>        // std::unordered_map 及 std::unordered_multimap 无序关联容器
    #ifdef CPLUSPLUS20_SUPPORT
        #include <span>                 // std::span 视图
    #endif // CPLUSPLUS20_SUPPORT
#endif // CPLUSPLUS11_SUPPORT

// 算法库
#include <algorithm>            // 操作于容器上的算法
#ifdef CPLUSPLUS17_SUPPORT
    #include <execution>            // 算法并行版本的预定义执行策略
#endif // CPLUSPLUS17_SUPPORT

// 迭代器库
#include <iterator>             // 容器迭代器

// 数值库
#include <cmath>                // 常用数学函数
#include <complex>              // 复数类型
#include <valarray>             // 表示和操作值的数组的类
#include <numeric>              // 容器中值的数值运算
#ifdef CPLUSPLUS11_SUPPORT
    #include <random>               // 随机数生成器及分布
    #include <ratio>                // 编译时有理数算术
    #include <cfenv>                // 浮点环境访问函数
    #ifdef CPLUSPLUS20_SUPPORT
        #include <bit>                  // 位操纵函数 
    #endif // CPLUSPLUS20_SUPPORT
#endif // CPLUSPLUS11_SUPPORT

// 输入/输出库
#include <iosfwd>               // 所有输入/输出库中的类的前置声明
#include <ios>                  // std::ios_base 类、std::basic_ios 类模板及数个 typedef
#include <istream>              // std::basic_istream 类模板及数个 typedef
#include <ostream>              // std::basic_ostream 、 std::basic_iostream 类模板及数个typedef
#include <iostream>             // 数个标准流对象
#include <fstream>              // std::basic_fstream 、 std::basic_ifstream 、 std::basic_ofstream 类模板及数个typedef
#include <sstream>              // std::basic_stringstream 、 std::basic_istringstream 、 std::basic_ostringstream 类模板及数个 typedef
#include <strstream>            // std::strstream 、 std::istrstream 、 std::ostrstream
#include <iomanip>              // 控制输入输出格式的帮助函数
#include <streambuf>            // std::basic_streambuf 类模板
#include <cstdio>               // C 风格输入输出函数
#ifdef CPLUSPLUS20_SUPPORT
    #include <syncstream>           // std::basic_osyncstream 、 std::basic_syncbuf 及 typedef
#endif

// 本地化库
#include <locale>               // 本地化工具
#include <clocale>              // C 本地化工具
#ifdef CPLUSPLUS11_SUPPORT
    #include <codecvt>              // Unicode 转换设施
#endif // (CPLUSPLUS11_SUPPORT && !CPLUSPLUS17_SUPPORT && !CPLUSPLUS20_SUPPORT)

// 正则表达式库
#ifdef CPLUSPLUS11_SUPPORT
#include <regex>                // 支持正则表达式处理的类、算法及迭代器
#endif

// 原子操作库
#ifdef CPLUSPLUS11_SUPPORT
#include <atomic>               // 原子操作库
#endif

// 线程支持库
#ifdef CPLUSPLUS11_SUPPORT
#include <thread>               // std::thread 类及支持函数
#include <mutex>                // 互斥原语
#include <future>               // 异步计算的原语
#include <condition_variable>   // 线程等待条件
    #ifdef CPLUSPLUS14_SUPPORT
        #include <shared_mutex>     // 共享的互斥原语
    #endif // CPLUSPLUS14_SUPPORT
#endif // CPLUSPLUS11_SUPPORT

// 文件系统库
#ifdef CPLUSPLUS17_SUPPORT
#include <filesystem>           // std::path 类及支持函数
#endif // CPLUSPLUS17_SUPPORT

// 其它

// Unsupported C headers
#ifdef COMPAT_C
#include <stdatomic.h>          // 原子类型
#include <stdnoreturn.h>        // noreturn 便利宏
#include <threads.h>            // 线程库
#endif

// Empty C headers
//#include <ccomplex> // 同 complex
//#include <ctgmath>  // cmath + complex

// Meaningless C headers (the macros these provide in C are language keywords in C++)
//#include <ciso646>
//#include <cstdalign>
//#include <cstdbool>

#endif // _GFL_STANDARD_H_
