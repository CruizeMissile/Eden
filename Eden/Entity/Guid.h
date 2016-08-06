#pragma once
#include "Core/Types.h"

namespace edn
{
	typedef u32 Guid;

	inline Guid& inst_guid()
	{
		static Guid guid = 0;
		return guid;
	}

	inline Guid next_guid()
	{
		Guid next = ++inst_guid();
		if (next == std::numeric_limits<Guid>::max())
			throw std::out_of_range("Guid hit max size of Guid!");
		return next;
	}

	template<typename Type>
	inline Guid get_guid()
	{
		static Guid guid = next_guid();
 		return guid;
	}
}