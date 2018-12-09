#ifndef _GLF_STANDARD_C_H_
#define _GLF_STANDARD_C_H_

/*
#define C95_SUPPORT 1
#define C99_SUPPORT 0
#define C11_SUPPORT 0
*/

#include <assert.h>             // 条件编译宏，将参数与零比较
#include <ctype.h>              // 用来确定包含于字符数据中的类型的函数
#include <errno.h>              // 报告错误条件的宏
#include <float.h>              // 浮点数类型的极限
#include <limits.h>             // 基本类型的大小
#include <locale.h>             // 本地化工具
#include <math.h>               // 常用数学函数
#include <setjmp.h>             // 非局部跳转
#include <signal.h>             // 号处理
#include <stdarg.h>             // 可变参数
#include <stddef.h>             // 常用宏定义
#include <stdio.h>              // 输入/输出
#include <stdlib.h>             // 基础工具：内存管理、程序工具、字符串转换、随机数
#include <string.h>             // 字符串处理
#include <time.h>               // 时间/日期工具
#ifdef C95_SUPPORT
    #include <iso646.h>             // 符号的替代写法
    #include <wchar.h>              // 扩展多字节和宽字符工具
    #include <wctype.h>             // 用来确定包含于宽字符数据中的类型的函数
    #ifdef C99_SUPPORT
        #include <complex.h>            // 复数运算
        #include <fenv.h>               // 浮点数环境
        #include <inttypes.h>           // 整数类型的格式转换
        #include <stdbool.h>            // 布尔类型
        #include <stdint.h>             // 定宽整数类型
        #include <tgmath.h>             // 泛型数学（包装 math.h 和 complex.h 的宏）
        #ifdef C11_SUPPORT
            #include <stdalign.h>           // alignas 与 alignof 便利宏
            #include <stdatomic.h>          // 原子类型
            #include <stdnoreturn.h>        // noreturn 便利宏
            #include <threads.h>            // 线程库
            #include <uchar.h>              // UTF-16 和 UTF-32 字符工具
        #endif // C11_SUPPORT
    #endif // C99_SUPPORT
#endif // C95_SUPPORT

#endif // _GLF_STANDARD_C_H_
