#pragma once

#include "Core/Debug.h"
#include "Core/Shareable.h"
#include "Core/Singleton.h"
#include "Entity/Component.h"
#include "Entity/Guid.h"
#include "Entity/Query.h"

#include <algorithm>
#include <memory>
#include <vector>
#include <map>

namespace edn
{
    class Database;
    class Entity;

    namespace Query
    {
        template<class LeftQuery>
        struct BaseQuery;
        template<class LeftQuery, class RightQuery>
        struct IntersectionQuery;
        template<class LeftQuery, class RightQuery>
        struct DifferenceQuery;
        template<class LeftQuery, class RightQuery>
        struct UnionQuery;
        template<class LeftQuery, class RightQuery>
        struct ExclusiveQuery;
        struct AllQuery;
        struct TypeQuery;
        struct TagQuery;

        template<class Query>
        struct Simplify
        {
            typedef Query Result;

            static Result toSimple(const Query& query)
            {
                return query;
            }
        };

        template<typename Query>
        inline typename Simplify<Query>::Result toSimple(const Query& q)
        {
            return Simplify<Query>::toSimple(q);
        }
    }

    // -----------------------------------------------------------------------------------------------
    // Entity Definition

    class Entity : public Shareable<Entity>
    {
        friend class Database;
        friend ShareableAlloc;
    public:

        // Tuple is used to store the type information with the base pointer
        typedef std::pair<Guid, ComponentBase*> ComponentTuple;
        typedef std::vector<ComponentTuple> ComponentList;
        typedef std::vector<Guid> TagList;

        // Function is a struct to pass into std::lower_bound easier also here to keep only
        // in Entity and database
        struct ComponentComparitor
        {
            bool operator() (const ComponentTuple& lhs, const ComponentTuple& rhs)
            {
                return lhs.first < rhs.first;
            }
        };

        ~Entity();

        template<typename Type, typename... Args>
        Type& add(Args&&... args);

        template<typename Type, typename... Args>
        Type& replace(Args&&... args);

        template<typename Type>
        void remove();

        template<typename Type>
        Type& get();

        template<typename Type>
        Type* tryGet();

        template<typename Type>
        bool has();

        template<typename Type>
        void addTag(ComponentTag<Type> t);

        template<typename Type>
        void removeTag(ComponentTag<Type> t);

        template<typename Type>
        bool hasTag(ComponentTag<Type> t);

        u32 getComponentCount();
        Entity::ComponentList& getComponents();
    private:
        Entity() = default;
        Entity(const Entity&) = delete;
        Entity(Entity&&) = default;
        Entity& operator=(const Entity&) = delete;
        Entity& operator=(Entity&&) = delete;

        ComponentList components;
        TagList tags;
    };

    // -----------------------------------------------------------------------------------------------
    // Database Definition

    static class Database : public Singleton<class Database>
    {
    public:
        typedef std::vector<Entity*> EntityList;
        typedef std::vector<std::reference_wrapper<Entity>> EntityRefList;

        // A way to index a type and get all of the entities that are associated with it.
        typedef std::map<Guid, EntityList> TypeIndex;

    private:
        EntityList entities;
        TypeIndex componentIndex;
        TypeIndex tagIndex;
        static EntityList emptyList;

    public:
        struct entity_iterator : std::iterator<std::forward_iterator_tag, Entity*>
        {
            typedef EntityList::const_iterator iterator;
            typedef EntityList::const_iterator const_iterator;
            inline entity_iterator(iterator iter);
            inline entity_iterator(const entity_iterator& other);

            inline entity_iterator& operator++();
            inline entity_iterator operator++(int);
            inline bool operator==(const entity_iterator& other) const;
            inline bool operator!=(const entity_iterator& other) const;
            inline Entity* operator*()const;
            iterator inner;
        };

        template<typename TIterator>
        struct entity_ref_iterator
        {
            typedef entity_ref_iterator<TIterator> this_type;
            typedef std::forward_iterator_tag iterator_category;
            typedef Entity& value_type;
            typedef std::ptrdiff_t difference_type;
            typedef Entity* pointer;
            typedef Entity& reference;

            inline entity_ref_iterator(TIterator iterator);
            inline entity_ref_iterator(const this_type&) = default;
            inline entity_ref_iterator(this_type&&) = default;

