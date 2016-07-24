#pragma once

#include "Core/Types.h"
#include "Entity/ComponentBase.h"

#include <memory>
#include <vector>

namespace edn
{
	template<typename Type>
	class Component : public ComponentBase
	{
		typedef std::vector<Type*> ComponentList;
		static ComponentList Container;
	public:
		Component()
		{
			type_id = get_guid<Type>();
			Container.push_back(static_cast<Type*>(this));
		}

		~Component()
		{
			auto it = std::find(Container.begin(), Container.end(), this);
			if (it != Container.end())
				Container.erase(it);
		}

		static Guid getType()
		{
			return get_guid<Type>();
		}
	};
	
	template<typename Type>
	std::vector<Type*> Component<Type>::Container;
}