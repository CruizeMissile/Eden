#pragma once
#include "cpplinq/cpplinq.hpp"

namespace edn
{
	namespace Query
	{
		struct BaseRange {};

		template<typename PreparedQuery>
		struct FromRange : BaseRange
		{
			typedef FromRange<PreparedQuery> this_type;
			typedef PreparedQuery iterator_type;

			iterator_type current;
			iterator_type upcomming;
			iterator_type end;
		};
	}
}