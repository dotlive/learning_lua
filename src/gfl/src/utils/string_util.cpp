#include <gfl/gfl.h>
#include <gfl/utils/string_util.h>

#ifdef MAGE_PLATFORM_WINDOWS
#include <windows.h>
#endif

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

    char* StringUtil::UtfToGbk(const char* utf8)
    {
        int len = MultiByteToWideChar(CP_UTF8, 0, utf8, -1, NULL, 0);
        wchar_t* wstr = new wchar_t[len+1];
        memset(wstr, 0, len+1);
        MultiByteToWideChar(CP_UTF8, 0, utf8, -1, wstr, len);
        len = WideCharToMultiByte(CP_ACP, 0, wstr, -1, NULL, 0, NULL, NULL);
        char* str = new char[len+1];
        memset(str, 0, len+1);
        WideCharToMultiByte(CP_ACP, 0, wstr, -1, str, len, NULL, NULL);
        if(wstr) delete[] wstr;
        return str;
    }

    char* StringUtil::GbkToUtf(const char* gb2312)
    {
        int len = MultiByteToWideChar(CP_ACP, 0, gb2312, -1, NULL, 0);
        wchar_t* wstr = new wchar_t[len+1];
        memset(wstr, 0, len+1);
        MultiByteToWideChar(CP_ACP, 0, gb2312, -1, wstr, len);
        len = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);
        char* str = new char[len+1];
        memset(str, 0, len+1);
        WideCharToMultiByte(CP_UTF8, 0, wstr, -1, str, len, NULL, NULL);
        if(wstr) delete[] wstr;
        return str;
    }

    size_t StringUtil::Split(std::vector<std::string>& result, const std::string& origin, const std::string& spliter)
    {
        if (origin == "")
        {
            return 0;
        }

        std::string strs(origin);
        strs += spliter;

        size_t pos;
        size_t size = strs.size();

        for (size_t i = 0; i < size; ++i)
        {
            pos = strs.find(spliter, i);
            if (pos < size)
            {
                std::string s = strs.substr(i, pos - i);
                result.push_back(s);
                i = pos + spliter.length() - 1;
            }

        }

        return result.size();
    }

    bool StringUtil::IsNullOrEmpty(const char* value)
    {
        return (value == NULL || value[0] == '\0');
    }

    int StringUtil::ToInt(const char* value)
    {
        return ::atoi(value);
    }

    bool StringUtil::ToBool(const char* value)
    {
        if (0 == strcmp(value, "true"))
            return true;
        else
            return false;
    }

    void StringUtil::FromInt(int value, std::string& result)
    {
        char buff[128] = { 0 };
        result += _itoa(value, buff, 10);
    }

    void StringUtil::FromBool(bool value, std::string& result)
    {
        result += value ? "true" : "false";
    }
}
