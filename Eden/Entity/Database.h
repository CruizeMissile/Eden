#pragma once

#include "Core/Debug.h"
#include "Core/Common.h"
#include "Core/Shareable.h"
#include "Entity/Component.h"
#include "Entity/Guid.h"

#include <algorithm>
#include <memory>
#include <vector>
#include <map>

namespace edn
{
	class Database;
	class Entity;

	// -----------------------------------------------------------------------------------------------
	// Entity Definition

	class Entity : public Shareable<Entity>
	{
		friend class Database;
		friend std::_Ref_count_obj<Entity>;
	public:

		// Tuple is used to store the type information with the base pointer
		typedef std::pair<Guid, ComponentBase*> ComponentTuple;
		typedef std::vector<ComponentTuple> ComponentList;

		// Function is a struct to pass into std::lower_bound easier also here to keep only
		// in Entity and database
		struct ComponentComparitor 
		{
			bool operator() (const ComponentTuple & lhs, const ComponentTuple & rhs)
			{
				return lhs.first < rhs.first;
			}
		};

		~Entity();

		template<typename Type, typename... Args>
		Type* add(Args&&... args);

		template<typename Type>
		void remove();

		template<typename Type>
		Type* get();

		template<typename Type>
		bool has();

		u32 getComponentCount();
		Entity::ComponentList & getComponents();
	private:
		Entity() = default;
		ComponentList components;
	};

	// -----------------------------------------------------------------------------------------------
	// Database Definition
	
	class Database : public Singleton<Database>
	{
		typedef std::vector<Entity*> EntityList;

		// A way to index a type and get all of the entities that are associated with it.
		typedef std::map<Guid, EntityList> ComponentTypeIndex;

		EntityList entities;
		ComponentTypeIndex componentIndex;

	public:
		Database();
		~Database();

		// Entity creation and deletion
		Entity::Ptr create();
		void destroy(Entity * e);

		// Component creation, deletion, getting and checking
		template<typename Type, typename... Args>
		Type * addComponent(Entity * e, Args&&... args);

		template<typename Type>
		bool removeComponent(Entity * e);
		bool removeComponent(Entity * e, Guid type, ComponentBase * c);

		void cleanEntity(Entity * e);

		template<typename Type>
		Type * getComponent(Entity * e);

		template<typename Type>
		bool hasComponent(Entity * e);
		
		// Entity list information
		u32 getEntityCount();
		EntityList & getEntities();
		
		template<typename Type>
		EntityList & getEntities();
	};

	// -----------------------------------------------------------------------------------------------
	// Query


	// -----------------------------------------------------------------------------------------------
	// Database Implementation

	Database::Database()
	{

	}

	Database::~Database()
	{
		componentIndex.clear();
	}

	Entity::Ptr Database::create()
	{
		auto handle = Entity::MakeNew();
		auto position = std::lower_bound(entities.begin(), entities.end(), handle.get());
		entities.insert(position, handle.get());
		return handle;
	}

	void Database::destroy(Entity * e)
	{
		// Getting the components and removing them and also removing the entity from the type index
		auto & components = e->components;
		while(!components.empty())
		{
			// Getting the component at the end of the list
			auto c = std::next(components.end(), -1);
			auto type = c->first;

			// Have the type just have to remove the entity from the indexmap
			auto & index_list = componentIndex[type];
			auto entity_position = std::lower_bound(index_list.begin(), index_list.end(), e);
			removeComponent(e, type, c->second);
		}

		// Finding the entity in the entity list
		auto it = std::lower_bound(entities.begin(), entities.end(), e);
		entities.erase(it);
	}

