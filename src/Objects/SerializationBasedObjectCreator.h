/*
    LibLCU,
    2020 - par0-git
    Class / SerializationBasedObjectCreator

    This class helps create an object instance from multiple SerializedValues.
*/
#pragma once
#include "SerializedValue.h"

namespace LCU {
    enum SerializedObjectValueType {
        INVALID,
        OBJECT,
        STRING,
        NUMBER,
        BOOL,
        VECTOR,
        _MAX_
    };

    struct SerializedObjectValue {
        SerializedObjectValueType type;
        const char* src;
        void* ptr;
    };
}