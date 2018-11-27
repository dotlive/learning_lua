#ifndef _GFL_FILE_SYS_H_
#define _GFL_FILE_SYS_H_

#include <stddef.h>

namespace Mage
{
    class FileSys
    {
    public:
        // 文件时间
        struct file_time_t
        {
            int nYear;
            int nMonth;
            int nDay;
            int nHour;
            int nMinute;
            int nSecond;
        };

    public:
        static FileSys* Instance();

    public:
        FileSys();
        ~FileSys();

        // 文件是否存在
        bool IsFileExists(const char* name);
        // 删除文件
        bool FileDelete(const char* name);
        // 获得文件大小
        size_t FileSize(const char* name);
        // 获得文件日期
        bool FileTime(const char* name, file_time_t* file_time);
        // 打开文件
        void* FileOpen(const char* name, const char* mode);
        // 关闭文件
        bool FileClose(void* handle);
        // 读文件
        size_t FileRead(void* handle, void* pdata, size_t len);
        // 写文件
        size_t FileWrite(void* handle, const void* pdata, size_t len);
        // 格式化写文件
        size_t FilePrint(void* handle, const char* info, ...);
        // 提交写入数据
        bool FileFlush(void* handle);
        // 移动读写指针
        bool FileSeek(void* handle, long offset, int origin);
        // 获得当前读写指针位置
        size_t FileTell(void* handle);
        // 获取文件全路径
        size_t GetFullPath(const char* file_name, char* buffer, size_t size);

        // 目录是否存在
        bool IsDirExists(const char* name);
        // 创建目录
        bool CreateDir(const char* name);
        // 删除目录
        bool DeleteDir(const char* name);
        // 获得当前工作目录
        bool GetCurrentDir(char* buffer, size_t size);
        // 设置当前工作目录
        bool SetCurrentDir(const char* name);

    private:
        // 获取标准化路径
        const char* GetNormalizedPath(const char* path, char* buffer, size_t size);

        static FileSys s_instance;
    };
}

#endif // _GFL_FILE_SYS_H_
