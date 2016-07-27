#pragma once

#include "Core/Types.h"

template<typename TypeName, typename IdType = u32>
struct TypeID
{
	typedef TypeID<TypeName, IdType> this_type;
	typedef IdType value_type;

	explicit inline TypeID(value_type v)
		: value(v)
	{
	}

	inline bool operator==(this_type other) const
	{
		return value == other.value;
	}

	inline bool operator!=(this_type other) const
	{
		return value != other.value;
	}

	inline bool operator<(this_type other) const
	{
		return value < other.value;
	}

	inline value_type typeValue() const
	{
		return value;
	}

private:
	value_type value;
};

namespace std
{
	template<typename T, typename I>
	struct hash<TypeID<T, I>>
	{
		typedef TypeID<T, I> argument_type;
		size_t operator()(argument_type type) const
		{
			using std::hash;
			return hash<typename argument_type::value_type>()(type.typeValue());
		}
	};
}