#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <thread>
#include "../../Session/Session.hpp"
#include "../Class/Loot/LolLootPlayerLoot.h"

namespace LCU {
    namespace League {
        namespace Loot {
            std::vector<Class::Loot::LolLootPlayerLoot> GetPlayerLoot(Session* session);
        }
    }
};
