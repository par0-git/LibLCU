/*
    LibLCU,
    2020 - par0-git
    Class / LolLootPlayerLoot << LolBaseClass
*/

#pragma once
#include "../LolClass.h"
#include "LolLootItemOwnershipStatus.h"
#include "LolLootRedeemableStatus.h"

namespace LCU {
    namespace League {
        namespace Class {
            namespace Loot {
                class LolLootPlayerLoot : public LolBaseClass {
                public:
                    std::string lootName,
                        lootId,
                        refId,
                        localizedName, 
                        localizedDescription,
                        itemDesc,
                        displayCategories,
                        rarity,
                        tags,
                        type,
                        asset,
                        tilePath,
                        splashPath,
                        shadowPath,
                        upgradeLootName,
                        upgradeEssenceName,
                        disenchantLootName,
                        localizedRecipeTitle,
                        localizedRecipeSubtitle;
                    
                    LolLootItemOwnershipStatus itemStatus, parentItemStatus;
                    LolLootRedeemableStatus redeemableStatus;

                    int count,
                        rentalGames,
                        storeItemId,
                        parentStoreItemId,
                        value,
                        upgradeEssenceValue,
                        disenchantValue;

                    int64_t expiryTime,
                        rentalSeconds;

                    bool isNew,
                        isRental;

                    std::vector<SerializedObjectValue> getSerializationData() {
                        return {
                            {SerializedValueType::STRING, "lootName", &lootName},
                            {SerializedValueType::STRING, "lootId", &lootId},
                            {SerializedValueType::STRING, "refId", &refId},
                            {SerializedValueType::STRING, "localizedName", &localizedName},
                            {SerializedValueType::STRING, "localizedDescription", &localizedDescription},
                            {SerializedValueType::STRING, "itemDesc", &itemDesc},
                            {SerializedValueType::STRING, "displayCategories", &displayCategories},
                            {SerializedValueType::STRING, "rarity", &rarity},
                            {SerializedValueType::STRING, "tags", &tags},
                            {SerializedValueType::STRING, "type", &type},
                            {SerializedValueType::STRING, "asset", &asset},
                            {SerializedValueType::STRING, "tilePath", &tilePath},
                            {SerializedValueType::STRING, "splashPath", &splashPath},
                            {SerializedValueType::STRING, "shadowPath", &shadowPath},
                            {SerializedValueType::STRING, "upgradeLootName", &upgradeLootName},
                            {SerializedValueType::STRING, "upgradeEssenceName", &upgradeEssenceName},
                            {SerializedValueType::STRING, "disenchantLootName", &disenchantLootName},
                            {SerializedValueType::STRING, "localizedRecipeTitle", &localizedRecipeTitle},
                            {SerializedValueType::STRING, "localizedRecipeSubtitle", &localizedRecipeSubtitle},

                            //{SerializedValueType::NUMBER, "itemStatus", &itemStatus},
                            //{SerializedValueType::NUMBER, "parentItemStatus", &parentItemStatus},
                            //{SerializedValueType::NUMBER, "redeemableStatus", &redeemableStatus},

                            {SerializedValueType::NUMBER, "count", &count},
                            {SerializedValueType::NUMBER, "rentalGames", &rentalGames},
                            {SerializedValueType::NUMBER, "storeItemId", &storeItemId},
                            {SerializedValueType::NUMBER, "parentStoreItemId", &parentStoreItemId},
                            {SerializedValueType::NUMBER, "value", &value},
                            {SerializedValueType::NUMBER, "upgradeEssenceValue", &upgradeEssenceValue},
                            {SerializedValueType::NUMBER, "disenchantValue", &disenchantValue},

                            {SerializedValueType::BOOL, "isNew", &isNew},
                            {SerializedValueType::BOOL, "isRental", &isRental},
                        };
                    }

                    const char* getClassReadableName() {
                        return "LolLootPlayerLoot";
                    }
                };
            }
        }
    }
};