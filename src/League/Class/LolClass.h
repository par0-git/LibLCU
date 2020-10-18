/*
    LibLCU,
    2020 - par0-git
    Class / LolBaseClass

    This class is the parent of all the class definitions.
*/

#pragma once
#include "../../Objects/SerializationBasedObjectCreator.h"
#include <nlohmann/json.hpp>
#include <string>
#include <vector>
#include "../../Output/Logging.hpp"
#include "../../Network/HTTP/HTTP.hpp"

// Begin a scope for managing a JSON Object<->C++ Class transfer.
#define JSON_CLASS_BEGIN(input, output) { nlohmann::json& _json_input_ = input; decltype(output)& _class_output_ = output;

#define JSON_CLASS_BEGIN_SAFE(input, output) try { nlohmann::json& _json_input_ = input; decltype(output)& _class_output_ = output;

// Copy a variable to / from a JSON object.
#define JSON_TO_CLASS_MEMBER(json_member, class_member) _class_output_.class_member = _json_input_ json_member.get<decltype(_class_output_.class_member)>();
#define JSON_FROM_CLASS_MEMBER(json_member, class_member) _json_input_ json_member = _class_output_.class_member;

// End a scope for managing a JSON Object<->C++ Class transfer.
#define JSON_CLASS_END() }

namespace LCU {
    namespace League {
        namespace Class {
            // Object base class
            class LolBaseClass {
            public:
                virtual const char* GetClassReadableName() = 0;
                virtual std::vector<SerializedObjectValue> GetSerializationData() = 0;

                LolBaseClass() {};

                LolBaseClass(SerializedValue& baseValue) {
                    std::vector<SerializedObjectValue> sData = GetSerializationData();
                    for (SerializedObjectValue sObjectValue : sData) {
                        try {

                            SerializedValue& childValue = baseValue.Child(sObjectValue.src);
                            switch (sObjectValue.type) {
                            case LCU::SerializedObjectValueType::INVALID:
                                sObjectValue.ptr = NULL;
                                break;
                            case LCU::SerializedObjectValueType::OBJECT:
                                *(SerializedValue*)sObjectValue.ptr = childValue; // This most likely won't work!
                                break;
                            case LCU::SerializedObjectValueType::STRING:
                                *(std::string*)sObjectValue.ptr = childValue.String();
                                break;
                            case LCU::SerializedObjectValueType::NUMBER:
                                *(int*)sObjectValue.ptr = childValue.Int();
                                break;
                            case LCU::SerializedObjectValueType::BOOL:
                                *(bool*)sObjectValue.ptr = childValue.Bool();
                                break;
                            case LCU::SerializedObjectValueType::VECTOR:
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
                                GetClassReadableName(),
                                sObjectValue.src
                            );

                            throw LCU::Exception::SerializedObjectFailure(e.reason());
                        }
                    }
                }
            };
        }
    }
};