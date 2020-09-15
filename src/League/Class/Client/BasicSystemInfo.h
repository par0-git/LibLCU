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

                    static void FromJSON(BasicSystemInfo& info, nlohmann::json input) {
                        try JSON_CLASS_BEGIN(input, info);
                            JSON_TO_CLASS_MEMBER(["operatingSystem"]["edition"], operatingSystem.edition);
                            JSON_TO_CLASS_MEMBER(["operatingSystem"]["platform"], operatingSystem.platform);
                            JSON_TO_CLASS_MEMBER(["operatingSystem"]["versionMajor"], operatingSystem.versionMajor);
                            JSON_TO_CLASS_MEMBER(["operatingSystem"]["versionMinor"], operatingSystem.versionMinor);
                            JSON_TO_CLASS_MEMBER(["physicalMemory"], physicalMemory);
                            JSON_TO_CLASS_MEMBER(["physicalProcessorCores"], physicalProcessorCores);
                            JSON_TO_CLASS_MEMBER(["processorSpeed"], processorSpeed);
                        JSON_CLASS_END() catch (std::exception& e) {
                            LCU::Log::Out(LCU::Log::LogLevel::ERR, LCU::Log::LogActivity::CLASS_CREATION, "Failed to create a %s class. (%s)", info.GetClassReadableName(), e.what());
                        };
                    }

                    nlohmann::json ToJSON() {
                        nlohmann::json output;
                        try JSON_CLASS_BEGIN(output, *this);
                            JSON_FROM_CLASS_MEMBER(["operatingSystem"]["edition"], operatingSystem.edition);
                            JSON_FROM_CLASS_MEMBER(["operatingSystem"]["platform"], operatingSystem.platform);
                            JSON_FROM_CLASS_MEMBER(["operatingSystem"]["versionMajor"], operatingSystem.versionMajor);
                            JSON_FROM_CLASS_MEMBER(["operatingSystem"]["versionMinor"], operatingSystem.versionMinor);
                            JSON_FROM_CLASS_MEMBER(["physicalMemory"], physicalMemory);
                            JSON_FROM_CLASS_MEMBER(["physicalProcessorCores"], physicalProcessorCores);
                            JSON_FROM_CLASS_MEMBER(["processorSpeed"], processorSpeed);
                        JSON_CLASS_END() catch (std::exception& e) {
                            LCU::Log::Out(LCU::Log::LogLevel::ERR, LCU::Log::LogActivity::CLASS_CREATION, "Failed to create a %s json object. (%s)", GetClassReadableName(), e.what());
                        };
                        return output;
                    }

                    const char* GetClassReadableName() {
                        return "BasicSystemInfo";
                    }
                };
            }
        }
    }
}