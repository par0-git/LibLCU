#include "Session.hpp"

bool LCU::Session::Init(std::string gameDir) {
    gameDirectory = gameDir;
    clientConnectionData = GetLockfileFromFile(gameDirectory + "//lockfile");
    
    if (!clientConnectionData.valid) {
        LCU::Log::Out(LCU::Log::FATAL, LCU::Log::LogActivity::INIT, "Invalid game directory provided.");
        return;
    }
}

LCU::Lockfile LCU::Session::GetLockfileFromFile(std::string file = "lockfile") {
    std::ifstream lockfile(file);
    std::vector<std::string> lockfileSplitArray;

    if (lockfile.is_open()) {
        std::string data;
        std::string buffer;

        // There is only 1 line in the lockfile, so no need for more than getline()
        getline(lockfile, data);

        for (int i = 0; i < data.size(); i++) {
            // If character is separator, add buffer to array and clear buffer for next characters
            if (data[i] == ':') {
                lockfileSplitArray.push_back(buffer);
                buffer = "";
                continue;
            }

            // Add character to buffer
            buffer += data[i];
        }
        lockfileSplitArray.push_back(buffer);
    }
    else {
        // Return invalid lockfile if not opened correctly
        return { "",0,0,"","",false };
    }

    return  { lockfileSplitArray[0], // name
            std::stoi(lockfileSplitArray[1]), // servicePort 
            std::stoi(lockfileSplitArray[2]), // serverPort
            lockfileSplitArray[3], // auth
            lockfileSplitArray[4], // protocol
            true }; // valid 
}