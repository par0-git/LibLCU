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
	SerializedValue data(SerializedValueType::OBJECT);
	data.child("newAffinity", true) = affinity;

	LCU::Network::HTTP::Post(session, "/riotclient/affinity", data.getJSON());
}

/// <summary>
/// Get the affinity of the application.
///	Seems to always return null, commented out.
/// </summary>
/// <param name="session">Pointer to a Session object.</param>
/*std::string LCU::League::Client::UX::GetAffinity(Session* session)
{
	// Parse response
	rapidjson::Document responseNative;
	responseNative.Parse(LCU::Network::HTTP::Get(session, "/riotclient/affinity").c_str());
	LCU::SerializedValue responseLayered(responseNative);
	return responseLayered.child("currentAffinity").asString();
}*/

/// <summary>
/// Get the command line arguments of the application.
/// </summary>
/// <param name="session">Pointer to a Session object.</param>
/// <returns>String vector of command line arguments.</returns>
std::vector<std::string> LCU::League::Client::UX::GetCommandLineArgs(Session* session)
{
	// Parse response
	rapidjson::Document responseNative;
	responseNative.Parse(LCU::Network::HTTP::Get(session, "/riotclient/command-line-args").c_str());
	LCU::SerializedValue responseLayered(responseNative);

	// Turn response to object array
	std::vector<LCU::SerializedValue> responseArray = responseLayered.asVector();
	std::vector<std::basic_string<response_char>> object;
	for (int i = 0; i < responseArray.size(); i++) {
		object.push_back(responseArray[i].asString());
	}

	return object;
}

/// <summary>
/// Set the command line arguments of the application.
/// </summary>
/// <param name="session">Pointer to a Session object.</param>
/// <param name="args">String vector of command line arguments.</param>
void LCU::League::Client::UX::SetCommandLineArgs(Session* session, std::vector<std::string> args)
{
	// This function is broken. Refer to issue #2.
	//LCU::Network::HTTP::Post(session, "/riotclient/new-args", data.dump());
}

/// <summary>
/// Get info for the current system.
/// </summary>
/// <param name="session">Pointer to a Session object.</param>
/// <returns>Basic system info.</returns>
LCU::League::Class::Client::BasicSystemInfo LCU::League::Client::UX::GetSystemInfo(Session* session)
{
	// Parse response
	rapidjson::Document responseNative;
	responseNative.Parse(LCU::Network::HTTP::Get(session, "/riotclient/system-info/v1/basic-info").c_str());
	LCU::SerializedValue responseLayered(responseNative);

	// Turn response to object
	LCU::League::Class::Client::BasicSystemInfo object;
	object.init(responseLayered);

	return object;
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
