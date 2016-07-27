#pragma once

#include "Core/MacroHelpers.h"
#include "Entity/Guid.h"


template<typename T>
struct TypeInfo
{
	static const char * name;
	static u32 hash;
};

#define _INTERNAL_EDN_REGISTER_TYPE_NAME( _ ) \
	template<> const char * TypeInfo<_>::name = #_

#define _INTERNAL_EDN_REGISTER_TYPE_HASH( _ ) \
	template<> u32 TypeInfo<_>::hash = static_cast<u32>(std::hash<const char*>{}(EDN_STRINGIZE(_)));

#define EDN_REGISTER_TYPE(_) _INTERNAL_EDN_REGISTER_TYPE_NAME(_); _INTERNAL_EDN_REGISTER_TYPE_HASH(_)
