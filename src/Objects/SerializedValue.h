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
        OBJECT,
        STRING,
        NUMBER,
        BOOL,
        VECTOR,
        _MAX_
    };

    // This class is a wrapper for a JSON object.
    class SerializedValue {
    public:
        SerializedValue(const rapidjson::Value& value, std::string _name = "undefined") {
            switch (value.GetType()) {
            case rapidjson::Type::kNullType:
                type = SerializedValueType::INVALID;
                break;
            case rapidjson::Type::kFalseType:
                type = SerializedValueType::BOOL;
                vBool = false;
                break;
            case rapidjson::Type::kTrueType:
                type = SerializedValueType::BOOL;
                vBool = true;
                break;
            case rapidjson::Type::kObjectType:
                type = SerializedValueType::OBJECT;
                for (rapidjson::Value::ConstMemberIterator i = value.MemberBegin(); i != value.MemberEnd(); ++i) {
                    const rapidjson::Value& objectNameValue = i->name;
                    const char* objectName = objectNameValue.GetString();

                    const rapidjson::Value& objectValue = i->value;

                    vObjects.push_back(SerializedValue(objectValue, objectName));
                }
                break;
            case rapidjson::Type::kArrayType:
                type = SerializedValueType::VECTOR;
                for (const rapidjson::Value& member : value.GetArray()) {
                    vArray.push_back(SerializedValue(member));
                }
                break;
            case rapidjson::Type::kStringType:
                type = SerializedValueType::STRING;
                vString = value.GetString();
                break;
            case rapidjson::Type::kNumberType:
                vInt32 = value.GetInt();
                type = SerializedValueType::NUMBER;
                break;
            default:
                throw LCU::Exception::SerializedParsingFailure("Object provided had an invalid type.");
                type = SerializedValueType::INVALID;
            }

            name = _name;
        }

        // Value Operators
        std::vector<SerializedValue>& Vector() {
            if (type != SerializedValueType::VECTOR)
                throw LCU::Exception::SerializedValueFailure("Tried to get a Vector from a(n) " + Type());

            return vArray;
        }

        std::string String() {
            if (type != SerializedValueType::STRING)
                throw LCU::Exception::SerializedValueFailure("Tried to get a String from a(n) " + Type());

            return vString;
        }

        int Int() {
            if (type != SerializedValueType::NUMBER)
                throw LCU::Exception::SerializedValueFailure("Tried to get a Number from a(n) " + Type());

            return vInt32;
        }

        bool Bool() {
            if (type != SerializedValueType::BOOL)
                throw LCU::Exception::SerializedValueFailure("Tried to get a Bool from a(n) " + Type());

            return vBool;
        }

        // Object Manipulation
        SerializedValue& Child(std::string object) {
            if (type != SerializedValueType::OBJECT)
                throw LCU::Exception::SerializedObjectFailure("Can't get an object from a " + Type());

            for (int i = 0; i < vObjects.size(); i++) {
                if (vObjects[i].getName() == object)
                    return vObjects[i];
            }

            throw LCU::Exception::SerializedObjectFailure("Object was not found.");
        }

        // Value Data
        std::string getReadable() {
            switch (type) {
            case SerializedValueType::INVALID:
                return "undefined";
                break;
            case SerializedValueType::OBJECT:
                return "object with " + std::to_string(vObjects.size()) + " children";
                break;
            case SerializedValueType::STRING:
                return vString;
                break;
            case SerializedValueType::NUMBER:
                return std::to_string(vInt32);
                break;
            case SerializedValueType::BOOL:
                return vBool ? "true" : "false";
                break;
            case SerializedValueType::VECTOR:
                return "array with " + std::to_string(vArray.size()) + " members";
                break;
            default:
                return "invalid";
            }
        }

        std::string getInfo() {
            return "([" + Type() + "], " + name + "): " + getReadable();
        }
        std::string getName() { return name; }
        void setName(std::string _name) { name = _name; }

        SerializedValueType& getType() { return type; }
        std::string getTypeReadable() { return Type(); }
    private:
        std::string name;
        union {
            int vInt32;
            bool vBool;
        };
        SerializedValueType type;
        std::vector<SerializedValue> vArray; // std::vector can't be in a union
        std::vector<SerializedValue> vObjects; // std::vector can't be in a union
        std::string vString; // std::string can't be in a union

        std::string Type() {
            std::string typeNames[SerializedValueType::_MAX_] = { "undefined", "object", "string", "number", "bool", "vector" };
            return typeNames[(int)type];
        }
    };
}