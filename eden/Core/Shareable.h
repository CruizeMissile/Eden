#pragma once
#include <memory>

namespace edn
{
    template<class Derived>
    class Shareable : private std::enable_shared_from_this<Derived>
    {
        // Hide this function from user code.
        using std::enable_shared_from_this<Derived>::shared_from_this;

    protected:
        using ShareableAlloc = std::_Ref_count_obj<Derived>;

    public:
        using Ptr = std::shared_ptr<Derived>;
        using Ref = std::weak_ptr<Derived>;

        Ptr GetPtr()
        {
            return this->shared_from_this();
        }

        Ref GetRef()
        {
            return this->shared_from_this();
        }

        template<typename... Args>
        static Ptr MakeNew(Args&&... params)
        {
            return std::make_shared<Derived>(std::forward<Args>(params)...);
        }
    };
}
