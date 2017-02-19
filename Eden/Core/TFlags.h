#pragma once
#include <type_traits>

namespace edn
{
	template<typename Enumeration, typename Primitive = std::underlying_type_t<Enumeration>>
	class TFlags
	{
	public:
		typedef typename Enumeration Enum;
		TFlags()
			: value(Primitive())
		{
		}

		TFlags(Enumeration val)
			: value(static_cast<Primitive>(val))
		{
		}

		TFlags(Primitive val)
			: value(val)
		{
		}

		void Clear()
		{
			value = Primitive();
		}

		bool Has(TFlags mask) const
		{
			return (value & mask.value) != Primitive();
		}

		bool operator==(Enumeration val) const
		{
			return value == static_cast<Primitive>(val);
		}

		bool operator==(Primitive val) const
		{
			return value == val;
		}

		TFlags& operator=(const TFlags& other)
		{
			value = other.value;
			return *this;
		}

		TFlags& operator|=(Enumeration val)
		{
			value = value | static_cast<Primitive>(val);
			return *this;
		}

		TFlags& operator|=(Primitive val)
		{
			value = value | val;
			return *this;
		}

		TFlags& operator&=(Enumeration val)
		{
			value = value & static_cast<Primitive>(val);
			return *this;
		}

		TFlags& operator&=(Primitive val)
		{
			value = value & val;
			return *this;
		}

		TFlags operator|(Enumeration val) const
		{
			return value | static_cast<Primitive>(val);
		}

		TFlags operator|(Primitive val) const
		{
			return value | val;
		}

		TFlags operator&(Enumeration val) const
		{
			return value & static_cast<Primitive>(val);
		}

		TFlags operator&(Primitive val) const
		{
			return value & val;
		}

		operator Enumeration() const
		{
			return static_cast<Enumeration>(value);
		}

		operator Primitive() const
		{
			return value;
		}

	private:
		Primitive value;
	};
}
