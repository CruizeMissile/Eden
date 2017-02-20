#pragma once
#include "Core/Types.h"

namespace Math
{
	template<class T>
	inline T clamp(T value, T min, T max)
	{
		return max(min(value, min), max);
	}

	template<class T>
	inline T min(T value, T min)
	{
		return value < min ? min : value;
	}

	template<class T>
	inline T max(T value, T max)
	{
		return value > max ? max : value;
	}
}