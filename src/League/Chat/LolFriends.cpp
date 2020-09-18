#include "LolFriends.h"

/// <summary>
/// Get a list of friends as a LolChatFriendResource vector.
/// </summary>
/// <param name="session">Pointer to a Session object.</param>
/// <returns>LolChatFriendResource vector</returns>
std::vector<LCU::League::Class::Chat::LolChatFriendResource> LCU::League::Chat::Friends::GetFriends(Session* session)
{
	std::basic_string<unsigned char> response = LCU::Network::HTTP::Get(session, "lol-chat/v1/friends");
	std::vector<LCU::League::Class::Chat::LolChatFriendResource> friends;

	for (auto& item : nlohmann::json::parse(response).items()) {
		Class::Chat::LolChatFriendResource user;
		Class::Chat::LolChatFriendResource::FromJSON(user, item.value());
		friends.push_back(user);
	}

	return friends;
}