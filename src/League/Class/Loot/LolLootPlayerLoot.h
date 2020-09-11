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

                    static void FromJSON(LolLootPlayerLoot& item, nlohmann::json input) {
                        try JSON_CLASS_BEGIN(input, item);
                            JSON_TO_CLASS_MEMBER(["lootName"], lootName);
                            JSON_TO_CLASS_MEMBER(["lootId"], lootId);
                            JSON_TO_CLASS_MEMBER(["refId"], refId);
                            JSON_TO_CLASS_MEMBER(["localizedName"], localizedName);
                            JSON_TO_CLASS_MEMBER(["localizedDescription"], localizedDescription);
                            JSON_TO_CLASS_MEMBER(["itemDesc"], itemDesc);
                            JSON_TO_CLASS_MEMBER(["displayCategories"], displayCategories);
                            JSON_TO_CLASS_MEMBER(["rarity"], rarity);
                            JSON_TO_CLASS_MEMBER(["tags"], tags);
                            JSON_TO_CLASS_MEMBER(["type"], type);
                            JSON_TO_CLASS_MEMBER(["asset"], asset);
                            JSON_TO_CLASS_MEMBER(["tilePath"], tilePath);
                            JSON_TO_CLASS_MEMBER(["splashPath"], splashPath);
                            JSON_TO_CLASS_MEMBER(["shadowPath"], shadowPath);
                            JSON_TO_CLASS_MEMBER(["upgradeLootName"], upgradeLootName);
                            JSON_TO_CLASS_MEMBER(["upgradeEssenceName"], upgradeEssenceName);
                            JSON_TO_CLASS_MEMBER(["disenchantLootName"], disenchantLootName);
                            JSON_TO_CLASS_MEMBER(["localizedRecipeTitle"], localizedRecipeTitle);
                            JSON_TO_CLASS_MEMBER(["localizedRecipeSubtitle"], localizedRecipeSubtitle);
                            JSON_TO_CLASS_MEMBER(["itemStatus"], itemStatus);
                            JSON_TO_CLASS_MEMBER(["parentItemStatus"], parentItemStatus);
                            JSON_TO_CLASS_MEMBER(["redeemableStatus"], redeemableStatus);
                            JSON_TO_CLASS_MEMBER(["count"], count);
                            JSON_TO_CLASS_MEMBER(["rentalGames"], rentalGames);
                            JSON_TO_CLASS_MEMBER(["storeItemId"], storeItemId);
                            JSON_TO_CLASS_MEMBER(["parentStoreItemId"], parentStoreItemId);
                            JSON_TO_CLASS_MEMBER(["value"], value);
                            JSON_TO_CLASS_MEMBER(["upgradeEssenceValue"], upgradeEssenceValue);
                            JSON_TO_CLASS_MEMBER(["disenchantValue"], disenchantValue);
                            JSON_TO_CLASS_MEMBER(["expiryTime"], expiryTime);
                            JSON_TO_CLASS_MEMBER(["rentalSeconds"], rentalSeconds);
                            JSON_TO_CLASS_MEMBER(["isNew"], isNew);
                            JSON_TO_CLASS_MEMBER(["isRental"], isRental);
                        JSON_CLASS_END() catch (std::exception& e) {
                            LCU::Log::Out(LCU::Log::LogLevel::ERR, LCU::Log::LogActivity::CLASS_CREATION, "Failed to create a %s class. (%s)", item.GetClassName(), e.what());
                        };
                    }

                    nlohmann::json ToJSON() {
                        nlohmann::json output;
                        try JSON_CLASS_BEGIN(output, *this);
                            JSON_FROM_CLASS_MEMBER(["lootName"], lootName);
                            JSON_FROM_CLASS_MEMBER(["lootId"], lootId);
                            JSON_FROM_CLASS_MEMBER(["refId"], refId);
                            JSON_FROM_CLASS_MEMBER(["localizedName"], localizedName);
                            JSON_FROM_CLASS_MEMBER(["localizedDescription"], localizedDescription);
                            JSON_FROM_CLASS_MEMBER(["itemDesc"], itemDesc);
                            JSON_FROM_CLASS_MEMBER(["displayCategories"], displayCategories);
                            JSON_FROM_CLASS_MEMBER(["rarity"], rarity);
                            JSON_FROM_CLASS_MEMBER(["tags"], tags);
                            JSON_FROM_CLASS_MEMBER(["type"], type);
                            JSON_FROM_CLASS_MEMBER(["asset"], asset);
                            JSON_FROM_CLASS_MEMBER(["tilePath"], tilePath);
                            JSON_FROM_CLASS_MEMBER(["splashPath"], splashPath);
                            JSON_FROM_CLASS_MEMBER(["shadowPath"], shadowPath);
                            JSON_FROM_CLASS_MEMBER(["upgradeLootName"], upgradeLootName);
                            JSON_FROM_CLASS_MEMBER(["upgradeEssenceName"], upgradeEssenceName);
                            JSON_FROM_CLASS_MEMBER(["disenchantLootName"], disenchantLootName);
                            JSON_FROM_CLASS_MEMBER(["localizedRecipeTitle"], localizedRecipeTitle);
                            JSON_FROM_CLASS_MEMBER(["localizedRecipeSubtitle"], localizedRecipeSubtitle);
                            JSON_FROM_CLASS_MEMBER(["itemStatus"], itemStatus);
                            JSON_FROM_CLASS_MEMBER(["parentItemStatus"], parentItemStatus);
                            JSON_FROM_CLASS_MEMBER(["redeemableStatus"], redeemableStatus);
                            JSON_FROM_CLASS_MEMBER(["count"], count);
                            JSON_FROM_CLASS_MEMBER(["rentalGames"], rentalGames);
                            JSON_FROM_CLASS_MEMBER(["storeItemId"], storeItemId);
                            JSON_FROM_CLASS_MEMBER(["parentStoreItemId"], parentStoreItemId);
                            JSON_FROM_CLASS_MEMBER(["value"], value);
                            JSON_FROM_CLASS_MEMBER(["upgradeEssenceValue"], upgradeEssenceValue);
                            JSON_FROM_CLASS_MEMBER(["disenchantValue"], disenchantValue);
                            JSON_FROM_CLASS_MEMBER(["expiryTime"], expiryTime);
                            JSON_FROM_CLASS_MEMBER(["rentalSeconds"], rentalSeconds);
                            JSON_FROM_CLASS_MEMBER(["isNew"], isNew);
                            JSON_FROM_CLASS_MEMBER(["isRental"], isRental);
                        JSON_CLASS_END() catch (std::exception& e) {
                            LCU::Log::Out(LCU::Log::LogLevel::ERR, LCU::Log::LogActivity::CLASS_CREATION, "Failed to create a %s json object. (%s)", GetClassName(), e.what());
                        };
                        return output;
                    }

                    const char* GetClassName() {
                        return "LolLootPlayerLoot";
                    }
                };
            }
        }
    }
};