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
                    // std::vector<LolStoreItemCost> prices
                    std::string releaseDate;

                    std::vector<SerializedObjectValue> GetSerializationData() {
                        return {
                           
                        };
                    }

                    static void FromJSON(LolStoreCatalogItem& item, nlohmann::json input) {
                    }

                    nlohmann::json ToJSON() {
                        nlohmann::json output;
                        return output;
                    }

                    const char* GetClassReadableName() {
                        return "LolStoreCatalogItem";
                    }
                };
            }
        }
    }
};