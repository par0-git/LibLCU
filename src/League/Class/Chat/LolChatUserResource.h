/*
    LibLCU,
    2020 - par0-git
    Class / LolChatUserResource << LolBaseClass
*/

#pragma once
#include "../LolClass.h"

namespace LCU {
    namespace League {
        namespace Class {
            namespace Chat {
                class LolChatUserResource : public LolBaseClass {
                public:
                    uint64_t summonerId;
                    std::string id;
                    std::string name;
                    std::string pid;
                    std::string puuid;
                    std::string gameName;
                    std::string gameTag;
                    int icon;
                    std::string availability;
                    std::string platformId;
                    std::string patchline;
                    std::string product;
                    std::string productName;
                    std::string summary;
                    uint64_t time;
                    std::string statusMessage;

                    std::vector<SerializedObjectValue> getSerializationData() {
                        return {
                            {SerializedValueType::NUMBER, "summonerId", &summonerId},
                            {SerializedValueType::STRING, "id", &id},
                            {SerializedValueType::STRING, "name", &name},
                            {SerializedValueType::STRING, "pid", &pid},
                            {SerializedValueType::STRING, "puuid", &puuid},
                            {SerializedValueType::STRING, "gameName", &gameName},
                            {SerializedValueType::STRING, "gameTag", &gameTag},
                            {SerializedValueType::NUMBER, "icon", &icon},
                            {SerializedValueType::STRING, "availability", &availability},
                            {SerializedValueType::STRING, "platformId", &platformId},
                            {SerializedValueType::STRING, "patchline", &patchline},
                            {SerializedValueType::STRING, "product", &product},
                            {SerializedValueType::STRING, "productName", &productName},
                            {SerializedValueType::STRING, "summary", &summary},
                            {SerializedValueType::NUMBER, "time", &time},
                            {SerializedValueType::STRING, "statusMessage", &statusMessage},
                        };
                    }

                    const char* getClassReadableName() {
                        return "LolChatUserResource";
                    }
                };
            }
        }
    }
};