#include <gfl/gfl.h>
#include <gfl/base/file_sys.h>
#include <gfl/utils/string_util.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#ifdef MAGE_PLATFORM_WINDOWS
#include <windows.h>
#else
#include <unistd.h>
#include <dirent.h>
#include <dlfcn.h>
#include <time.h>
#include <ctype.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <utime.h>
#endif

#ifdef MAGE_PLATFORM_WINDOWS
#define PATH_SEPARATOR '\\'
#else
#define PATH_SEPARATOR '/'
#endif


namespace Mage
{
    FileSys FileSys::s_instance;

    FileSys* FileSys::Instance()
    {
        return &s_instance;
    }

    FileSys::FileSys()
    {
    }

    FileSys::~FileSys()
    {
    }

    bool FileSys::IsFileExists(const char* name)
    {
#ifdef MAGE_PLATFORM_WINDOWS
        DWORD res = GetFileAttributesA(name);
        if (res == DWORD(-1))
        {
            return false;
        }
        return (res & FILE_ATTRIBUTE_DIRECTORY) == 0;
#else
        char sname[512];
        GetNormalizedPath(name, sname, sizeof(sname));

        struct stat st;
        if (stat(sname, &st) == -1)
        {
            return false;
        }

        return (st.st_mode & S_IFMT) == S_IFREG;
#endif
    }

    bool FileSys::FileDelete(const char* name)
    {
#ifdef MAGE_PLATFORM_WINDOWS
        return DeleteFileA(name) == TRUE;
#else
        char sname[512];
        GetNormalizedPath(name, sname, sizeof(sname));
        return unlink(sname) == 0;
#endif
    }

    size_t FileSys::FileSize(const char* name)
    {
#ifdef MAGE_PLATFORM_WINDOWS
        HANDLE fp = CreateFileA(name, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);
        if (INVALID_HANDLE_VALUE == fp)
        {
            return false;
        }

        DWORD size_high;
        DWORD size_low = GetFileSize(fp, &size_high);

        CloseHandle(fp);

        return size_low;
#else
        char sname[512];
        GetNormalizedPath(name, sname, sizeof(sname));

        struct stat st;
        if (stat(sname, &st) == -1)
        {
            return false;
        }

        return st.st_size & 0xFFFFFFFF;
#endif
    }

    bool FileSys::FileTime(const char* name, file_time_t* file_time)
    {
#ifdef MAGE_PLATFORM_WINDOWS
        HANDLE fp = CreateFileA(name, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);
        if (INVALID_HANDLE_VALUE == fp)
        {
            return false;
        }

        FILETIME ft;
        if (!GetFileTime(fp, NULL, NULL, &ft))
        {
            CloseHandle(fp);
            return false;
        }

        CloseHandle(fp);

        // 使用国际标准时间
        SYSTEMTIME st;
        FileTimeToSystemTime(&ft, &st);

        file_time->nYear = st.wYear;
        file_time->nMonth = st.wMonth;
        file_time->nDay = st.wDay;
        file_time->nHour = st.wHour;
        file_time->nMinute = st.wMinute;
        file_time->nSecond = st.wSecond;

        return true;
#else
        char sname[512];
        GetNormalizedPath(name, sname, sizeof(sname));

        struct stat st;
        if (stat(sname, &st) == -1)
        {
            return false;
        }

        // 使用国际标准时间
        tm* pt = gmtime((long*)&st.st_mtime);
        file_time->nYear = pt->tm_year + 1900;
        file_time->nMonth = pt->tm_mon + 1;
        file_time->nDay = pt->tm_mday;
        file_time->nHour = pt->tm_hour;
        file_time->nMinute = pt->tm_min;
        file_time->nSecond = pt->tm_sec;

        return true;
#endif
    }

    void* FileSys::FileOpen(const char* name, const char* mode)
    {
        return fopen(name, mode);
    }

    bool FileSys::FileClose(void* handle)
    {
        return fclose((FILE*)handle) == 0;
    }

    size_t FileSys::FileRead(void* handle, void* pdata, size_t len)
    {
        return fread(pdata, sizeof(char), len, (FILE*)handle);
    }

    size_t FileSys::FileWrite(void* handle, const void* pdata, size_t len)
    {
        return fwrite(pdata, sizeof(char), len, (FILE*)handle);
    }

    size_t FileSys::FilePrint(void* handle, const char* info, ...)
    {
        va_list vlist;

        va_start(vlist, info);
        size_t res = vfprintf((FILE*)handle, info, vlist);
        va_end(vlist);

        return res;
    }

    bool FileSys::FileFlush(void* handle)
    {
        return fflush((FILE*)handle) == 0;
    }

    bool FileSys::FileSeek(void* handle, long offset, int origin)
    {
        return fseek((FILE*)handle, offset, origin) == 0;
    }

    size_t FileSys::FileTell(void* handle)
    {
        return ftell((FILE*)handle);
    }

