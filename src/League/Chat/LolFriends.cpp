#include "LolFriends.h"

/// <summary>
/// Get a list of friends as a LolChatFriendResource vector.
/// </summary>
/// <param name="session">Pointer to a Session object.</param>
/// <returns>LolChatFriendResource vector</returns>
std::vector<LCU::League::Class::Chat::LolChatFriendResource> LCU::League::Chat::Friends::GetFriends(Session* session)
{
	// Parse response
	rapidjson::Document responseNative;
	responseNative.Parse(LCU::Network::HTTP::Get(session, "lol-chat/v1/friends").c_str());
	LCU::SerializedValue responseLayered(responseNative);

	// Turn response to object
	std::vector<LCU::League::Class::Chat::LolChatFriendResource> object;

	for (auto& item : responseLayered.asVector()) {
		Class::Chat::LolChatFriendResource user;
		user.init(item);
		object.push_back(user);
	}

	return object;
}