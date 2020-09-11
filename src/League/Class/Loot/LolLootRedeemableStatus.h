/*
    LibLCU,
    2020 - par0-git
    Enum / LolLootRedeemableStatus
*/

#pragma once

namespace LCU {
    namespace League {
        namespace Class {
            namespace Loot {
                enum class LolLootRedeemableStatus {
                    UNKNOWN,
                    REDEEMABLE,
                    REDEEMABLE_RENTAL,
                    NOT_REDEEMABLE,
                    NOT_REDEEMABLE_RENTAL,
                    ALREADY_OWNED,
                    ALREADY_RENTED,
                    CHAMPION_NOT_OWNED,
                    SKIN_NOT_OWNED
                };
            }
        }
    }
};