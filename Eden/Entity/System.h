#pragma once
#include "Core/Debug.h"
#include "Core/TypeInfo.h"
#include "Entity/Component.h"
#include "Entity/Database.h"

#include <unordered_map>

namespace edn
{

	class SystemBase
	{
	public:
		virtual ~SystemBase() { }
	};

	template<typename Type>
	class System : public SystemBase
	{
	public:
		System() { }
		~System() { }

		virtual void process() = 0;
		virtual String toString() = 0;
	};

	// -----------------------------------------------------------------------------------------------
	// System Manager

	class SystemManager : public SingletonOld<SystemManager>
	{
		typedef std::pair<Guid, SystemBase*> SystemTuple;
		typedef std::vector<SystemTuple> SystemList;
		SystemList systems;

		struct SystemComparitor
		{
			bool operator() (const SystemTuple& lhs, const SystemTuple& rhs)
			{
				return lhs.first < rhs.first;
			}
		};

	public:
		SystemManager() { }
		~SystemManager() { }

		template<typename Type>
		Type * create();

		template<typename Type>
		void destroy(SystemBase * s);

		void destroy(SystemBase * s, Guid type);
	};

	template<typename Type>
	Type * SystemManager::create()
	{
		static_assert(std::is_base_of<SystemBase, Type>::value, "Type is not base of System");

		auto type = get_guid<Type>();
		auto it = std::lower_bound(systems.begin(), systems.end(), SystemTuple(type, nullptr), SystemComparitor());

		ASSERT(it == systems.end());

		auto system = new Type();
		systems.insert(it, SystemTuple(type, system);
		return system;
	}

	template<typename Type>
	void SystemManager::destroy(SystemBase * s)
	{
		destroy(s, get_guid<Type>());

	}

	void SystemManager::destroy(SystemBase * s, Guid type)
	{
		auto it = std::lower_bound(systems.begin(), systems.end(), SystemTuple(type, s), SystemComparitor());

		ASSERT(it != systems.end(), "System was not found");

		delete it->second;
		systems.erase(it);
	}
}
