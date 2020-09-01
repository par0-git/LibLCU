#include "LolChat.h"

/// <summary>
/// Get a LolChatUserResource for the signed-in user.
/// </summary>
/// <param name="session">Pointer to a Session object.</param>
/// <returns>LolChatUserResource</returns>
LCU::League::Class::Chat::LolChatUserResource LCU::League::Chat::GetMe(Session* session)
{
	nlohmann::json jsonObject = nlohmann::json::parse(LCU::Network::HTTP::Get(session, "lol-chat/v1/me"));

	Class::Chat::LolChatUserResource out;
	Class::Chat::LolChatUserResource::FromJSON(out, jsonObject);
	return out;
}

/// <summary>
/// Set the signed-in user to a LolChatUserResource.
/// </summary>
/// <param name="session">Pointer to a Session object.</param>
/// <param name="user">LolChatUserResource to use.</param>
void LCU::League::Chat::SetMe(Session* session, LCU::League::Class::Chat::LolChatUserResource user)
{
	LCU::Network::HTTP::Put(session, "lol-chat/v1/me", user.ToJSON().dump());
}
