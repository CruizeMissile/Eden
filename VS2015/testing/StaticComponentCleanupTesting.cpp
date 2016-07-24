#include "Core/Common.h"

#include <iostream>
#include <vector>

using namespace edn;

template<typename Type>
std::vector<Type*> registerCleanup();

class ComponentBase
{ 
public: 
	virtual ~ComponentBase() {};
	u32 type_id; 
};

template<typename Type>
class Component : public ComponentBase
{
public:
	Component()
	{
		type_id = Entity::getGUID<Type>();
		Components.push_back(static_cast<Type*>(this));
	}

	~Component()
	{
		auto it = std::find(Components.begin(), Components.end(), this);
		if (it != Components.end())
		{
			Components.erase(it);
		}
	}

	static std::vector<Type*> Components;
};

template<typename Type>
std::vector<Type*> Component<Type>::Components = registerCleanup<Type>();

class Tasos : public Component<Tasos>
{
public:
	~Tasos()
	{
		//std::cout << "Smell TASOS while sleeping" << std::endl;
	}
};

class James : public Component<James>
{
public:
	~James()
	{
		//std::cout << "Inappropriately touch James" << std::endl;
	}
};

class Emi : public Component<Emi>
{
public:
	~Emi()
	{
		//std::cout << "Snuggle Emi" << std::endl;
	}
};

class Database : public Singleton<Database>
{
public:
	
	void cleanup()
	{
		for (unsigned i = 0; i < cleanupList.size(); i++)
		{
			for (unsigned j = 0; j < cleanupList[i]->size(); j++)
			{
				delete (*cleanupList[i])[j];
			}

			cleanupList[i]->clear();
		}
	}

	template<typename Type>
	Type * createComponent()
	{
		return new Type();
	}

	static std::vector<std::vector<ComponentBase*>*> cleanupList;
};

std::vector<std::vector<ComponentBase*>*> Database::cleanupList;

template<typename Type>
std::vector<Type*> registerCleanup()
{
	Database::Instance().cleanupList.push_back(reinterpret_cast<std::vector<ComponentBase*>*>(&Component<Type>::Components));
	//std::cout << "hi" << std::endl;
	return std::vector<Type*>();
}

//int main()
//{
//	Tasos *potato = new Tasos();
//	Emi *yolo = new Emi();
//	James *yames = new James();
//
//	Database::Instance().cleanup();
//
//	system("pause");
//	return 0;
//}