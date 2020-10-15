#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <thread>
#include "../../Network/Session.hpp"
#include "../Class/Loot/LolLootPlayerLoot.h"

namespace LCU {
    namespace League {
        namespace Loot {
            std::vector<Class::Loot::LolLootPlayerLoot> GetPlayerLoot(Session* session);
        }
    }
};