            inline this_type& operator=(const this_type&) = default;
            inline this_type& operator=(this_type&&) = default;

            inline this_type& operator++();
            inline this_type operator++(int);
            inline bool operator==(const this_type& other) const;
            inline bool operator!=(const this_type& other) const;
            inline Entity& operator*() const;

            TIterator inner;
        };

        class BaseRange {};

        class RangeAll : public BaseRange
        {
        public:
            typedef entity_iterator const_iterator;

            inline RangeAll();

            inline const_iterator begin() const;
            inline const_iterator end() const;
        private:
            RangeAll& operator=(const RangeAll&) = delete;
        };

        class RangeType : public BaseRange
        {
        public:
            typedef entity_iterator const_iterator;

            inline RangeType(Guid type);

            inline const_iterator begin() const;
            inline const_iterator end() const;
        private:
            RangeType& operator=(const RangeType&) = delete;
            TypeIndex::const_iterator typeIterator;
            Guid type;
        };

        class RangeTag : public BaseRange
        {
        public:
            typedef entity_iterator const_iterator;

            inline RangeTag(Guid type);

            inline const_iterator begin() const;
            inline const_iterator end() const;
        private:
            RangeTag& operator=(const RangeTag&) = delete;
            TypeIndex::const_iterator typeIterator;
            Guid type;
        };

        template<typename TRange>
        class RefRange
        {
        public:
            typedef entity_ref_iterator<typename TRange::const_iterator> const_iterator;
            typedef RefRange<TRange> this_type;

            inline RefRange(TRange range);
            inline RefRange(const this_type&) = delete;
            inline RefRange(this_type&&) = default;

            inline this_type& operator=(const this_type&) = delete;
            inline this_type& operator=(this_type&&) = default;

            inline const_iterator begin() const;
            inline const_iterator end() const;

            TRange range;
        };

    public:
        Database();
        ~Database();

        // Entity creation and deletion
        Entity::Ptr create();
        void destroy(Entity& e);

        // Component creation, deletion, getting and checking
        template<typename Type, typename... Args>
        Type& addComponent(Entity& e, Args&&... args);

        template<typename Type, typename... Args>
        Type& replaceComponent(Entity& e, Args&&... args);

        template<typename Type>
        bool removeComponent(Entity& e);
        bool removeComponent(Entity& e, Guid type, ComponentBase* c);

        void cleanEntity(Entity& e);

        template<typename Type>
        Type& getComponent(Entity& e);

        template<typename Type>
        Type* tryGetComponent(Entity& e);

        template<typename Type>
        bool hasComponent(Entity& e);

        // Tag addition removal getting and checking
        template<typename Type>
        void addTag(Entity& e, ComponentTag<Type> t);

        template<typename Type>
        void removeTag(Entity& e, ComponentTag<Type> t);
        void removeTag(Entity& e, Guid type);

        template<typename Type>
        bool hasTag(Entity& e, ComponentTag<Type> t);

        template<typename Filter>
        RefRange<typename Query::Simplify<Filter>::Result::RangeType> where(const Filter& fullQuery) const;

        // Entity list information
        inline u32 getEntityCount();
        inline EntityList& getEntities();

        template<typename Type>
        inline EntityList& getEntities();

        inline RangeAll all() const;
    } &Db = Singleton<class Database>::instanceRef;
    Database::EntityList  Database::emptyList = Database::EntityList();

    // -----------------------------------------------------------------------------------------------

    namespace detail
    {
        template<class Ty1, class Ty2>
        struct _safe_cast
        {
            Ty1* operator()(ComponentBase* c) { return dynamic_cast<Ty1*>(c); }
        };

        template<class Ty1>
        struct _safe_cast<Ty1, Ty1>
        {
            Ty1* operator()(ComponentBase* c) { return static_cast<Ty1*>(c); }
        };

        template<typename Type>
        Type* safe_cast(ComponentBase* c)
        {
            static_assert(std::is_base_of<ComponentBase, Type>::value, "Not base of componentbase.");
            return _safe_cast<Type, typename Type::Template>()(c);
        }
    }

    // -----------------------------------------------------------------------------------------------
    // entity_iterator

    Database::entity_iterator::entity_iterator(iterator iter)
        : inner(iter)
    {
    }

