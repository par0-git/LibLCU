#include "HTTP.hpp"

void LCU::Network::HTTP::Put(Session* session, std::string url, std::string data)
{
	CURL* curl = session->GetCURLInstance();
	LCU::Network::HTTP::Init(curl, session, url);

	if (!curl) {
		LCU::Log::Out(LCU::Log::LogLevel::WARNING, LCU::Log::LogActivity::HTTP, "Provided CURL object is NULL after Init. PUT failed.");
		return;
	}

	// Request data
	curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());

	// Request type
	curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PUT");

	// Perform PUT
	CURLcode result = curl_easy_perform(curl);

	if (result != CURLE_OK)
		LCU::Log::Out(LCU::Log::LogLevel::WARNING, LCU::Log::LogActivity::HTTP, "PUT request failed. (%i)", result);
}