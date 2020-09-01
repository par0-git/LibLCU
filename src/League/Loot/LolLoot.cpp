#include "LolLoot.h"

/// <summary>
/// Get a list of player loot as a LolLootPlayerLoot vector.
/// </summary>
/// <param name="session">Pointer to a Session object.</param>
/// <returns>LolLootPlayerLoot vector</returns>
std::vector <LCU::League::Class::Loot::LolLootPlayerLoot> LCU::League::Loot::GetPlayerLoot(Session* session)
{
	nlohmann::json jsonObject = nlohmann::json::parse(LCU::Network::HTTP::Get(session, "lol-loot/v1/player-loot"));
	std::vector<LCU::League::Class::Loot::LolLootPlayerLoot> out;

	for (auto& item : jsonObject.items()) {
		LCU::League::Class::Loot::LolLootPlayerLoot lootObject;
		LCU::League::Class::Loot::LolLootPlayerLoot::FromJSON(lootObject, item.value());
		out.push_back(lootObject);
	}

	return out;
}
