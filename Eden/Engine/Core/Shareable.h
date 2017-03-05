#pragma once
#include <memory>

namespace edn
{
	template<class Derived>
	class Shareable : private std::enable_shared_from_this<Derived>
	{
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
			return std::make_shared<private_enabler>(std::forward<Args>(params)...);
		}

	private:
		struct private_enabler;
	};

	// http://stackoverflow.com/a/20961251
	template<class Derived>
	struct Shareable<Derived>::private_enabler : public Shareable<Derived>
	{
		private_enabler() : Shareable<Derived>() {}
	};
}
