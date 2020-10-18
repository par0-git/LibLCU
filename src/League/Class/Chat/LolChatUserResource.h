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
                    using LolBaseClass::LolBaseClass;

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
                    std::string lastSeenOnlineTimestamp;

                    std::vector<SerializedObjectValue> GetSerializationData() {
                        return {
                            {SerializedObjectValueType::NUMBER, "summonerId", &summonerId},
                            {SerializedObjectValueType::STRING, "id", &id},
                            {SerializedObjectValueType::STRING, "name", &name},
                            {SerializedObjectValueType::STRING, "pid", &pid},
                            {SerializedObjectValueType::STRING, "puuid", &puuid},
                            {SerializedObjectValueType::STRING, "gameName", &gameName},
                            {SerializedObjectValueType::STRING, "gameTag", &gameTag},
                            {SerializedObjectValueType::NUMBER, "icon", &icon},
                            {SerializedObjectValueType::STRING, "availability", &availability},
                            {SerializedObjectValueType::STRING, "platformId", &platformId},
                            {SerializedObjectValueType::STRING, "patchline", &patchline},
                            {SerializedObjectValueType::STRING, "product", &product},
                            {SerializedObjectValueType::STRING, "productName", &productName},
                            {SerializedObjectValueType::STRING, "summary", &summary},
                            {SerializedObjectValueType::NUMBER, "time", &time},
                            {SerializedObjectValueType::STRING, "statusMessage", &statusMessage},
                            {SerializedObjectValueType::STRING, "lastSeenOnlineTimestamp", &lastSeenOnlineTimestamp},
                        };
                    }

                    static void FromJSON(LolChatUserResource& user, nlohmann::json input) {
                        try JSON_CLASS_BEGIN(input, user);
                            JSON_TO_CLASS_MEMBER(["summonerId"], summonerId);
                            JSON_TO_CLASS_MEMBER(["id"], id);
                            JSON_TO_CLASS_MEMBER(["name"], name);
                            JSON_TO_CLASS_MEMBER(["pid"], pid);
                            JSON_TO_CLASS_MEMBER(["puuid"], puuid);
                            JSON_TO_CLASS_MEMBER(["gameName"], gameName);
                            JSON_TO_CLASS_MEMBER(["gameTag"], gameTag);
                            JSON_TO_CLASS_MEMBER(["icon"], icon);
                            JSON_TO_CLASS_MEMBER(["availability"], availability);
                            JSON_TO_CLASS_MEMBER(["platformId"], platformId);
                            JSON_TO_CLASS_MEMBER(["patchline"], patchline);
                            JSON_TO_CLASS_MEMBER(["product"], product);
                            JSON_TO_CLASS_MEMBER(["productName"], productName);
                            JSON_TO_CLASS_MEMBER(["summary"], summary);
                            JSON_TO_CLASS_MEMBER(["time"], time);
                            JSON_TO_CLASS_MEMBER(["statusMessage"], statusMessage);
                            JSON_TO_CLASS_MEMBER(["lastSeenOnlineTimestamp"], lastSeenOnlineTimestamp);
                        JSON_CLASS_END() catch (std::exception& e) {
                            LCU::Log::Out(LCU::Log::LogLevel::ERR, LCU::Log::LogActivity::CLASS_CREATION, "Failed to create a %s class. (%s)", user.GetClassReadableName(), e.what());
                        };
                    }
                    
                    nlohmann::json ToJSON() {
                        nlohmann::json output;
                        try JSON_CLASS_BEGIN(output, *this);
                            JSON_FROM_CLASS_MEMBER(["summonerId"], summonerId);
                            JSON_FROM_CLASS_MEMBER(["id"], id);
                            JSON_FROM_CLASS_MEMBER(["name"], name);
                            JSON_FROM_CLASS_MEMBER(["pid"], pid);
                            JSON_FROM_CLASS_MEMBER(["puuid"], puuid);
                            JSON_FROM_CLASS_MEMBER(["gameName"], gameName);
                            JSON_FROM_CLASS_MEMBER(["gameTag"], gameTag);
                            JSON_FROM_CLASS_MEMBER(["icon"], icon);
                            JSON_FROM_CLASS_MEMBER(["availability"], availability);
                            JSON_FROM_CLASS_MEMBER(["platformId"], platformId);
                            JSON_FROM_CLASS_MEMBER(["patchline"], patchline);
                            JSON_FROM_CLASS_MEMBER(["product"], product);
                            JSON_FROM_CLASS_MEMBER(["productName"], productName);
                            JSON_FROM_CLASS_MEMBER(["summary"], summary);
                            JSON_FROM_CLASS_MEMBER(["time"], time);
                            JSON_FROM_CLASS_MEMBER(["statusMessage"], statusMessage);
                            JSON_FROM_CLASS_MEMBER(["lastSeenOnlineTimestamp"], lastSeenOnlineTimestamp);
                        JSON_CLASS_END() catch (std::exception& e) {
                            LCU::Log::Out(LCU::Log::LogLevel::ERR, LCU::Log::LogActivity::CLASS_CREATION, "Failed to create a %s json object. (%s)", GetClassReadableName(), e.what());
                        };
                        return output;
                    }

                    const char* GetClassReadableName() {
                        return "LolChatUserResource";
                    }
                };
            }
        }
    }
};