    Database::entity_iterator::entity_iterator(const Database::entity_iterator& other)
        : inner(other.inner)
    {
    }

    Database::entity_iterator& Database::entity_iterator::operator++()
    {
        inner++;
        return *this;
    }

    Database::entity_iterator Database::entity_iterator::operator++(int value)
    {
        entity_iterator temp(*this);
        operator++();
        return temp;
    }

    bool Database::entity_iterator::operator==(const Database::entity_iterator& other) const
    {
        return inner == other.inner;
    }

    bool Database::entity_iterator::operator!=(const Database::entity_iterator& other) const
    {
        return inner != other.inner;
    }

    Entity* Database::entity_iterator::operator*() const
    {
        return *inner;
    }

    // -----------------------------------------------------------------------------------------------
    // entity_iterator

    template<typename TIterator>
    inline Database::entity_ref_iterator<TIterator>::entity_ref_iterator(TIterator iterator)
        : inner(iterator)
    {
    }

    template<typename TIterator>
    inline typename Database::entity_ref_iterator<TIterator>::this_type& Database::entity_ref_iterator<TIterator>::operator++()
    {
        inner++;
        return *this;
    }

    template<typename TIterator>
    inline typename Database::entity_ref_iterator<TIterator>::this_type Database::entity_ref_iterator<TIterator>::operator++(int)
    {
        this_type temp(*this);
        operator++();
        return temp;
    }

    template<typename TIterator>
    inline bool Database::entity_ref_iterator<TIterator>::operator==(const typename Database::entity_ref_iterator<TIterator>::this_type& other) const
    {
        return inner == other.inner;
    }

    template<typename TIterator>
    inline bool Database::entity_ref_iterator<TIterator>::operator!=(const typename Database::entity_ref_iterator<TIterator>::this_type& other) const
    {
        return inner != other.inner;
    }

    template<typename TIterator>
    inline Entity& Database::entity_ref_iterator<TIterator>::operator*() const
    {
        return **inner;
    }

    // -----------------------------------------------------------------------------------------------

    inline Database::RangeAll::RangeAll()
    {
    }

    inline Database::RangeAll::const_iterator Database::RangeAll::begin() const
    {
        return const_iterator(Db.entities.begin());
    }

    inline Database::RangeAll::const_iterator Database::RangeAll::end() const
    {
        return const_iterator(Db.entities.end());
    }

    inline Database::RangeType::RangeType(Guid type)
        : typeIterator(Db.componentIndex.find(type))
        , type(type)
    {
    }

    inline Database::RangeType::const_iterator Database::RangeType::begin() const
    {
        if (typeIterator == Db.componentIndex.end())
            return static_cast<Database::RangeType::const_iterator>(Database::emptyList.begin());
        return typeIterator->second.begin();
    }

    inline Database::RangeType::const_iterator Database::RangeType::end() const
    {
        if (typeIterator == Db.componentIndex.end())
            return static_cast<Database::RangeType::const_iterator>(Database::emptyList.end());
        return typeIterator->second.end();
    }

    // -----------------------------------------------------------------------------------------------

    inline Database::RangeTag::RangeTag(Guid type)
        : typeIterator(Db.tagIndex.find(type))
        , type(type)
    {
    }

    inline Database::RangeTag::const_iterator Database::RangeTag::begin() const
    {
        if (typeIterator == Db.tagIndex.end())
            return static_cast<Database::RangeType::const_iterator>(Database::emptyList.begin());
        return typeIterator->second.begin();
    }

    inline Database::RangeTag::const_iterator Database::RangeTag::end() const
    {
        if (typeIterator == Db.tagIndex.end())
            return static_cast<Database::RangeType::const_iterator>(Database::emptyList.end());
        return typeIterator->second.end();
    }

    // -----------------------------------------------------------------------------------------------

    template<typename TRange>
    inline Database::RefRange<TRange>::RefRange(TRange range)
        : range(range)
    {
    }

    template<typename TRange>
    inline typename Database::RefRange<TRange>::const_iterator Database::RefRange<TRange>::begin() const
    {
        return const_iterator(range.begin());
    }

    template<typename TRange>
    inline typename Database::RefRange<TRange>::const_iterator Database::RefRange<TRange>::end() const
    {
        return const_iterator(range.end());
    }

