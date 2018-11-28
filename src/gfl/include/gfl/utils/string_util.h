#ifndef _GLF_STRING_UTIL_H_
#define _GLF_STRING_UTIL_H_

#include <vector>
#include <string>

namespace Mage
{
    class StringUtil
    {
    public:
        static void CopyString(char* buf, size_t byte_size, const char* str);

        static char* UtfToGbk(const char* utf8);
        static char* GbkToUtf(const char* gb2312);

        static size_t Split(std::vector<std::string>& result, const std::string& origin, const std::string& spliter);
        static bool IsNullOrEmpty(const char* value);

        static int ToInt(const char* value);
        static bool ToBool(const char* value);

        static void FromInt(int value, std::string& result);
        static void FromBool(bool value, std::string& result);
    };
}

#endif // _GLF_STRING_UTIL_H_
