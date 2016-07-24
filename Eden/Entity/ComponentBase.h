#pragma once
#include "Entity/Guid.h"

namespace edn
{
	class ComponentBase
	{
	public:
		virtual ~ComponentBase() { }
		Guid type_id;

		bool operator==(const ComponentBase& other) { return type_id == other.type_id; }
		bool operator>(const ComponentBase& other) { return type_id == other.type_id; }
		bool operator==(const Guid & other) { return type_id == other; }
		bool operator>(const Guid & other) { return type_id > other; }
		bool operator==(const Guid * other) { return type_id == *other; }
		bool operator>(const Guid * other) { return type_id > *other; }
	};
}