/*
    LibLCU,
    2020 - par0-git
    Class / LolBaseClass

    This class is the parent of all the class definitions.
*/

#pragma once
#include "../../Objects/SerializationBasedObjectCreator.h"
#include <string>
#include <vector>
#include "../../Output/Logging.hpp"
#include "../../Network/HTTP/HTTP.hpp"

namespace LCU {
    namespace League {
        namespace Class {
            // Object base class
            class LolBaseClass {
            public:
                virtual const char* getClassReadableName() = 0;
                virtual std::vector<SerializedObjectValue> getSerializationData() = 0;

                LolBaseClass() {};

                /// <summary>
                /// Create the class from a serialized value.
                /// </summary>
                /// <param name="baseValue">SerializedValue</param>
                void init(SerializedValue& baseValue) {
                    std::vector<SerializedObjectValue> sData = getSerializationData();
                    for (SerializedObjectValue sObjectValue : sData) {
                        try {
                            SerializedValue& childValue = baseValue.child(sObjectValue.src);

                            switch (sObjectValue.type) {
                            case LCU::SerializedValueType::INVALID:
                                sObjectValue.ptr = NULL;
                                break;
                            case LCU::SerializedValueType::OBJECT:
                                *(SerializedValue*)sObjectValue.ptr = childValue; // This most likely won't work!
                                break;
                            case LCU::SerializedValueType::STRING:
                                *(std::string*)sObjectValue.ptr = childValue.asString();
                                break;
                            case LCU::SerializedValueType::NUMBER:
                                *(int*)sObjectValue.ptr = childValue.asInt();
                                break;
                            case LCU::SerializedValueType::BOOL:
                                *(bool*)sObjectValue.ptr = childValue.asBool();
                                break;
                            case LCU::SerializedValueType::VECTOR:
                                *(std::vector<SerializedValue>*)sObjectValue.ptr = childValue.asVector();
                                break;
                            default:
                                sObjectValue.ptr = NULL;
                            };
                        }
                        catch (LCU::Exception::SerializedObjectFailure& e) {
                            // No object found from src
                            LCU::Log::Out(
                                LCU::Log::LogLevel::ERR,
                                LCU::Log::LogActivity::CLASS_CREATION,
                                "Could not create the object for %s. The child %s did not exist.",
                                getClassReadableName(),
                                sObjectValue.src
                            );

                            //throw LCU::Exception::SerializedObjectFailure(e.reason());
                        }
                    }
                }

                /// <summary>
                /// Serialize the class.
                /// </summary>
                /// <returns>SerializedValue</returns>
                SerializedValue serialize() {
                    std::vector<SerializedObjectValue> sData = getSerializationData();
                    SerializedValue sOutput = SerializedValue(SerializedValueType::OBJECT);

                    for (SerializedObjectValue sObjectValue : sData) {
                        // Get child and create if it doesn't exist
                        SerializedValue& childValue = sOutput.child(sObjectValue.src, true);

                        // Set child value
                        switch (sObjectValue.type) {
                        case LCU::SerializedValueType::INVALID:
                            childValue = SerializedValueType::INVALID;
                            break;
                        case LCU::SerializedValueType::OBJECT:
                            childValue = *(SerializedValue*)sObjectValue.ptr; // This most likely won't work!
                            break;
                        case LCU::SerializedValueType::STRING:
                            childValue = (*(std::string*)sObjectValue.ptr);
                            break;
                        case LCU::SerializedValueType::NUMBER:
                            childValue = (*(int*)sObjectValue.ptr);
                            break;
                        case LCU::SerializedValueType::BOOL:
                            childValue = (*(bool*)sObjectValue.ptr);
                            break;
                        case LCU::SerializedValueType::VECTOR:
                            childValue = (*(std::vector<SerializedValue>*)sObjectValue.ptr);
                            break;
                        default:
                            sObjectValue.ptr = NULL;
                        };
                    }
                    return sOutput;
                }

                /// <summary>
                /// Return a pretty string with info about the class.
                /// </summary>
                /// <returns>Pretty string.</returns>
                std::string pretty() {
                    std::vector<SerializedObjectValue> sData = getSerializationData();
                    std::string typeNames[(int)SerializedValueType::_MAX_] = { "undefined", "object", "string", "number", "bool", "vector" };
                    std::string output;

                    // Char arrays
                    char classInfoString[256];
                    char classMemberString[128];

                    // Get pretty class name and address
                    int classInfoSize = snprintf(classInfoString, 256, "{%s} (0x%p)\n", 
                        getClassReadableName(), 
                        this);

                    // Add class name and address to output string
                    output += classInfoString;

                    for (SerializedObjectValue sObjectValue : sData) {
                        // Get pretty member information
                        int classMemberSize = snprintf(classMemberString, 128, "\t[%s](%s)(0x%p)\n", 
                            sObjectValue.src, 
                            typeNames[(int)sObjectValue.type].c_str(), 
                            sObjectValue.ptr);

                        // Add member information to string
                        output += classMemberString;
                    }

                    // Return string
                    return output;
                }
            };
        }
    }
};