    // -----------------------------------------------------------------------------------------------
    // Database Implementation

    Database::Database()
    {
    }

    Database::~Database()
    {
        componentIndex.clear();
        tagIndex.clear();
    }

    Entity::Ptr Database::create()
    {
        auto handle = Entity::MakeNew();
        auto position = std::lower_bound(entities.begin(), entities.end(), handle.get());
        entities.insert(position, handle.get());
        return handle;
    }

    void Database::destroy(Entity& e)
    {
        // Getting the components and removing them and also removing the entity from the type index
        auto& components = e.components;
        while(!components.empty())
        {
            // Getting the component at the end of the list
            auto c = std::next(components.end(), -1);
            auto type = c->first;

            // Have the type just have to remove the entity from the indexmap
            removeComponent(e, type, c->second);
        }

        auto& tags = e.tags;
        while (!tags.empty())
        {
            // Getting the tag at the end of the list
            auto t = std::next(tags.end(), - 1);

            // Have the type just have to remove it from the tag index map
            removeTag(e, *t);
        }

        // Finding the entity in the entity list
        auto it = std::lower_bound(entities.begin(), entities.end(), &e);
        entities.erase(it);
    }

    template<typename Type, typename... Args>
    Type& Database::addComponent(Entity& e, Args&&... args)
    {
        static_assert(std::is_base_of<ComponentBase, Type>::value, "Type is not base of Component");
        ASSERT(!hasComponent<Type::Template>(e), "Entity already has component type");

        auto& components = e.components;

        // Have to lower bounds once to check to see where it will be inserted. Can also check to
        // see if it is already in the entity. If it is then we can assert
        auto position = std::lower_bound(components.begin(), components.end(),
            Entity::ComponentTuple(Type::GetType(), nullptr), Entity::ComponentComparitor());

        auto type = Type::GetType();
        auto tuple = Entity::ComponentTuple(type, new Type(e, std::forward<Args>(args)...));
        components.insert(position, tuple);

        // Update the component type index to have this entity
        auto& index_list = componentIndex[type];
        auto entity_position = std::lower_bound(index_list.begin(), index_list.end(),&e);
        index_list.insert(entity_position,&e);

        return *static_cast<Type*>(tuple.second);
    }

    template<typename Type, typename... Args>
    Type& Database::replaceComponent(Entity& e, Args&&... args)
    {
        static_assert(std::is_base_of<ComponentBase, Type>::value, "Type is not base of component");
        auto& components = e.components;

        auto position = std::lower_bound(components.begin(), components.end(),
            Entity::ComponentTuple(Type::GetType(), nullptr), Entity::ComponentComparitor());

        auto type = Type::GetType();
        auto tuple = Entity::ComponentTuple(type, new Type(e, std::forward<Args>(args)...));

        // Checking to see if we are creating a new entity or replacing
        if (hasComponent<typename Type::Template>(e)) // Replacing component
        {
            auto old = position->second;
            position->second = tuple.second;
            delete old;
        }
        else // add new component
        {
            components.insert(position, tuple);
            // Update the component type index to have this entity
            auto& index_list = componentIndex[type];
            auto entity_position = std::lower_bound(index_list.begin(), index_list.end(), &e);
            index_list.insert(entity_position, &e);
        }
        return *static_cast<Type*>(tuple.second);
    }

    template<typename Type>
    bool Database::removeComponent(Entity& e)
    {
        static_assert(std::is_base_of<ComponentBase, Type>::value, "Type is not base of Component");
        auto& components = e.components;

        auto type = Type::GetType();
        auto tuple = Entity::ComponentTuple(type, nullptr);

        // Getting the component from the entity list
        auto it = std::lower_bound(components.begin(), components.end(), tuple, Entity::ComponentComparitor());
        if (it == components.end())
            return false;

        // Checking to see if it is the same type
        if (!detail::safe_cast<Type>(it->second))
            return false;

        // Removing entity from component type index
        auto& index_list = componentIndex[type];
        auto entity_position = std::lower_bound(index_list.begin(), index_list.end(), &e);
        index_list.erase(entity_position);

        // Deleting the component and removing it from the entity list
        delete it->second;
        components.erase(it);
        return true;
    }

