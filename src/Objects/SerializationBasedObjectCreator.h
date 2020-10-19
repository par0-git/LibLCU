/*
    LibLCU,
    2020 - par0-git
    Class / SerializationBasedObjectCreator

    This class helps create an object instance from multiple SerializedValues.
*/
#pragma once
#include "SerializedValue.h"

namespace LCU {
    struct SerializedObjectValue {
        SerializedValueType type;
        const char* src;
        void* ptr;
    };
}