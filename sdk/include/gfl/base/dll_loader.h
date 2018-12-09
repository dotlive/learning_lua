#ifndef _GFL_DLL_LOADER_H_
#define _GFL_DLL_LOADER_H_

#include <string>

namespace Mage
{
    class DllLoader
    {
    public:
        DllLoader();
        ~DllLoader();

        bool Load(std::string const & dll_name);
        void Free();

        void* GetProcAddress(std::string const & proc_name);

    private:
        void* dll_handle_;
    };
}

#endif // _GFL_DLL_LOADER_H_
