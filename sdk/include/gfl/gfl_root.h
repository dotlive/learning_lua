#ifndef _GFL_GFL_ROOT_H_
#define _GFL_GFL_ROOT_H_

#include <gfl/gfl.h>
#include <gfl/base/file_sys.h>
#include <gfl/base/dll_loader.h>
#include <gfl/utils/singleton.h>

namespace Mage
{
    class Root : public Singleton<Root>
    {
    public:
        bool StartUp();
        void ShutDown();

        FileSys* getFileSys() { return filesys_; }
        DllLoader* getDllLoader() { return dllloader_; }

    private:
        FileSys *filesys_;
        DllLoader *dllloader_;
    };
}

#endif // _GFL_GFL_ROOT_H_