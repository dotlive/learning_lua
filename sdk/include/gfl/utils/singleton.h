#ifndef _GLF_UTILS_SINGLETON_H__
#define _GLF_UTILS_SINGLETON_H__

namespace Mage
{
    template <typename T>
    class Singleton
    {
    public:
        Singleton()
        {
            instance_ = static_cast<T*>(this);
        }

        ~Singleton()
        {
            instance_ = 0;
        }

        static T& Instance()
        {
            return (*instance_);
        }

        static T* InstancePtr()
        {
            return instance_;
        }

    private:
        Singleton(const Singleton<T> &);
        Singleton& operator=(const Singleton<T> &);

        static T* instance_;
    };
}

#endif // _GLF_UTILS_SINGLETON_H__
