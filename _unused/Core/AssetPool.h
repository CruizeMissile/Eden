#ifndef H_CORE_ASSET_POOL_H
#define H_CORE_ASSET_POOL_H

#include "Precompiled.h"

namespace edn
{
    class Asset;

    class AssetPoolInterface
    {
    protected:
        AssetPoolInterface() { }

    public:
        virtual ~AssetPoolInterface() { }
        virtual void Remove(String filename) = 0;
    };

    template<typename Type>
    class AssetPool : public AssetPoolInterface
    {
    public:
        static_assert(std::is_base_of<Asset, Type>::value, "Not a Asset type");
        typedef std::unordered_map<String, Type> AssetList;
        typedef typename AssetList::iterator AssetIterator;

    public:
        AssetPool()
        {

        }

        ~AssetPool()
        {
            Cleanup();
        }

        void Cleanup()
        {
            ClearContainer(m_assets);
        }

        Type * Create(String file)
        {
            auto result = m_assets.emplace(std::make_pair(file, Type()));

            if (result.second == false)
                return  nullptr;

            return &result.first->second;
        }

        Type * Lookup(String name)
        {
            auto result = m_assets.find(name);

            if (result == m_assets.end())
                return nullptr;

            return &result->second;
        }

        void Remove(String name)
        {
            m_assets.erase(name);
        }

        void Clear()
        {
            m_assets.clear();
        }

        void Begin()
        {
            return m_assets.begin();
        }

        void End()
        {
            return m_assets.end();
        }

    private:
        AssetList m_assets;
    };
}

#endif
