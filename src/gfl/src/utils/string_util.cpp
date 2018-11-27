#include "gfl/utils/string_util.h"


namespace Mage
{
    void StringUtil::CopyString(char* buf, size_t byte_size, const char* str)
    {
        size_t SIZE1 = strlen(str) + 1;
        if (SIZE1 <= byte_size)
        {
            memcpy(buf, str, SIZE1);
        }
        else
        {
            memcpy(buf, str, byte_size - 1);
            buf[byte_size - 1] = 0;
        }
    }
}
