#include "LolFriends.h"

/// <summary>
/// Get a list of friends as a LolChatFriendResource vector.
/// </summary>
/// <param name="session">Pointer to a Session object.</param>
/// <returns>LolChatFriendResource vector</returns>
std::vector<LCU::League::Class::Chat::LolChatFriendResource> LCU::League::Chat::Friends::GetFriends(Session* session)
{
	nlohmann::json jsonObject = nlohmann::json::parse(LCU::Network::HTTP::Get(session, "lol-chat/v1/friends"));
	std::vector<LCU::League::Class::Chat::LolChatFriendResource> out;

	for (auto& item : jsonObject.items()) {
		Class::Chat::LolChatFriendResource chatFriendResource;
		Class::Chat::LolChatFriendResource::FromJSON(chatFriendResource, item.value());
		out.push_back(chatFriendResource);
	}

	return out;
}