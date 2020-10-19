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