#pragma once
#include "Core/Types.h"

namespace Math
{
    class Radian;
    class Degree;

    // --------------------------------------------------------------------------------------------
    // Radian

    class Radian
    {
        static const f32 pi;
    public:
        Radian();
        Radian(Degree degree);
        explicit Radian(f32 value);

        Degree toDegree() const;

        f32 operator*(f32 rhs) const;
        f32& operator()();

        f32 value;
    };

    // --------------------------------------------------------------------------------------------
    // Degree

    class Degree
    {
        static const f32 pi;
    public:
        Degree();
        Degree(Radian radian);
        explicit Degree(f32 value);

        Radian toRadian();

        f32 operator*(f32 rhs) const;
        f32& operator()();

        f32 value;
    };

    // --------------------------------------------------------------------------------------------
    // Radian

    inline Radian::Radian()
        : value(0)
    {
    }

    inline Radian::Radian(Degree degree)
    {
        value = degree * pi / 180.f;
    }

    inline Radian::Radian(f32 value)
        : value(value)
    {
    }

    inline Degree Radian::toDegree() const
    {
        return Degree(*this);
    }

    inline f32 Radian::operator*(f32 rhs) const
    {
        return value * rhs;
    }

    inline f32& Radian::operator()()
    {
        return value;
    }

    // --------------------------------------------------------------------------------------------
    // Degree

    inline Degree::Degree()
        : value(0)
    {
    }

    inline Degree::Degree(Radian radian)
    {
        value = radian() * (pi * 180.f);
    }

    inline Degree::Degree(f32 value)
        : value(value)
    {
    }

    inline Radian Degree::toRadian()
    {
        return Radian(*this);
    }

    inline f32 Degree::operator*(f32 rhs) const
    {
        return value * rhs;
    }

    inline f32& Degree::operator()()
    {
        return value;
    }
}
