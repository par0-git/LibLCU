#include "LolChat.h"

/// <summary>
/// Get a LolChatUserResource for the signed-in user.
/// </summary>
/// <param name="session">Pointer to a Session object.</param>
/// <returns>LolChatUserResource</returns>
LCU::League::Class::Chat::LolChatUserResource LCU::League::Chat::GetMe(Session* session)
{
	// Parse response
	rapidjson::Document responseNative;
	responseNative.Parse(LCU::Network::HTTP::Get(session, "lol-chat/v1/me").c_str());
	LCU::SerializedValue responseLayered(responseNative);

	// Turn response to object
	Class::Chat::LolChatUserResource object;
	object.init(responseLayered);

	return object;
}

/// <summary>
/// Set the signed-in user to a LolChatUserResource.
/// </summary>
/// <param name="session">Pointer to a Session object.</param>
/// <param name="user">LolChatUserResource to use.</param>
void LCU::League::Chat::SetMe(Session* session, LCU::League::Class::Chat::LolChatUserResource user)
{
	std::cout << user.statusMessage << ":: s\n";
	LCU::Network::HTTP::Put(session, "lol-chat/v1/me", user.serialize().getJSON());
}