	template<typename Type, typename... Args>
	Type * Database::addComponent(Entity * e, Args&&... args)
	{
		static_assert(std::is_base_of<ComponentBase, Type>::value, "Type is not base of Component");
		auto & components = e->components;

		// Have to lower bounds once to check to see where it will be inserted. Can also check to
		// see if it is already in the entity. If it is then we can assert
		auto position = std::lower_bound(components.begin(), components.end(), 
			Entity::ComponentTuple(get_guid<Type>(), nullptr), Entity::ComponentComparitor());

		ASSERT(position == components.end(), "Entity already has component type");

		auto type = get_guid<Type>();
		auto tuple = Entity::ComponentTuple(type, new Type(*e, std::forward<Args>(args)...));
		components.insert(position, tuple);

		// Update the component type index to have this entity
		auto & index_list = componentIndex[type];
		auto entity_positin = std::lower_bound(index_list.begin(), index_list.end(), e);
		index_list.insert(entity_positin, e);

		return static_cast<Type*>(tuple.second);
	}

	template<typename Type>
	bool Database::removeComponent(Entity * e)
	{
		static_assert(std::is_base_of<ComponentBase, Type>::value, "Type is not base of Component");
		auto & components = e->components;

		auto type = get_guid<Type>();
		auto tuple = Entity::ComponentTuple(type, nullptr);
		
		// Getting the component from the entity list
		auto it = std::lower_bound(components.begin(), components.end(), tuple, Entity::ComponentComparitor());
		if (it == components.end())
			return false;

		// Removing entity from component type index
		auto & index_list = componentIndex[type];
		auto entity_position = std::lower_bound(index_list.begin(), index_list.end(), e);
		index_list.erase(entity_position);

		// Deleting the component and removing it from the entity list
		delete it->second;
		components.erase(it);
		return true;
	}

	bool Database::removeComponent(Entity * e, Guid type, ComponentBase * c)
	{
		auto & components = e->components;

		auto tuple = Entity::ComponentTuple(type, c);

		auto it = std::lower_bound(components.begin(), components.end(), tuple, Entity::ComponentComparitor());
		if (it == components.end())
			return false;

		// Removing entity from component type index
		auto & index_list = componentIndex[type];
		auto entity_position = std::lower_bound(index_list.begin(), index_list.end(), e);
		index_list.erase(entity_position);

		// Deleting the component and removing from entity list.
		delete it->second;
		components.erase(it);
		return true;
	}

	void Database::cleanEntity(Entity * e)
	{
		auto components = e->components;
		while (!components.empty())
		{
			auto c = std::next(components.end(), -1);
			removeComponent(e, c->first, c->second);
		}
	}

	template<typename Type>
	Type * Database::getComponent(Entity * e)
	{
		auto & components = e->components;

		auto tuple = Entity::ComponentTuple(get_guid<Type>(), nullptr);
		auto it = std::lower_bound(components.begin(), components.end(), tuple, Entity::ComponentComparitor());

		if (it == components.end())
			return nullptr;

		return static_cast<Type*>(it->second);
	}

	template<typename Type>
	bool Database::hasComponent(Entity * e)
	{
		auto & components = e->components;
		return std::binary_search(components.begin(), components.end(), 
			Entity::ComponentTuple(get_guid<Type>(), nullptr), Entity::ComponentComparitor());
	}

	u32 Database::getEntityCount()
	{
		return static_cast<u32>(entities.size());
	}

	Database::EntityList & Database::getEntities()
	{
		return entities;
	}

	template<typename Type>
	Database::EntityList & Database::getEntities()
	{
		auto type = get_guid<type>();
		auto it = componentIndex.find(type);
		ASSERT(it != componentIndex.end(), "There are entities with that type");
		return it->second;
	}

	// -----------------------------------------------------------------------------------------------
	// Entity Implementation

	Entity::~Entity()
	{
		Database::Instance().destroy(this);
	}

	template<typename Type, typename... Args>
	Type* Entity::add(Args&&... args)
	{
		return Database::Instance().addComponent<Type>(this, std::forward<Args>(args)...);
	}

	template<typename Type>
	void Entity::remove()
	{
		Database::Instance().removeComponent<Type>(this);
	}

	template<typename Type>
	Type* Entity::get()
	{
		return Database::Instance().getComponent<Type>(this);
	}

	template<typename Type>
	bool Entity::has()
	{
		return Database::Instance().hasComponent<Type>(this);
	}

	u32 Entity::getComponentCount()
	{
		return static_cast<u32>(components.size());
	}

	Entity::ComponentList & Entity::getComponents()
	{
		return components;
	}
}