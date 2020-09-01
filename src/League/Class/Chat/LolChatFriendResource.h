#pragma once
#include "LolChatUserResource.h"

namespace LCU {
    namespace League {
        namespace Class {
            namespace Chat {
                class LolChatFriendResource : public LolChatUserResource {
                public:
                    bool isP2PConversationMuted;
                    unsigned int groupId;
                    unsigned int displayGroupId;
                    std::string groupName;
                    std::string displayGroupName;

                    static void FromJSON(LolChatFriendResource& user, nlohmann::json input) {
                        // Parent class FromJSON
                        LolChatUserResource::FromJSON(user, input);

                        try JSON_CLASS_BEGIN(input, user);
                            JSON_TO_CLASS_MEMBER(["isP2PConversationMuted"], isP2PConversationMuted);
                            JSON_TO_CLASS_MEMBER(["groupId"], groupId);
                            JSON_TO_CLASS_MEMBER(["displayGroupId"], displayGroupId);
                            JSON_TO_CLASS_MEMBER(["groupName"], groupName);
                            JSON_TO_CLASS_MEMBER(["displayGroupName"], displayGroupName);
                        JSON_CLASS_END() catch (std::exception& e) {
                            LCU::Log::Out(LCU::Log::LogLevel::ERR, LCU::Log::LogActivity::CLASS_CREATION, "Failed to create a LolChatFriendResource class. (%s)", e.what());
                        };
                    }

                    nlohmann::json ToJSON() {
                        return LCFR_ToBaseJSON();
                    }

                    nlohmann::json LCFR_ToBaseJSON() {
                        nlohmann::json output = LCUR_ToBaseJSON();

                        try JSON_CLASS_BEGIN(output, *this);
                            JSON_FROM_CLASS_MEMBER(["isP2PConversationMuted"], isP2PConversationMuted);
                            JSON_FROM_CLASS_MEMBER(["groupId"], groupId);
                            JSON_FROM_CLASS_MEMBER(["displayGroupId"], displayGroupId);
                            JSON_FROM_CLASS_MEMBER(["groupName"], groupName);
                            JSON_FROM_CLASS_MEMBER(["displayGroupName"], displayGroupName);
                        JSON_CLASS_END() catch (std::exception& e) {
                            LCU::Log::Out(LCU::Log::LogLevel::ERR, LCU::Log::LogActivity::CLASS_CREATION, "Failed to create a LolChatFriendResource json. (%s)", e.what());
                        };
                        return output;
                    }
                };
            }
        }
    }
};