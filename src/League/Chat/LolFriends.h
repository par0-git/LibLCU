#pragma once
#include "../../Session/Session.hpp"
#include "../Class/Chat/LolChatFriendResource.h"

namespace LCU {
    namespace League {
        namespace Chat {
            namespace Friends {
                std::vector<Class::Chat::LolChatFriendResource> GetFriends(Session* session);
            }
        }
    }
};
