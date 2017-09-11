#pragma once
#include "Core\Types.h"
#include <unordered_map>
#include <atomic>

template<typename ValueType>
class TypeMap
{
    // Internally, we are using a hash table to store the mappings from type ID's
    // to the values.
    typedef std::unordered_map<u32, ValueType> InternalMap;
public:

    typedef typename InternalMap::iterator iterator;
    typedef typename InternalMap::const_iterator const_iterator;
    typedef typename InternalMap::value_type value_type;

    const_iterator begin() const { return map.begin(); }
    const_iterator end() const { return map.end(); }

    iterator begin() { return map.begin(); }
    iterator end() { return map.end(); }

    // Finds the value associated with the type "Key" in the type map
    template<typename Key>
    iterator find() { return map.find(getTypeId<Key>()); }

    // Const version of find
    template<typename Key>
    const_iterator find() const { return map.find(getTypeId<Key>()); }

    // Associates a value with the type "Key"
    template<typename Key>
    void put(ValueType && value)
    {
        map[getTypeId<Key>()] = std::forward<ValueType>(value);
    }

private:
    template<typename Key>
    inline static int getTypeId()
    {
        static const int id = LastTypeId++;
        return id;
    }

    static std::atomic_int LastTypeId;
    InternalMap map;
};

template<typename ValueType>
std::atomic_int TypeMap<ValueType>::LastTypeId(0);
