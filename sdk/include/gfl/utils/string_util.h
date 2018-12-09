#ifndef _GLF_STRING_UTIL_H_
#define _GLF_STRING_UTIL_H_

#include <string>

namespace Mage
{
    class StringUtil
    {
    public:
        static void CopyString(char* buf, size_t byte_size, const char* str);
    };
}

#endif // _GLF_STRING_UTIL_H_
