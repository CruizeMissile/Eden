#pragma once

#include "Core/Assert.h"
#include "Core/Common.h"
#include "Core/Shareable.h"
#include "Entity/Component.h"
#include "Entity/Guid.h"

#include <algorithm>
#include <memory>
#include <vector>

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
		typedef std::vector<ComponentBase*> ComponentList;
		ComponentList components;
		Entity() = default;
	public:
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
		std::vector<ComponentBase*> & getComponents();
	};

	// -----------------------------------------------------------------------------------------------
	// Database Definition
	
	class Database : public Singleton<Database>
	{
		typedef std::vector<Entity*> EntityList;
		EntityList entities;

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
		bool removeComponent(Entity * e, ComponentBase * c);

		void cleanEntity(Entity * e);

		template<typename Type>
		Type * getComponent(Entity * e);

		template<typename Type>
		bool hasComponent(Entity * e);
		
		// Entity list information
		u32 getEntityCount();
	};

	// -----------------------------------------------------------------------------------------------
	//

	bool component_lower_bounds(const ComponentBase * c, const Guid & id)
	{
		return c->type_id < id;
	}

	bool component_find(const Guid & id, const ComponentBase * c)
	{
		return c->type_id == id;
	}

	// -----------------------------------------------------------------------------------------------
	// Database Implementation

	Database::Database()
	{

	}

	Database::~Database()
	{

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
		// Finding the entity
		auto it = std::lower_bound(entities.begin(), entities.end(), e);

		// Getting the components and removing them
		auto & components = e->components;
		for (auto c : components)
			delete c;

		entities.erase(it);
	}

	template<typename Type, typename... Args>
	Type * Database::addComponent(Entity * e, Args&&... args)
	{
		static_assert(std::is_base_of<ComponentBase, Type>::value, "Type is not base of Component");
		ASSERT(!hasComponent<Type>(e), "Entity already has Component Type");

		auto component = new Type(std::forward<Args>(args)...);

		auto & components = e->components;
		auto position = std::lower_bound(components.begin(), components.end(), component);
		components.insert(position, component);
		return component;
	}

	template<typename Type>
	bool Database::removeComponent(Entity * e)
	{
		static_assert(std::is_base_of<ComponentBase, Type>::value, "Type is not base of Component");
		auto & components = e->components;
		
		Guid id = get_guid<Type>();
		auto it = std::find_if(components.begin(), components.end(),
			[&id](ComponentBase* cb)->bool {return cb->type_id == id; });

		if (it == components.end())
			return false;
		
		delete *it;
		components.erase(it);
		return true;
	}

	bool Database::removeComponent(Entity * e, ComponentBase * c)
	{
		auto & components = e->components;
		auto it = std::find(components.begin(), components.end(), c);

		if (it == components.end())
			return false;

		components.erase(it);
		delete *it;
		return true;
	}

	void Database::cleanEntity(Entity * e)
	{
		while (e->components.size() > 0)
			removeComponent(e, e->components[0]);
	}

	template<typename Type>
	Type * Database::getComponent(Entity * e)
	{
		auto & components = e->components;
		auto position = std::lower_bound(components.begin(), components.end(), get_guid<Type>(), component_lower_bounds);

		if (position == components.end())
			return nullptr;

		return static_cast<Type*>(*position);
	}

	template<typename Type>
	bool Database::hasComponent(Entity * e)
	{
		auto & components = e->components;
		auto position = std::lower_bound(components.begin(), components.end(), get_guid<Type>(), component_lower_bounds);

		return position != components.end();
	}

	u32 Database::getEntityCount()
	{
		return static_cast<u32>(entities.size());
	}

	// -----------------------------------------------------------------------------------------------
	// Database Implementation

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

	std::vector<ComponentBase*> & Entity::getComponents()
	{
		return components;
	}
}