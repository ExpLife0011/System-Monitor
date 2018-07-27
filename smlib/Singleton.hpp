#ifndef _SINGLETON_HPP_
#define _SINGLETON_HPP_

namespace SMLib
{
    template <typename _Ty>
    class Singleton
    {
    public:
        static
        _Ty&
        Instance()
        {
            static _Ty _Instance;
            return _Instance;
        }

        template<typename ... Args>
        static
        Initialize(
            _In_ Args&& ...
        )
        {
            Instance().Initialize(static_cast<Args&&>(Args)...);
        }

    private:
        Singleton() { }
    };
}

#endif // _SINGLETON_HPP_
