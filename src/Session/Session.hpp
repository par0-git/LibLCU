#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <thread>
#include <curl/curl.h>
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
    public:
        Session() {}

        Session(std::string gameDir) {
            Init(gameDir);
        }

        ~Session() {
            active = false;
            Disconnect();
        }
        
        bool Init(std::string gameDir);
        bool Disconnect();

        CURL* GetCURLInstance();
        Lockfile GetLockfileFromFile(std::string file = "lockfile");

        // Information for connecting to the back-end client server.  
        Lockfile clientConnectionData;
    private:
        // Activity.
        bool active = false;

        // Where the default client is stored.
        std::string gameDirectory;

        // CURL instances (by thread).
        std::vector<std::pair<CURL*, std::thread::id>> byThreadCurl;
    };
};
