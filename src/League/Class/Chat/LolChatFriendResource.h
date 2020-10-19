/*
    LibLCU,
    2020 - par0-git
    Class / LolChatFriendResource << LolChatUserResource << LolBaseClass
*/

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
                    std::vector<SerializedValue> testVector;

                    std::vector<SerializedObjectValue> getSerializationData() {
                        return {
                            {SerializedValueType::BOOL, "isP2PConversationMuted", &isP2PConversationMuted},
                            {SerializedValueType::NUMBER, "groupId", &groupId},
                            {SerializedValueType::NUMBER, "displayGroupId", &displayGroupId},
                            {SerializedValueType::STRING, "groupName", &groupName},
                            {SerializedValueType::STRING, "displayGroupName", &displayGroupName},
                            {SerializedValueType::VECTOR, "testVector", &testVector},
                        };
                    }

                    const char* getClassReadableName() {
                        return "LolChatFriendResource";
                    }
                };
            }
        }
    }
};