    bool Database::removeComponent(Entity& e, Guid type, ComponentBase* c)
    {
        auto& components = e.components;

        auto tuple = Entity::ComponentTuple(type, c);

        auto it = std::lower_bound(components.begin(), components.end(), tuple, Entity::ComponentComparitor());
        if (it == components.end())
            return false;

        // Removing entity from component type index
        auto& index_list = componentIndex[type];
        auto entity_position = std::lower_bound(index_list.begin(), index_list.end(), &e);
        index_list.erase(entity_position);

        // Deleting the component and removing from entity list.
        delete it->second;
        components.erase(it);
        return true;
    }

    void Database::cleanEntity(Entity& e)
    {
        auto& components = e.components;
        while (!components.empty())
        {
            auto c = std::next(components.end(), -1);
            removeComponent(e, c->first, c->second);
        }

        auto& tags = e.tags;
        while (!tags.empty())
        {
            auto t = std::next(tags.end(), -1);
            removeTag(e, *t);
        }
    }

    template<typename Type>
    Type& Database::getComponent(Entity& e)
    {
        auto result = tryGetComponent<Type>(e);
        ASSERT(result != nullptr,
            "Component does not exist in entity. Cannot return reference to a nullptr. Try using tryGet()");
        return *result;
    }

    template<typename Type>
    Type* Database::tryGetComponent(Entity& e)
    {
        auto& components = e.components;

        auto tuple = Entity::ComponentTuple(Type::GetType(), nullptr);
        auto it = std::lower_bound(components.begin(), components.end(), tuple, Entity::ComponentComparitor());

        if (it == components.end())
            return nullptr;

        return detail::safe_cast<Type>(it->second);
    }

    template<typename Type>
    bool Database::hasComponent(Entity& e)
    {
        return tryGetComponent<Type>(e) != nullptr;
    }

    // Tags -----

    template<typename Type>
    void Database::addTag(Entity& e, ComponentTag<Type> t)
    {
#ifdef EDN_DEBUG
        if (hasTag(e, t))
            return;
#endif
        auto& tags = e.tags;

        auto type = t.type;
        auto position = std::lower_bound(tags.begin(), tags.end(), type);

        tags.insert(position, type);

        auto& index_list = tagIndex[type];
        auto entity_position = std::lower_bound(index_list.begin(), index_list.end(), &e);
        index_list.insert(entity_position, &e);
    }

    template<typename Type>
    void Database::removeTag(Entity& e, ComponentTag<Type> t)
    {
        auto& tags = e.tags;
        auto type = t.type;

        // Getting the component from the entity list
        auto it = std::lower_bound(tags.begin(), tags.end(), type);
        if (it == tags.end())
            return;

        // Removing entity from component type index
        auto& index_list = tagIndex[type];
        auto entity_position = std::lower_bound(index_list.begin(), index_list.end(), &e);
        index_list.erase(entity_position);

        // Deleting the component and removing it from the entity list
        tags.erase(it);
    }

    void Database::removeTag(Entity& e, Guid type)
    {
        auto& tags = e.tags;

        auto it = std::lower_bound(tags.begin(), tags.end(), type);
        if (it == tags.end())
            return;

        // Removing entity from component type index
        auto& index_list = tagIndex[type];
        auto entity_position = std::lower_bound(index_list.begin(), index_list.end(), &e);
        index_list.erase(entity_position);

        // Eemoving from entity list.
        tags.erase(it);
    }

    template<typename Type>
    bool Database::hasTag(Entity& e, ComponentTag<Type> t)
    {
        auto& tags = e.tags;
        return std::binary_search(tags.begin(), tags.end(), t.type);
    }

    template<class Filter>
    inline typename Database::RefRange<typename Query::Simplify<Filter>::Result::RangeType> Database::where(const Filter& fullQuery) const
    {
        //return Query::toSimple(fullQuery).toRange();
        auto range = typename Query::Simplify<Filter>::Result::RangeType(Query::toSimple(fullQuery).toRange());
        return RefRange<typename Query::Simplify<Filter>::Result::RangeType>(range);
    }

    inline u32 Database::getEntityCount()
    {
        return static_cast<u32>(entities.size());
    }

    inline Database::EntityList& Database::getEntities()
    {
        return entities;
    }

