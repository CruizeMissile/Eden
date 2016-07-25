#pragma once

template <typename T>
struct TypeName
{
	static const char* Get()
	{
		return typeid(T).name();
	}
};

#define EDN_TYPENAME (_) template<> struct TypeName<_> { static const char *Get() { return #_; }}
