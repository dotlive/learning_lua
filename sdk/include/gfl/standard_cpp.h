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

// �����
#ifdef CPLUSPLUS20_SUPPORT
#include <concepts>             // ���������
#endif // CPLUSPLUS20_SUPPORT

// ���߿�
#include <cstdlib>              // ͨ�ù��ߣ�������ơ���̬�ڴ���䡢����������������
#include <csignal>              // �źŹ���ĺ�����곣��
#include <csetjmp>              // ���浽ִ�л����ĺ꣬������ִ�л����ĺ���
#include <cstdarg>              // �䳤�����б�Ĵ���
#include <typeinfo>             // ����ʱ������Ϣ����
#include <bitset>               // std::bitset ��ģ��
#include <functional>           // �������󡢺������á��󶨲��������ð�װ
#include <utility>              // ���ֹ������
#include <ctime>                // C ���ʱ��/���ڹ���
#include <cstddef>              // ��׼������Ͷ���
#ifdef CPLUSPLUS11_SUPPORT
    #include <typeindex>            // std::type_index
    #include <type_traits>          // ����ʱ������Ϣ
    #include <chrono>               // C++ ʱ�乤��
    #include <initializer_list>     // std::initializer_list ��ģ��
    #include <tuple>                // std::tuple ��ģ��
    #ifdef CPLUSPLUS17_SUPPORT
        #include <any>                  // std::any ��
        #include <optional>             // std::optional ��ģ��
        #include <variant>              // std::variant ��ģ��
        #ifdef CPLUSPLUS20_SUPPORT
            #include <compare>              // ��·�Ƚ������֧��
            #include <version>              // �ṩ����ʵ�ֵĿ���Ϣ
        #endif // CPLUSPLUS20_SUPPORT
    #endif // CPLUSPLUS17_SUPPORT
#endif // CPLUSPLUS11_SUPPORT

// ��̬�ڴ����
#include <new>                  // �Ͳ��ڴ������
#include <memory>               // �߲��ڴ������
#ifdef CPLUSPLUS11_SUPPORT
    #include <scoped_allocator>     // Ƕ�׷�������
    #ifdef CPLUSPLUS17_SUPPORT
        #include <memory_resource>      // ��̬���������ڴ���Դ
    #endif // CPLUSPLUS17_SUPPORT
#endif // CPLUSPLUS11_SUPPORT

// ��ֵ����
#include <climits>              // �������ͼ���
#include <cfloat>               // �������ͼ���
#include <limits>               // ��ѯ�����������Եı�׼����ʽ
#ifdef CPLUSPLUS11_SUPPORT
    #include <cstdint>              // �����������������͵ļ���
    #include <cinttypes>            // ��ʽ���ꡢ intmax_t �� uintmax_t ��ѧ���߼�ת��
#endif // CPLUSPLUS11_SUPPORT

// ������
#include <exception>            // �쳣������
#include <stdexcept>            // ��׼�쳣����
#include <cassert>              // �����������Ƚϵ������Ա����
#include <cerrno>               // �������һ�δ���ŵĺ�
#ifdef CPLUSPLUS11_SUPPORT
    #include <system_error>         // ���� std::error_code������ƽ̨�Ĵ�����
    #ifdef CPLUSPLUS20_SUPPORT
        #include <contract>             // ��ԼΥ����Ϣ
    #endif // CPLUSPLUS20_SUPPORT
#endif // CPLUSPLUS11_SUPPORT

// �ַ�����
#include <cctype>               // ȷ���ַ��������������͵ĺ���
#include <cwctype>              // ȷ�����ַ��������������͵ĺ���
#include <cstring>              // ����խ�ַ���������
#include <cwchar>               // ���ֿ����ֽ��ַ���������
#include <string>               // std::basic_string ��ģ��
#ifdef CPLUSPLUS11_SUPPORT
    #include <cuchar>               // C ��� Unicode �ַ�ת������
    #ifdef CPLUSPLUS17_SUPPORT
        #include <string_view>          // std::basic_string_view ��ģ��
        #include <charconv>             // std::to_chars �� std::from_chars
    #endif // CPLUSPLUS20_SUPPORT
#endif // CPLUSPLUS11_SUPPORT

