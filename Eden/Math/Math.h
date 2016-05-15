#ifndef H_MATH_MATH_H
#define H_MATH_MATH_H

namespace edn
{
	#define PI 3.14159265358979323846

	inline float ToRadian(float degrees)
	{
		return (degrees * PI) / 180;
	}
}

#endif