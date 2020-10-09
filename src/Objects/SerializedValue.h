/*
    LibLCU,
    2020 - par0-git
    Class / SerializedValue

    This class is the wrapper for a JSON object.
*/
#pragma once
#include <string> // for SerializedValueType::STRING
#include <vector> // for SerializedValueType::VECTOR
#include "../../Output/Exceptions.hpp"

namespace LCU {
    enum SerializedValueType {
        STRING,
        INT32,
        UINT64,
        BOOL,
        VECTOR,
    };
    
    // This class is a wrapper for a JSON object.
	class SerializedValue {
    public:
        SerializedValue() {

        }

        std::string& String() {
            if (type != SerializedValueType::STRING)
                throw LCU::Exception::SerializedValueFailure("Tried to get a String from a(n) " + Type());

            return vString;
        }

        int& Int() {
            if (type != SerializedValueType::INT32)
                throw LCU::Exception::SerializedValueFailure("Tried to get an Int32 from a(n) " + Type());
        
            return vInt32;
        }

        uint64_t& UInt64() {
            if (type != SerializedValueType::UINT64)
                throw LCU::Exception::SerializedValueFailure("Tried to get a UInt64 from a(n) " + Type());
        
            return vUInt64;
        }

        bool& Bool() {
            if (type != SerializedValueType::BOOL)
                throw LCU::Exception::SerializedValueFailure("Tried to get a Bool from a(n) " + Type());
            
            return vBool;
        }

        std::vector<SerializedValue>& Vector() {
            if (type != SerializedValueType::VECTOR)
                throw LCU::Exception::SerializedValueFailure("Tried to get a Vector from a(n) " + Type());

            return vArray;
        }

    private:
        SerializedValueType type;
        union {
            std::string vString;
            int vInt32;
            uint64_t vUInt64;
            bool vBool;
            std::vector<SerializedValue> vArray;
        };

        std::string Type() {
            std::string typeNames[sizeof(SerializedValueType)+1] = {"string", "int32", "uint64", "bool", "vector"};
            return typeNames[(int)type];
        }
	};
}