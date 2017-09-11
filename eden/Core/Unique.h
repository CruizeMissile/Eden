#pragma once
#include <memory>

namespace edn
{
    template<class Derived>
    class Unique
    {
    public:
        using Ptr = std::unique_ptr<Derived>;

        template<typename... Args>
        static Ptr MakeNew(Args&&... params)
        {
            return std::make_unique<Derived>(std::forward<Args>(params)...);
        }
    };
}
