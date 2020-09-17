#pragma once
#include "../../Session/Session.hpp"
#include "../../Network/HTTP/HTTP.hpp"
#include "../Class/Client/BasicSystemInfo.h"
#include <nlohmann\json.hpp>

namespace LCU {
    namespace League {
        namespace Client {
            namespace ProcessControl {
                void Quit(Session* session);
                void Restart(Session* session, int delay = 0);
                void Repair(Session* session);
            }
            namespace UX {
                void Unload(Session* session);

                void SetAffinity(Session* session, std::string affinity);
                std::string GetAffinity(Session* session);

                std::vector<std::string> GetCommandLineArgs(Session* session);
                void SetCommandLineArgs(Session* session, std::vector<std::string> args);

                LCU::League::Class::Client::BasicSystemInfo GetSystemInfo(Session* session);

                void Kill(Session* session);
                void Launch(Session* session);
     
                void Flash(Session* session);
                void Show(Session* session);
                void Minimize(Session* session);
            }
        }
    }
};
