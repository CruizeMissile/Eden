#ifndef H_CORE_COMMON_H
#define H_CORE_COMMON_H

namespace edn
{
	//
	// NonCopyable
	//
	class NonCopyable
	{
	public:
		NonCopyable() { }
		NonCopyable(const NonCopyable&) = delete;
		NonCopyable& operator=(const NonCopyable&) = delete;
	};

	//
	// Singleton
	//
	template<typename Type>
	class Singleton : public NonCopyable
	{
	public:
		static Type & Instance()
		{
			static Type instance;
			return instance;
		}
	protected:
		explicit Singleton<Type>() {}
	};
}

#endif