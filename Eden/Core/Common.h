#ifndef H_CORE_COMMON_H
#define H_CORE_COMMON_H

namespace edn
{
	//
	// NonCopyable
	//
	class NonCopyable
	{
	protected:
		NonCopyable();
	private:
		NonCopyable(const NonCopyable&) = delete;
		NonCopyable& operator=(const NonCopyable&) = delete;
	};

	//
	// Singleton
	//
	template<typename Type>
	class Singleton : private NonCopyable
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