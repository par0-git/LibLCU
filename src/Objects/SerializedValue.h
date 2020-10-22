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
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

namespace LCU {
    enum class SerializedValueType {
        INVALID,
        OBJECT,
        STRING,
        NUMBER,
        BOOL,
        VECTOR,
        _MAX_
    };

    enum class SerializedValueNumberType {
        INVALID,
        INT,
        UINT64,
        DOUBLE,
        _MAX_
    };

    // This class is a wrapper for a JSON object.
    class SerializedValue {
    public:
        SerializedValue() : type{ SerializedValueType::INVALID }, nValType{SerializedValueNumberType::INVALID} {};
        SerializedValue(SerializedValueType forcedType) : type{forcedType} {};

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
                type = SerializedValueType::NUMBER;
                if (value.IsDouble()) {
                    vDouble = value.GetDouble();
                    nValType = SerializedValueNumberType::DOUBLE;
                    break;
                }
                else if (value.IsUint64()) {
                    vuInt64 = value.GetUint64();
                    nValType = SerializedValueNumberType::UINT64;
                    break;
                }

                nValType = SerializedValueNumberType::INT;
                vInt32 = value.GetInt();
                break;
            default:
                throw LCU::Exception::SerializedParsingFailure("Object provided had an invalid type.");
                type = SerializedValueType::INVALID;
            }

