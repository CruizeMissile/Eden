#ifndef H_CORE_ASSET_MANAGER_H
#define H_CORE_ASSET_MANAGER_H

#include "Precompiled.h"
#include "AssetPool.h"
#include "Singleton.h"

namespace edn
{
	class AssetManager;

	class Asset
	{
		friend class AssetManager;
	public:
		void Load(String filename);

		//protected:
		virtual void loadFromFile(String filename) = 0;
		virtual void loadFromCashe(String filename) = 0;
		virtual void writeCacheFile(String filename) = 0;

		String m_name;
		String m_subDir;
	};

	static class AssetManager : public Singleton<class AssetManager>
	{
		typedef std::unique_ptr<AssetPoolInterface> AssetPoolPtr;
		typedef std::unordered_map<std::type_index, AssetPoolPtr> AssetPoolList;
		typedef AssetPoolList::value_type AssetPoolPair;

	public:
		template<typename Type>
		void Register();

		template<typename Type>
		Type * Load(String file);

		//Texture * texture = AssetManager::Load<Texture>(filename);

		String & AssetPath() { return m_rootAssetPath; }
		String & CachePath() { return m_rootCachePath; }

		void SetAssetPath(String path) { m_rootAssetPath = path; }
		void SetCachePath(String path) { m_rootCachePath = path; }

	private:
		template<typename Type>
		Type * create(String file);
		template<typename Type>
		Type * lookup(String file);

		template<typename Type>
		AssetPool<Type> * getAssetPool();

		AssetPoolList m_assets;
		String m_rootAssetPath;
		String m_rootCachePath;
	} &AssetManager = Singleton<class AssetManager>::instanceRef;

	//
	// Asset
	//


	//
	// AssetManager
	//
	template<typename Type>
	void AssetManager::Register()
	{
		// Validate Asset type
		static_assert(std::is_base_of<Asset, Type>::value, "Not a asset type");

		// Check if Asset type is registered
		auto it = AssetManager.m_assets.find(typeid(Type));

		if (it != AssetManager.m_assets.end())
			return;

		std::type_index index = typeid(Type);

		auto poolPtr = std::make_unique<AssetPool<Type>>();

		auto pair = std::make_pair(index, std::move(poolPtr));
		auto result = AssetManager.m_assets.insert(std::move(pair));
	}

	template<typename Type>
	Type * AssetManager::Load(String file)
	{
		// Validate component type
		static_assert(std::is_base_of<Asset, Type>::value, "Not a Asset type");

		// Getting the Type asset list
		Type * value = lookup<Type>(file);

		// could not find the
		if (value == nullptr)
		{
			value = create<Type>(file);
			value->Load(file);
			return value;
		}
		return value;
	}

	template<typename Type>
	Type * AssetManager::create(String file)
	{
		AssetPool<Type> * pool = getAssetPool<Type>();

		if (pool == nullptr)
			return nullptr;

		return pool->Create(file);
	}

	template<typename Type>
	Type * AssetManager::lookup(String file)
	{
		AssetPool<Type> * pool = getAssetPool<Type>();

		if (pool == nullptr)
			return nullptr;

		return pool->Lookup(file);
	}

	template<typename Type>
	AssetPool<Type> * AssetManager::getAssetPool()
	{
		auto it = m_assets.find(typeid(Type));
		if (it == m_assets.end())
			return nullptr;

		AssetPool<Type> * pool = reinterpret_cast<AssetPool<Type>*>(it->second.get());
		return pool;
	}
}

#endif