// ������
#include <vector>               // std::vector ����
#include <deque>                // std::deque ����
#include <list>                 // std::list ����
#include <set>                  // std::set �� std::multiset ��������
#include <map>                  // std::map �� std::multimap ��������
#include <stack>                // std::stack ����������
#include <queue>                // std::queue �� std::priority_queue ����������
#ifdef CPLUSPLUS11_SUPPORT
    #include <array>                // std::array ����
    #include <forward_list>         // std::forward_list ����
    #include <unordered_set>        // std::unordered_set �� std::unordered_multiset �����������
    #include <unordered_map>        // std::unordered_map �� std::unordered_multimap �����������
    #ifdef CPLUSPLUS20_SUPPORT
        #include <span>                 // std::span ��ͼ
    #endif // CPLUSPLUS20_SUPPORT
#endif // CPLUSPLUS11_SUPPORT

// �㷨��
#include <algorithm>            // �����������ϵ��㷨
#ifdef CPLUSPLUS17_SUPPORT
    #include <execution>            // �㷨���а汾��Ԥ����ִ�в���
#endif // CPLUSPLUS17_SUPPORT

// ��������
#include <iterator>             // ����������

// ��ֵ��
#include <cmath>                // ������ѧ����
#include <complex>              // ��������
#include <valarray>             // ��ʾ�Ͳ���ֵ���������
#include <numeric>              // ������ֵ����ֵ����
#ifdef CPLUSPLUS11_SUPPORT
    #include <random>               // ��������������ֲ�
    #include <ratio>                // ����ʱ����������
    #include <cfenv>                // ���㻷�����ʺ���
    #ifdef CPLUSPLUS20_SUPPORT
        #include <bit>                  // λ���ݺ��� 
    #endif // CPLUSPLUS20_SUPPORT
#endif // CPLUSPLUS11_SUPPORT

// ����/�����
#include <iosfwd>               // ��������/������е����ǰ������
#include <ios>                  // std::ios_base �ࡢstd::basic_ios ��ģ�弰���� typedef
#include <istream>              // std::basic_istream ��ģ�弰���� typedef
#include <ostream>              // std::basic_ostream �� std::basic_iostream ��ģ�弰����typedef
#include <iostream>             // ������׼������
#include <fstream>              // std::basic_fstream �� std::basic_ifstream �� std::basic_ofstream ��ģ�弰����typedef
#include <sstream>              // std::basic_stringstream �� std::basic_istringstream �� std::basic_ostringstream ��ģ�弰���� typedef
#include <strstream>            // std::strstream �� std::istrstream �� std::ostrstream
#include <iomanip>              // �������������ʽ�İ�������
#include <streambuf>            // std::basic_streambuf ��ģ��
#include <cstdio>               // C ��������������
#ifdef CPLUSPLUS20_SUPPORT
    #include <syncstream>           // std::basic_osyncstream �� std::basic_syncbuf �� typedef
#endif

// ���ػ���
#include <locale>               // ���ػ�����
#include <clocale>              // C ���ػ�����
#ifdef CPLUSPLUS11_SUPPORT
    #include <codecvt>              // Unicode ת����ʩ
#endif // (CPLUSPLUS11_SUPPORT && !CPLUSPLUS17_SUPPORT && !CPLUSPLUS20_SUPPORT)

// ������ʽ��
#ifdef CPLUSPLUS11_SUPPORT
#include <regex>                // ֧��������ʽ������ࡢ�㷨��������
#endif

// ԭ�Ӳ�����
#ifdef CPLUSPLUS11_SUPPORT
#include <atomic>               // ԭ�Ӳ�����
#endif

// �߳�֧�ֿ�
#ifdef CPLUSPLUS11_SUPPORT
#include <thread>               // std::thread �༰֧�ֺ���
#include <mutex>                // ����ԭ��
#include <future>               // �첽�����ԭ��
#include <condition_variable>   // �̵߳ȴ�����
    #ifdef CPLUSPLUS14_SUPPORT
        #include <shared_mutex>     // ����Ļ���ԭ��
    #endif // CPLUSPLUS14_SUPPORT
#endif // CPLUSPLUS11_SUPPORT

// �ļ�ϵͳ��
#ifdef CPLUSPLUS17_SUPPORT
#include <filesystem>           // std::path �༰֧�ֺ���
#endif // CPLUSPLUS17_SUPPORT

// ����

// Unsupported C headers
#ifdef COMPAT_C
#include <stdatomic.h>          // ԭ������
#include <stdnoreturn.h>        // noreturn ������
#include <threads.h>            // �߳̿�
#endif

// Empty C headers
//#include <ccomplex> // ͬ complex
//#include <ctgmath>  // cmath + complex

// Meaningless C headers (the macros these provide in C are language keywords in C++)
//#include <ciso646>
//#include <cstdalign>
//#include <cstdbool>

#endif // _GFL_STANDARD_H_