            name = _name;
        }

        // Conversions
        SerializedValue& operator= (const bool& a) { 
            type = SerializedValueType::BOOL;
            vBool = a;
            clean();
            return *this; 
        }

        SerializedValue& operator= (const std::vector<SerializedValue>& a) {
            type = SerializedValueType::VECTOR;
            vArray = a;
            clean();
            return *this;
        }

        SerializedValue& operator= (const std::string& a) {
            type = SerializedValueType::STRING;
            vString = a;
            clean();
            return *this;
        }

        SerializedValue& operator= (const int& a) {
            type = SerializedValueType::NUMBER;
            nValType = SerializedValueNumberType::INT;
            vInt32 = a;
            clean();
            return *this;
        }

        SerializedValue& operator= (const uint64_t& a) {
            type = SerializedValueType::NUMBER;
            nValType = SerializedValueNumberType::UINT64;
            vuInt64 = a;
            clean();
            return *this;
        }

        SerializedValue& operator= (const double& a) {
            type = SerializedValueType::NUMBER;
            nValType = SerializedValueNumberType::DOUBLE;
            vDouble = a;
            clean();
            return *this;
        }

        // Copy constructor
        SerializedValue(const SerializedValue& rhs) { 
            // Copy over data
            type = rhs.type;
            name = rhs.name;
            nValType = rhs.nValType;

            // Copy over value
            switch (type) {
            case SerializedValueType::INVALID:
                break;
            case SerializedValueType::OBJECT:
                vObjects = rhs.vObjects;
                break;
            case SerializedValueType::STRING:
                vString = rhs.vString;
                break;
            case SerializedValueType::NUMBER:
                vDouble = rhs.vDouble;
                vuInt64 = rhs.vuInt64;
                vInt32 = rhs.vInt32;
                break;
            case SerializedValueType::BOOL:
                vBool = rhs.vBool;
                break;
            case SerializedValueType::VECTOR:
                vArray = rhs.vArray;
                break;
            default:
                break;
            }

            // Clean new object
            clean();
        }

        // Value Operators
        std::vector<SerializedValue>& asVector() {
            if (type != SerializedValueType::VECTOR)
                throw LCU::Exception::SerializedValueFailure("Tried to get a Vector from a(n) " + getReadableType() + " [" + name + "]");

            return vArray;
        }

        std::string asString() {
            if (type != SerializedValueType::STRING)
                throw LCU::Exception::SerializedValueFailure("Tried to get a String from a(n) " + getReadableType() + " [" + name + "]");

            return vString;
        }

        int asInt() {
            if (type != SerializedValueType::NUMBER)
                throw LCU::Exception::SerializedValueFailure("Tried to get a Number from a(n) " + getReadableType() + " [" + name + "]");

            if (nValType != SerializedValueNumberType::INT)
                LCU::Log::Out(LCU::Log::LogLevel::WARNING, LCU::Log::LogActivity::CLASS_CREATION, "Converting a(n) %s to a int can result in precision loss.", getReadableNumberType());

            switch (nValType) {
            case SerializedValueNumberType::DOUBLE:
                return (int)vDouble;
                break;
            case SerializedValueNumberType::INT:
                return (int)vInt32;
                break;
            case SerializedValueNumberType::UINT64:
                return (int)vuInt64;
                break;
            default:
                throw LCU::Exception::SerializedValueFailure("Invalid number type [" + getReadableNumberType() + "]");
            }
        }
        
        double asDouble() {
            if (type != SerializedValueType::NUMBER)
                throw LCU::Exception::SerializedValueFailure("Tried to get a Number from a(n) " + getReadableType() + " [" + name + "]");

            if (nValType != SerializedValueNumberType::DOUBLE)
                LCU::Log::Out(LCU::Log::LogLevel::WARNING, LCU::Log::LogActivity::CLASS_CREATION, "Converting a(n) %s to a double can result in precision loss.", getReadableNumberType());

            switch (nValType) {
            case SerializedValueNumberType::DOUBLE:
                return (double)vDouble;
                break;
            case SerializedValueNumberType::INT:
                return (double)vInt32;
                break;
            case SerializedValueNumberType::UINT64:
                return (double)vuInt64;
                break;
            default:
                throw LCU::Exception::SerializedValueFailure("Invalid number type [" + getReadableNumberType() + "]");
            }
        }

        uint64_t asUint64() {
            if (type != SerializedValueType::NUMBER)
                throw LCU::Exception::SerializedValueFailure("Tried to get a Number from a(n) " + getReadableType() + " [" + name + "]");

            switch (nValType) {
            case SerializedValueNumberType::DOUBLE:
                return (uint64_t)vDouble;
                break;
            case SerializedValueNumberType::INT:
                return (uint64_t)vInt32;
                break;
            case SerializedValueNumberType::UINT64:
                return (uint64_t)vuInt64;
                break;
            default:
                throw LCU::Exception::SerializedValueFailure("Invalid number type [" + getReadableNumberType() + "]");
            }
        }

        bool asBool() {
            if (type != SerializedValueType::BOOL)
                throw LCU::Exception::SerializedValueFailure("Tried to get a Bool from a(n) " + getReadableType() + " [" + name + "]");

            return vBool;
        }

        // Object Manipulation
        SerializedValue& child(std::string object, bool createMissing = false) {
            if (type != SerializedValueType::OBJECT)
                throw LCU::Exception::SerializedObjectFailure("Can't get an object from a " + getReadableType() + " [" + name + "]");

            const char* delimiter = "::";
            if (object.find(delimiter) != std::string::npos) {
                SerializedValue* objChild = this;
                size_t lastDelimiterPosition = 0;
                size_t delimiterSize = strlen(delimiter);

                // Loop until all delimiters found
                while (true) {
                    size_t currDelimiterPosition = object.find(delimiter, lastDelimiterPosition + delimiterSize);
                    size_t lastDelimiterPositionEnd = (lastDelimiterPosition == 0) ? lastDelimiterPosition : lastDelimiterPosition + delimiterSize;

                    // Get object name from inbetween delimiters
                    std::string objName = (currDelimiterPosition == -1) ? object.substr(lastDelimiterPositionEnd) : object.substr(lastDelimiterPositionEnd, currDelimiterPosition - lastDelimiterPositionEnd);
                    SerializedValue* newObjPtr = objChild->child_ptr(objName);
                    
                    if (createMissing && !newObjPtr) {
                        SerializedValue newMissingObjContainer;
                        newMissingObjContainer.name = objName;
                        newMissingObjContainer.type = SerializedValueType::OBJECT;
                        objChild->vObjects.push_back(newMissingObjContainer);
                        objChild = &objChild->vObjects[objChild->vObjects.size() - 1];
                    }
                    else if (newObjPtr) {
                        objChild = newObjPtr;
                    }
                    else {
                        printf("ValuePtr == NULL! ([%s]:%s, 0x%p)\n", object.c_str(), objName.c_str(), newObjPtr);
                    }

                    lastDelimiterPosition = currDelimiterPosition;
                    if (currDelimiterPosition == std::string::npos) {
                        break;
                    }
                }
                return *objChild;
            }
            else {
                for (int i = 0; i < vObjects.size(); i++) {
                    if (vObjects[i].name == object)
                        return vObjects[i];
                }

                if (createMissing) {
                    SerializedValue newMissingObjContainer;
                    newMissingObjContainer.name = object;
                    newMissingObjContainer.type = SerializedValueType::OBJECT;
                    vObjects.push_back(newMissingObjContainer);
                    return vObjects[vObjects.size() - 1];
                }
            }
            throw LCU::Exception::SerializedObjectFailure("Object was not found.");
        }

        // Value Data
        std::string getReadable() {
            std::string objectListStr;
            switch (type) {
            case SerializedValueType::INVALID:
                return "undefined";
                break;
            case SerializedValueType::OBJECT:
                for (int i = 0; i < vObjects.size(); i++) {
                    objectListStr += vObjects[i].name;
                    if (i != vObjects.size() - 1)
                        objectListStr += ',';
                }
                return "object with " + std::to_string(vObjects.size()) + " children: [" + objectListStr + "]";
                break;
            case SerializedValueType::STRING:
                return vString;
                break;
            case SerializedValueType::NUMBER:
                return "[" + getReadableNumberType() + "] " + std::to_string(vInt32);
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
            return "([" + getReadableType() + "], " + name + "): \"" + getReadable() + '\"';
        }
        std::string getName() { return name; }
        void setName(std::string _name) { name = _name; }

        SerializedValueType& getType() { return type; }
        std::string getTypeReadable() { return getReadableType(); }

        // Converting
        std::string getJSON() {
            rapidjson::StringBuffer buffer;
            rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);

            rapidjson::Document document;
            getNativeDocument(document);
            document.Accept(writer);

            return std::string(buffer.GetString());
        }

        rapidjson::Value getNativeValue(rapidjson::Document& document) {
            rapidjson::Value value;
            rapidjson::Document::AllocatorType& allocator = document.GetAllocator();

            switch (type) {
            case SerializedValueType::OBJECT:
                value.SetObject();
                getNativeDocument(document, &value);
                break;
            case SerializedValueType::STRING:
                value.SetString(rapidjson::StringRef(vString.c_str()));
                break;
            case SerializedValueType::NUMBER:
                switch (nValType) {
                case SerializedValueNumberType::INT:
                    value.SetInt(vInt32);
                    break;
                case SerializedValueNumberType::UINT64:
                    value.SetUint64(vuInt64);
                    break;
                case SerializedValueNumberType::DOUBLE:
                    value.SetDouble(vDouble);
                    break;
                }
                break;
            case SerializedValueType::BOOL:
                value.SetBool(vBool);
                break;
            case SerializedValueType::VECTOR:
                value.SetArray();
                for (int i = 0; i < vArray.size(); i++) {
                    value.PushBack(vArray[i].getNativeValue(document), allocator);
                }
                break;
            }

            return value;
        }

        void getNativeDocument(rapidjson::Document& document, rapidjson::Value* _recursiveObject = NULL) {
            if (type != SerializedValueType::OBJECT)
                throw LCU::Exception::SerializedObjectFailure("Can't get a document from a(n) " + getReadableType());

            // Make sure document is an object
            if (document.GetType() != rapidjson::Type::kObjectType)
                document.SetObject();

            // Start work on all objects
            for (int i = 0; i < vObjects.size(); i++) {
                rapidjson::Value value = vObjects[i].getNativeValue(document);

                if (_recursiveObject == NULL) {
                    document.AddMember(
                        rapidjson::StringRef(vObjects[i].name.c_str()),
                        value,
                        document.GetAllocator()
                    );
                }
                else {
                    _recursiveObject->AddMember(
                        rapidjson::StringRef(vObjects[i].name.c_str()),
                        value,
                        document.GetAllocator()
                    );
                }
            }
        }
        ~SerializedValue() {}
    private:
        std::string name;
        union {
            int vInt32;
            bool vBool;
        };

        union {
            uint64_t vuInt64;
            double vDouble;
        };

        SerializedValueType type;
        SerializedValueNumberType nValType = SerializedValueNumberType::INT;
        std::vector<SerializedValue> vArray; // std::vector can't be in a union
        std::vector<SerializedValue> vObjects; // std::vector can't be in a union
        std::string vString; // std::string can't be in a union

        /// <summary>
        /// Get a _pointer_ to a SerializedValue child
        /// </summary>
        /// <param name="object">Child name</param>
        /// <returns>SerializedValue pointer</returns>
        SerializedValue* child_ptr(std::string object) {
            if (type != SerializedValueType::OBJECT)
                throw LCU::Exception::SerializedObjectFailure("Can't get an object from a " + getReadableType());

            for (int i = 0; i < vObjects.size(); i++) {
                if (vObjects[i].name == object)
                    return &vObjects[i];
            }
            return NULL;
        }

        /// <summary>
        /// Remove all unused values
        /// </summary>
        void clean() {
            if (type != SerializedValueType::STRING)
                vString.clear();

            if (type != SerializedValueType::VECTOR)
                vArray.clear();

            if (type != SerializedValueType::OBJECT)
                vObjects.clear();

            if (type != SerializedValueType::NUMBER) {
                vInt32 = 0;
                vDouble = 0;
                vuInt64 = 0;
            }
            else {
                switch (nValType) {
                case SerializedValueNumberType::INT:
                    vDouble = 0;
                    vuInt64 = 0;
                    break; 
                case SerializedValueNumberType::UINT64:
                    vInt32 = 0;
                    vDouble = 0;
                    break;
                case SerializedValueNumberType::DOUBLE:
                    vInt32 = 0;
                    vuInt64 = 0;
                    break;
                }
            }
        }

        std::string getReadableType() {
            std::string typeNames[(int)SerializedValueType::_MAX_] = { "undefined", "object", "string", "number", "bool", "vector" };
            return typeNames[(int)type];
        }

        std::string getReadableNumberType() {
            std::string typeNames[(int)SerializedValueNumberType::_MAX_] = { "undefined", "int", "uint64", "double" };
            return typeNames[(int)nValType];
        }
    };
}