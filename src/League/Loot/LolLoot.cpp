#include "LolLoot.h"

/// <summary>
/// Get a list of player loot as a LolLootPlayerLoot vector.
/// </summary>
/// <param name="session">Pointer to a Session object.</param>
/// <returns>LolLootPlayerLoot vector</returns>
std::vector <LCU::League::Class::Loot::LolLootPlayerLoot> LCU::League::Loot::GetPlayerLoot(Session* session)
{
	std::basic_string<unsigned char> response = LCU::Network::HTTP::Get(session, "lol-loot/v1/player-loot");
	std::vector<LCU::League::Class::Loot::LolLootPlayerLoot> loot;

	/*for (auto& item : nlohmann::json::parse(response).items()) {
		LCU::League::Class::Loot::LolLootPlayerLoot object;
		LCU::League::Class::Loot::LolLootPlayerLoot::FromJSON(object, item.value());
		loot.push_back(object);
	}*/

	return loot;
}
