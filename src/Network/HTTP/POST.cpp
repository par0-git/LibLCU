#include "HTTP.hpp"

void LCU::Network::HTTP::Post(Session* session, std::string url, std::string data)
{
	CURL* curl = session->GetCURLInstance();
	LCU::Network::HTTP::Init(curl, session, url);

	if (!curl) {
		LCU::Log::Out(LCU::Log::LogLevel::WARNING, LCU::Log::LogActivity::HTTP, "Provided CURL object is NULL after Init. POST failed.");
		return;
	}

	// Request data
	curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());

	// Request type
	curl_easy_setopt(curl, CURLOPT_POST, 1L);
	curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");

	// Perform POST
	CURLcode result = curl_easy_perform(curl);

	if (result != CURLE_OK)
		LCU::Log::Out(LCU::Log::LogLevel::WARNING, LCU::Log::LogActivity::HTTP, "POST request failed. (%i)", result);
}