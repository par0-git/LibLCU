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

                void init(SerializedValue& baseValue) {
                    std::vector<SerializedObjectValue> sData = getSerializationData();

                    for (SerializedObjectValue sObjectValue : sData) {
                        try {
                            SerializedValue& childValue = baseValue.Child(sObjectValue.src);
                            std::string cc;
                            switch (sObjectValue.type) {
                            case LCU::SerializedValueType::INVALID:
                                sObjectValue.ptr = NULL;
                                break;
                            case LCU::SerializedValueType::OBJECT:
                                *(SerializedValue*)sObjectValue.ptr = childValue; // This most likely won't work!
                                break;
                            case LCU::SerializedValueType::STRING:
                                *(std::string*)sObjectValue.ptr = childValue.String();
                                break;
                            case LCU::SerializedValueType::NUMBER:
                                *(int*)sObjectValue.ptr = childValue.Int();
                                break;
                            case LCU::SerializedValueType::BOOL:
                                *(bool*)sObjectValue.ptr = childValue.Bool();
                                break;
                            case LCU::SerializedValueType::VECTOR:
                                *(std::vector<SerializedValue>*)sObjectValue.ptr = childValue.Vector();
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

                            throw LCU::Exception::SerializedObjectFailure(e.reason());
                        }
                    }
                }

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