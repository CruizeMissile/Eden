#pragma once

#include "Core/Platform.h"
#include "Core/Types.h"
#include <iostream>

namespace Hidden
{
    static const u32 FRONT_SIZE = sizeof("Hidden::GetTypeNameHelper<");
    static const u32 BACK_SIZE = sizeof(">::GetTypeName");
    template<class T>
    struct GetTypeNameHelper
    {
        static String GetTypeName()
        {
            String func(__FUNCTION__);
            u32 size = sizeof(__FUNCTION__) - FRONT_SIZE - BACK_SIZE;
            String result = func.substr(FRONT_SIZE - 1, size + 1);
            u32 space = static_cast<u32>(result.find(' '));
            if (space == String::npos)
                return result;
            result = result.substr(space + 1);
            return result;
        }
    };
}

template<class T>
struct TypeInfo
{
    static const String name;
};

template<class T>
const String TypeInfo<T>::name = Hidden::GetTypeNameHelper<T>::GetTypeName();
