#pragma once

#include "Core/Shareable.h"
#include "Entity/Database.h"

#include <vector>

namespace edn
{
	class ComponentBase;

	class Entity : public Shareable<Entity>
	{
		friend class Database;
		std::vector<ComponentBase*> components;
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
	};

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

}