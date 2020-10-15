/*
    LibLCU,
    2020 - par0-git
    Class / SerializedValue

    This class is the wrapper for a JSON object.
*/
#pragma once
#include <string> // for SerializedValueType::STRING
#include <vector> // for SerializedValueType::VECTOR
#include "Exceptions/SerializedObjectException.h"
#include <rapidjson/document.h> // Method of parsing

namespace LCU {
    enum SerializedValueType {
        INVALID,
        STRING,
        INT32,
        INT64,
        UINT32,
        UINT64,
        BOOL,
        VECTOR,
    };

    // This class is a wrapper for a JSON object.
    class SerializedValue {
    public:
        SerializedValue(const rapidjson::Value& value) {
            // RapidJSON method of parsing
            switch (value.GetType()) {
            case rapidjson::Type::kNullType:
                type = SerializedValueType::INVALID;
                break;
            case rapidjson::Type::kFalseType:
            case rapidjson::Type::kTrueType:
                type = SerializedValueType::BOOL;
                vBool = true;
                break;
            case rapidjson::Type::kObjectType:
                type = SerializedValueType::INVALID;
                break;
            case rapidjson::Type::kArrayType:
                type = SerializedValueType::VECTOR;

                break;
            case rapidjson::Type::kStringType:
                type = SerializedValueType::STRING;
                vString = value.GetString();
                break;
            case rapidjson::Type::kNumberType:
                if (value.IsUint64()) {
                    type = SerializedValueType::UINT64;
                    vUInt64 = value.GetUint64();
                }
                else if (value.IsUint()) {
                    type = SerializedValueType::UINT32;
                    vUInt32 = value.GetUint();
                }
                else if (value.IsInt64()) {
                    type = SerializedValueType::INT64;
                    vInt64 = value.GetInt64();
                }
                else {
                    type = SerializedValueType::INT32;
                    vInt32 = value.GetInt();
                    vInt32 = 0;
                }
                break;
            default:
                type = SerializedValueType::INVALID;
            }
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

        int64_t& Int64() {
            if (type != SerializedValueType::INT64)
                throw LCU::Exception::SerializedValueFailure("Tried to get an Int64 from a(n) " + Type());

            return vInt64;
        }

        uint32_t& UInt() {
            if (type != SerializedValueType::UINT32)
                throw LCU::Exception::SerializedValueFailure("Tried to get a UInt32 from a(n) " + Type());

            return vUInt32;
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
        
        SerializedValueType& getType() { return type; }
        std::string getTypeReadable() { return Type(); }
    private:
        SerializedValueType type;
        union {
            int vInt32;
            int64_t vInt64;
            uint32_t vUInt32;
            uint64_t vUInt64;
            bool vBool;
        };
        std::vector<SerializedValue> vArray; // std::vector can't be in a union
        std::string vString; // std::string can't be in a union

        std::string Type() {
            std::string typeNames[sizeof(SerializedValueType) + 1] = { "string", "int32", "uint64", "bool", "vector" };
            return typeNames[(int)type];
        }
    };
}