    size_t FileSys::GetFullPath(const char * file_name, char * buffer, size_t size)
    {
        memset(buffer, 0, size);

#ifdef MAGE_PLATFORM_WINDOWS
        DWORD res = GetFullPathNameA(file_name, (DWORD)size, buffer, NULL);
        if (0 == res)
        {
            buffer[0] = 0;
            return 0;
        }

        if (size_t(res) >= size)
        {
            buffer[0] = 0;
            return 0;
        }

        return (int)res;
#else
        const char* first = file_name;

        // 消除前面的空格
        while ((*first == ' ') || (*first == '\t'))
        {
            ++first;
        }

        // 是否已经包含完整的路径
        if (*first == '/')
        {
            size_t file_name_len = strlen(first);
            if (file_name_len >= size)
            {
                return 0;
            }

            memcpy(buffer, first, file_name_len + 1);
        }
        else
        {
            // 获取当前目录
            char cur_dir[512] = { 0 };
            if (getcwd(cur_dir, sizeof(cur_dir) - 1) == NULL)
            {
                return 0;
            }

            // 解析相对路径
            const char* p = first;
            while (*p)
            {
                if (*p == '.')
                {
                    // (.\)当前目录
                    if ((p[1] == '\\') || (p[1] == '/'))
                    {
                        p += 2;
                        continue;
                    }

                    if (p[1] != '.')
                    {
                        break;
                    }

                    if ((p[2] != '\\') && (p[2] != '/'))
                    {
                        break;
                    }

                    // (..\)取上一级目录
                    char* prev = strrchr(cur_dir, '/');
                    if (prev)
                    {
                        *(prev + 1) = 0;
                    }

                    p += 3;
                }
                else
                {
                    break;
                }
            }

            size_t cur_dir_len = strlen(cur_dir);
            if (cur_dir[cur_dir_len - 1] != '/')
            {
                cur_dir[cur_dir_len] = '/';
            }

            if (strlen(cur_dir) + strlen(p) >= size)
            {
                return 0;
            }

            strcpy(buffer, cur_dir);
            strcat(buffer, p);
        }

        return strlen(buffer);
#endif
    }

    bool FileSys::IsDirExists(const char* name)
    {
#ifdef MAGE_PLATFORM_WINDOWS
        DWORD res = GetFileAttributesA(name);
        if (res == DWORD(-1))
        {
            return false;
        }
        return (res & FILE_ATTRIBUTE_DIRECTORY) != 0;
#else
        char sname[512];
        GetNormalizedPath(name, sname, sizeof(sname));

        struct stat st;
        if (stat(sname, &st) == -1)
        {
            return false;
        }

        return (st.st_mode & S_IFMT) == S_IFDIR;
#endif
    }

    bool FileSys::CreateDir(const char* name)
    {
        if (IsDirExists(name))
        {
            return false;
        }

#ifdef MAGE_PLATFORM_WINDOWS
        if (CreateDirectoryA(name, NULL) == TRUE)
        {
            return true;
        }
#else
        char sname[512];
        GetNormalizedPath(name, sname, sizeof(sname));
        if (mkdir(sname, 0700) == 0)
        {
            return true;
        }

        bool succeed = true;

        char buffer[256];
        size_t size = strlen(name) + 1;
        StringUtil::CopyString(buffer, size, name);

        for (size_t i = 0; i < size; ++i)
        {
            if ((buffer[i] == '\\') || (buffer[i] == '/'))
            {
                buffer[i] = 0;

                if (!IsDirExists(buffer))
                {
                    if (!CreateDir(buffer))
                    {
                        succeed = false;
                    }
                }

                buffer[i] = PATH_SEPARATOR;
            }
        }

        return succeed;
#endif
    }

    bool FileSys::DeleteDir(const char* name)
    {
#ifdef MAGE_PLATFORM_WINDOWS
        return RemoveDirectoryA(name) == TRUE;
#else
        char sname[512];
        GetNormalizedPath(name, sname, sizeof(sname));
        return rmdir(sname) == 0;
#endif
    }

    bool FileSys::GetCurrentDir(char * buffer, size_t size)
    {
#ifdef MAGE_PLATFORM_WINDOWS
        DWORD res = GetCurrentDirectoryA((DWORD)size, buffer);
        if (0 == res)
        {
            buffer[0] = 0;
            return false;
        }

        if (size_t(res) >= size)
        {
            buffer[0] = 0;
            return false;
        }

        return true;
#else
        char* res = getcwd(buffer, size);
        if (NULL == res)
        {
            buffer[0] = 0;
            return false;
        }

        return true;
#endif
    }

    bool FileSys::SetCurrentDir(const char * name)
    {
#ifdef MAGE_PLATFORM_WINDOWS
        return SetCurrentDirectoryA(name) == TRUE;
#else
        return chdir(name) == 0;
#endif
    }

    const char* FileSys::GetNormalizedPath(const char* path, char* buffer, size_t size)
    {
        // 标注前一个符号是不是目标分隔符，是则设成true
        bool slash = false;
        const char* src = path;
        char* dst = buffer;
        char* dst_end = buffer + size - 1;

        while (*src)
        {
            if (dst >= dst_end)
            {
                break;
            }

            if ((*src == '/') || (*src == '\\'))
            {
                if (slash)
                {
                    // 消除重复的斜杠
                    ++src;
                    continue;
                }
                else
                {
                    slash = true;
                }

                *dst = PATH_SEPARATOR;
            }
            else
            {
#ifndef MAGE_PLATFORM_WINDOWS
                *dst = *src;
#endif
                slash = false;
            }

            ++dst;
            ++src;
        }

        *dst = 0;

        return buffer;
    }
}