    template<typename Type>
    inline Database::EntityList& Database::getEntities()
    {
        auto type = Type::GetType();
        auto it = tagIndex.find(type);
        ASSERT(it != componentIndex.end(), "There are entities with that type");
        return it->second;
    }
    inline Database::RangeAll Database::all() const
    {
        return RangeAll();
    }

    // -----------------------------------------------------------------------------------------------
    // Entity Implementation

    Entity::~Entity()
    {
        Db.destroy(*this);
    }

    template<typename Type, typename... Args>
    Type& Entity::add(Args&&... args)
    {
        return Db.addComponent<Type>(*this, std::forward<Args>(args)...);
    }

    template<typename Type, typename... Args>
    Type& Entity::replace(Args&&... args)
    {
        return Db.replaceComponent<Type>(*this, std::forward<Args>(args)...);
    }

    template<typename Type>
    void Entity::remove()
    {
        Db.removeComponent<Type>(*this);
    }

    template<typename Type>
    Type& Entity::get()
    {
        return Db.getComponent<Type>(*this);
    }

    template<typename Type>
    Type* Entity::tryGet()
    {
        return Db.tryGetComponent<Type>(*this);
    }

    template<typename Type>
    bool Entity::has()
    {
        return Db.hasComponent<Type>(*this);
    }

    template<typename Type>
    void Entity::addTag(ComponentTag<Type> t)
    {
        Db.addTag<Type>(*this, t);
    }

    template<typename Type>
    void Entity::removeTag(ComponentTag<Type> t)
    {
        Db.removeTag<Type>(*this, t);
    }

    template<typename Type>
    bool Entity::hasTag(ComponentTag<Type> t)
    {
        return Db.hasTag<Type>(*this, t);
    }

    u32 Entity::getComponentCount()
    {
        return static_cast<u32>(components.size());
    }

    Entity::ComponentList& Entity::getComponents()
    {
        return components;
    }

    // -----------------------------------------------------------------------------------------------
    // Query

    namespace Query
    {
        template<class LeftQuery>
        struct BaseQuery
        {
            template<class RightQuery>
            IntersectionQuery<LeftQuery, RightQuery> operator&&(const RightQuery& rhs) const
            {
                return IntersectionQuery<LeftQuery, RightQuery>(*static_cast<const LeftQuery*>(this), rhs);
            }

            DifferenceQuery<AllQuery, LeftQuery> operator!() const
            {
                return DifferenceQuery<AllQuery, LeftQuery>(AllQuery(), *static_cast<const LeftQuery*>(this));
            }

            template<class RightQuery>
            UnionQuery<LeftQuery, RightQuery> operator||(const RightQuery& rhs) const
            {
                return UnionQuery<LeftQuery, RightQuery>(*static_cast<const LeftQuery*>(this), rhs);
            }

            template<class RightQuery>
            ExclusiveQuery<LeftQuery, RightQuery> operator^(const RightQuery& rhs) const
            {
                return ExclusiveQuery<LeftQuery, RightQuery>(*static_cast<const LeftQuery*>(this), rhs);
            }
        };

        template<class LeftQuery, class RightQuery>
        struct IntersectionQuery : public BaseQuery<IntersectionQuery<LeftQuery, RightQuery>>
        {
            typedef RangeOperation<
                typename LeftQuery::RangeType::const_iterator,
                typename RightQuery::RangeType::const_iterator, Intersection> RangeType;

            IntersectionQuery(const LeftQuery& lhs, const RightQuery& rhs)
                : left(lhs)
                , right(rhs)
            {
            }

            RangeType toRange()
            {
                return make_intersection_range(left.toRange(), right.toRange());
            }

            LeftQuery left;
            RightQuery right;
        };

        template<class LeftQuery, class RightQuery>
        struct DifferenceQuery : public BaseQuery<DifferenceQuery<LeftQuery, RightQuery>>
        {
            typedef RangeOperation<
                typename LeftQuery::RangeType::const_iterator,
                typename RightQuery::RangeType::const_iterator, Difference> RangeType;

            DifferenceQuery(const LeftQuery& lhs, const RightQuery& rhs)
                : left(lhs)
                , right(rhs)
            {
            }

            RangeType toRange()
            {
                return make_difference_range(left.toRange(), right.toRange());
            }

            LeftQuery left;
            RightQuery right;
        };

