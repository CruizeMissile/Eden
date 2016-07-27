#pragma once
#include "Core/Debug.h"
#include "Core/TypeInfo.h"
#include "Entity/Component.h"
#include "Entity/Database.h"

#include <unordered_map>

namespace edn
{
	s32 hash_string(String str)
	{
		s32 hash = 0;
		s32 offset = 'a' - 1;
		for (String::const_iterator it = str.begin(); it != str.end(); ++it)
		{
			hash = hash << 1 | (*it - offset);
		}
		return hash;
	}

	class SystemBase
	{
	public:
		virtual ~SystemBase() { }
		Guid type_id;
	};

	template<typename Type>
	class System : public SystemBase
	{
		static std::unordered_map<u32, SystemBase*> RegisterSystem;
	public:
		System()
		{
			u32 hash = hash_string(EDN_TYPENAME(Type));
			ASSERT(RegisterSystem.find(hash) == RegisterSystem.end(), "System already exists");

			RegisterSystem[hash] = this;
		}
		
		~System()
		{
			u32 hash = hash_string(toString());
			auto it = RegisterSystem.find(hash);
			ASSERT(it != RegisterSystem.end(), "System does not exists");
			RegisterSystem.erase(it);
		}

		virtual void process() = 0;
		virtual String toString() = 0;
	};
	template<typename Type>
	std::unordered_map<u32, SystemBase*> System<Type>::RegisterSystem;

	// -----------------------------------------------------------------------------------------------
	// System Manager

	class SystemManager : public Singleton<SystemManager>
	{
	public:
		SystemManager() { }
		~SystemManager() { Unregister(); }

		template<typename Type>
		void Register()
		{
			static_assert(std::is_base_of<SystemBase, Type>::value), "Type is not of system");
			auto system = new Type();
			u32 hash = hash_string(system.toString());
			ASSERT(it != systems.find(hash) == systems.end());
			systems[hash] = system;
		}

		template<typename Type, typename... Args>
		void Register()
		{
			auto ptr[] = 
			{
				Register<Type>(),
				Register<Args>()...
			};
		}

		void Unregister()
		{
			systems.clear();
		}

		std::unordered_map<u32, SystemBase*> systems;
	};
}