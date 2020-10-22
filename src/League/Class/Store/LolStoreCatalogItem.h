/*
    LibLCU,
    2020 - par0-git
    Class / LolStoreCatalogItem << LolBaseClass
*/

#pragma once
#include "../LolClass.h"

namespace LCU {
    namespace League {
        namespace Class {
            namespace Loot {
                class LolStoreCatalogItem : public LolBaseClass {
                public:
                    int itemId;
                    std::string inventoryType, iconUrl;
                    // std::map<LolStoreItemLocalization> localizations
                    bool active;
                    std::string inactiveDate;
                    int maxQuantity;
                    //std::vector<LolStoreItemCost> prices
                    std::string releaseDate;

                    std::vector<SerializedObjectValue> GetSerializationData() {
                        return {
                            {SerializedValueType::NUMBER, "itemId", &itemId},
                            {SerializedValueType::STRING, "inventoryType", &inventoryType},
                            {SerializedValueType::STRING, "iconUrl", &iconUrl},
                            {SerializedValueType::BOOL, "active", &active},
                            {SerializedValueType::STRING, "inactiveDate", &inactiveDate},
                            {SerializedValueType::NUMBER, "maxQuantity", &maxQuantity},
                            //{SerializedValueType::VECTOR, "prices", &prices},
                            {SerializedValueType::STRING, "releaseDate", &releaseDate},
                        };
                    }

                    const char* GetClassReadableName() {
                        return "LolStoreCatalogItem";
                    }
                };
            }
        }
    }
};