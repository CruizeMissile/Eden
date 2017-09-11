#pragma once

#include "Core/Types.h"
#include "Entity/Guid.h"

#include <memory>
#include <vector>

namespace edn
{
    class Entity;

    class ComponentBase
    {
    public:
        ComponentBase() { }
        ComponentBase(const ComponentBase&) = delete;
        ComponentBase(ComponentBase&&) = default;
        virtual ~ComponentBase() { }
    };

    template<typename Type>
    class Component : public ComponentBase
    {
    public:
        typedef Type Template;

        Component(Entity& e);
        Component(const Component&) = delete;
        Component(Component&&) = default;
        ~Component() = default;

        static Guid GetType();

        virtual String toString() = 0;

        // The owner will never be null to it can be a reference
        Entity& owner;
    private:
        static Guid type_id;
    };

    template<typename Type>
    Guid Component<Type>::type_id = get_guid<Type>();

    template<typename Type>
    Guid Component<Type>::GetType()
    {
        return type_id;
    }

    template<typename Type>
    Component<Type>::Component(Entity& e)
        : owner(e)
    {
    }

    template<typename Type>
    inline String Component<Type>::toString()
    {
        return "Component";
    }

    // -----------------------------------------------------------------------------------------------
    // Component Tag

    class ComponentTagType
    {
    public:
        template<typename Type>
        static Guid get_type();

    private:
        static Guid& inst_guid();
        static Guid next_guid();
    };

    template<typename Type>
    inline Guid ComponentTagType::get_type()
    {
        static Guid guid = next_guid();
        return guid;
    }

    inline Guid& ComponentTagType::inst_guid()
    {
        static Guid guid = 0;
        return guid;
    }

    inline Guid ComponentTagType::next_guid()
    {
        Guid next = ++inst_guid();
        if (next == std::numeric_limits<Guid>::max())
            throw std::out_of_range("Component Guid hit max u32");
        return next;
    }

    template<typename Type>
    struct ComponentTag
    {
        static Guid type;
    };

    template<typename Type>
    Guid ComponentTag<Type>::type = ComponentTagType::get_type<Type>();

#define CREATE_TAG(tag_name) \
    struct EDN_PASTE(tag_name, TagName) : public ComponentTag<EDN_PASTE(tag_name, TagName)> {}; \
    typedef EDN_PASTE(tag_name, TagName) tag_name
}
