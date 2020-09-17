#include "RiotClient.h"

/// <summary>
/// Quit the application.
/// </summary>
/// <param name="session">Pointer to a Session object.</param>
void LCU::League::Client::ProcessControl::Quit(Session* session)
{
	LCU::Network::HTTP::Post(session, "/process-control/v1/process/quit", "");
}

/// <summary>
/// Restart the application.
/// </summary>
/// <param name="session">Pointer to a Session object.</param>
/// <param name="delay">Delay until restart.</param>
void LCU::League::Client::ProcessControl::Restart(Session* session, int delay)
{
	// Takes "delaySeconds" as a uint32
	nlohmann::json data;
	data["delaySeconds"] = delay;

	LCU::Network::HTTP::Post(session, "/process-control/v1/process/restart", data.dump());
}

/// <summary>
/// Restart and repair the application.
/// </summary>
/// <param name="session">Pointer to a Session object.</param>
void LCU::League::Client::ProcessControl::Repair(Session* session)
{
	LCU::Network::HTTP::Post(session, "/process-control/v1/process/restart-to-repair", "");
}

/// <summary>
/// Unload the UX application.
/// </summary>
/// <param name="session">Pointer to a Session object.</param>
void LCU::League::Client::UX::Unload(Session* session)
{
	LCU::Network::HTTP::Post(session, "/riotclient/unload", "");
}

/// <summary>
/// Show the UX application.
/// </summary>
/// <param name="session">Pointer to a Session object.</param>
void LCU::League::Client::UX::Show(Session* session)
{
	LCU::Network::HTTP::Post(session, "/riotclient/ux-show", "");
}

/// <summary>
/// Flash the UX application in the taskbar.
/// </summary>
/// <param name="session">Pointer to a Session object.</param>
void LCU::League::Client::UX::Flash(Session* session)
{
	LCU::Network::HTTP::Post(session, "/riotclient/ux-flash", "");
}

/// <summary>
/// Minimize the UX application.
/// </summary>
/// <param name="session">Pointer to a Session object.</param>
void LCU::League::Client::UX::Minimize(Session* session)
{
	LCU::Network::HTTP::Post(session, "/riotclient/ux-minimize", "");
}

/// <summary>
/// Set the affinity of the application.
/// </summary>
/// <param name="session">Pointer to a Session object.</param>
/// <param name="affinity">New affinity to use.</param>
void LCU::League::Client::UX::SetAffinity(Session* session, std::string affinity)
{
	// Takes "newAffinity" as a string
	nlohmann::json data;
	data["newAffinity"] = affinity;

	LCU::Network::HTTP::Post(session, "/riotclient/affinity", data.dump());
}

/// <summary>
/// Get the affinity of the application.
/// </summary>
/// <param name="session">Pointer to a Session object.</param>
std::string LCU::League::Client::UX::GetAffinity(Session* session)
{
	nlohmann::json data = nlohmann::json::parse(LCU::Network::HTTP::Get(session, "/riotclient/affinity"));
	return data["currentAffinity"];
}

/// <summary>
/// Get the command line arguments of the application.
/// </summary>
/// <param name="session">Pointer to a Session object.</param>
/// <returns>String vector of command line arguments.</returns>
std::vector<std::string> LCU::League::Client::UX::GetCommandLineArgs(Session* session)
{
	nlohmann::json data = nlohmann::json::parse(LCU::Network::HTTP::Get(session, "/riotclient/command-line-args"));
	return data;
}

/// <summary>
/// Set the command line arguments of the application.
/// </summary>
/// <param name="session">Pointer to a Session object.</param>
/// <param name="args">String vector of command line arguments.</param>
void LCU::League::Client::UX::SetCommandLineArgs(Session* session, std::vector<std::string> args)
{
	nlohmann::json data = args;
	LCU::Network::HTTP::Post(session, "/riotclient/new-args", data.dump());
}

/// <summary>
/// Get info for the current system.
/// </summary>
/// <param name="session">Pointer to a Session object.</param>
/// <returns>Basic system info.</returns>
LCU::League::Class::Client::BasicSystemInfo LCU::League::Client::UX::GetSystemInfo(Session* session)
{
	nlohmann::json data = nlohmann::json::parse(LCU::Network::HTTP::Get(session, "/riotclient/system-info/v1/basic-info"));
	LCU::League::Class::Client::BasicSystemInfo sysInfo;

	LCU::League::Class::Client::BasicSystemInfo::FromJSON(sysInfo, data);
	return sysInfo;
}

/// <summary>
/// Kills the UX application.
/// </summary>
/// <param name="session">Pointer to a Session object.</param>
void LCU::League::Client::UX::Kill(Session* session)
{
	LCU::Network::HTTP::Post(session, "/riotclient/kill-ux", "");
}

/// <summary>
/// Launch the UX application.
/// </summary>
/// <param name="session">Pointer to a Session object.</param>
void LCU::League::Client::UX::Launch(Session* session)
{
	LCU::Network::HTTP::Post(session, "/riotclient/launch-ux", "");
}
