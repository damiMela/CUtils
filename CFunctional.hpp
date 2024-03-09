#pragma once

namespace cutils
{
    template <typename Signature>
    class CFunction;

    template <typename R>
    class CFunction<R()>
    {
    public:
        typedef R (*FuncPtr)();

        CFunction(FuncPtr func) : m_func(func) {}

        R operator()()
        {
            return m_func();
        }

    private:
        FuncPtr m_func;
    };

    template <typename R, typename Arg>
    class CFunction<R(Arg)>
    {
    public:
        typedef R (*FuncPtr)(Arg);

        CFunction(FuncPtr func) : m_func(func) {}

        R operator()(Arg arg)
        {
            return m_func(arg);
        }

    private:
        FuncPtr m_func;
    };

}