        template<class LeftQuery, class RightQuery>
        struct UnionQuery : public BaseQuery<UnionQuery<LeftQuery, RightQuery>>
        {
            typedef RangeOperation<
                typename LeftQuery::RangeType::const_iterator,
                typename RightQuery::RangeType::const_iterator, Union> RangeType;

            UnionQuery(const LeftQuery& lhs, const RightQuery& rhs)
                : left(lhs)
                , right(rhs)
            {
            }

            RangeType toRange()
            {
                return make_union_range(left.toRange(), right.toRange());
            }

            LeftQuery left;
            RightQuery right;
        };

        template<class LeftQuery, class RightQuery>
        struct ExclusiveQuery : public BaseQuery<ExclusiveQuery<LeftQuery, RightQuery>>
        {
            typedef RangeOperation<
                typename LeftQuery::RangeType::const_iterator,
                typename RightQuery::RangeType::const_iterator, Exclusive> RangeType;

            ExclusiveQuery(const LeftQuery& lhs, const RightQuery& rhs)
                : left(lhs)
                , right(rhs)
            {
            }

            RangeType toRange()
            {
                return make_exclusive_range(left.toRange(), right.toRange());
            }

            LeftQuery left;
            RightQuery right;
        };

        struct AllQuery : public BaseQuery<AllQuery>
        {
            typedef typename Database::RangeAll RangeType;
            AllQuery() { }

            RangeType toRange()
            {
                return RangeType();
            }
        };

        struct TypeQuery : public BaseQuery<TypeQuery>
        {
            typedef typename Database::RangeType RangeType;

            TypeQuery(Guid type)
                : type(type)
            {
            }

            RangeType toRange()
            {
                return RangeType(type);
            }
        private:
            Guid type;
        };

        struct TagQuery : public BaseQuery<TagQuery>
        {
            typedef typename Database::RangeTag RangeType;

            TagQuery(Guid tag)
                : tag(tag)
            {
            }

            RangeType toRange()
            {
                return Database::RangeTag(tag);
            }
        private:
            Guid tag;
        };

        // If we are intersecting one with all queries it is just one
        template<class One>
        struct Simplify<IntersectionQuery<One, AllQuery>>
        {
            typedef Simplify<One> S1;
            typedef typename S1::Result Result;
            typedef IntersectionQuery<One, AllQuery> Case;

            static Result toSimple(Case& c)
            {
                return S1::toSimple(c.left);
            }
        };

        // This is the same case as before just the other order
        template<class Two>
        struct Simplify<IntersectionQuery<AllQuery, Two>>
        {
            typedef Simplify<Two> S2;
            typedef typename S2::Result Result;
            typedef IntersectionQuery<AllQuery, Two> Case;

            static Result toSimple(Case& q)
            {
                return S2::toSimple(q.right);
            }
        };

        // This case is for where(has<One>() && !has<Two>())
        // this can be optimised to me the difference of one and two
        template<class One, class Two>
        struct Simplify<IntersectionQuery<One, DifferenceQuery<AllQuery, Two>>>
        {
            typedef Simplify<One> S1;
            typedef Simplify<Two> S2;
            typedef DifferenceQuery<typename S1::Result, typename S2::Result> Result;
            typedef IntersectionQuery<One, DifferenceQuery<AllQuery, Two>> Case;

            static Result toSimple(const Case& c)
            {
                return Result(S1::toSimple(c.left), S2::toSimple(c.right.right));
            }
        };
    }

    template<class Component>
    inline Query::TypeQuery hasComponent()
    {
        static_assert(std::is_base_of<ComponentBase, Component>::value, "Type is not a component");
        return Query::TypeQuery(Component::Template::GetType());
    }

    template<class Component>
    inline Query::TypeQuery hasComponent(Component c)
    {
        static_assert(std::is_base_of<ComponentBase, Component>::value, "Type is not a component");
        return Query::TypeQuery(c.GetType());
    }

    template<class Tag>
    inline Query::TagQuery hasTag()
    {
        return Query::TagQuery(ComponentTag<Tag>::type);
    }

    template<class Tag>
    inline Query::TagQuery hasTag(ComponentTag<Tag> t)
    {
        return Query::TagQuery(t.type);
    }

    template<class Range>
    inline Database::EntityRefList toVector(const Range& range)
    {
        return Database::EntityRefList(range.begin(), range.end());
    }
}
