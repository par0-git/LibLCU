/*
    LibLCU,
    2020 - par0-git
    Class / BasicSystemInfo
*/

#pragma once
#include "../LolClass.h"

namespace LCU {
    namespace League {
        namespace Class {
            namespace Client {
                struct BasicOperatingSystem {
                    std::string edition, platform, versionMajor, versionMinor;
                };
                
                class BasicSystemInfo : public LolBaseClass {
                public:
                    BasicOperatingSystem operatingSystem;
                    int physicalMemory, physicalProcessorCores, processorSpeed;

                    std::vector<SerializedObjectValue> getSerializationData() {
                        return {
                            {SerializedValueType::STRING, "operatingSystem::edition", &operatingSystem.edition},
                            {SerializedValueType::STRING, "operatingSystem::platform", &operatingSystem.platform},
                            {SerializedValueType::STRING, "operatingSystem::versionMajor", &operatingSystem.versionMajor},
                            {SerializedValueType::STRING, "operatingSystem::versionMinor", &operatingSystem.versionMinor},
                            {SerializedValueType::NUMBER, "physicalMemory", &physicalMemory},
                            {SerializedValueType::NUMBER, "physicalProcessorCores", &physicalProcessorCores},
                            {SerializedValueType::NUMBER, "processorSpeed", &processorSpeed},
                        };
                    }

                    const char* getClassReadableName() {
                        return "BasicSystemInfo";
                    }
                };
            }
        }
    }
}