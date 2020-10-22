#include "LolLoot.h"

/// <summary>
/// Get a list of player loot as a LolLootPlayerLoot vector.
/// </summary>
/// <param name="session">Pointer to a Session object.</param>
/// <returns>LolLootPlayerLoot vector</returns>
std::vector <LCU::League::Class::Loot::LolLootPlayerLoot> LCU::League::Loot::GetPlayerLoot(Session* session)
{
	// Parse response
	rapidjson::Document responseNative;
	responseNative.Parse(LCU::Network::HTTP::Get(session, "lol-loot/v1/player-loot").c_str());
	LCU::SerializedValue responseLayered(responseNative);

	// Turn response to object
	std::vector<LCU::League::Class::Loot::LolLootPlayerLoot> object;

	for (auto& item : responseLayered.asVector()) {
		LCU::League::Class::Loot::LolLootPlayerLoot loot;
		loot.init(item);
		object.push_back(loot);
	}

	return object;
}
