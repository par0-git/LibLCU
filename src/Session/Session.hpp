#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "../Output/Logging.hpp"

namespace LCU {
	struct Lockfile {
		std::string name;
		int servicePort;
		int serverPort;
		std::string auth;
		std::string protocol;
		bool valid = false;
	};
	
    class Session {
        // Where the default client is stored.
        std::string gameDirectory;

        // Information for connecting to the back-end client server.  
        Lockfile clientConnectionData;

    public:
        bool Init(std::string gameDir);

    private:
        Lockfile GetLockfileFromFile(std::string file = "lockfile");
    };
};