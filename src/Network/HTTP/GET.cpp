#include "HTTP.hpp"
std::vector<std::pair<std::basic_string<unsigned char>, CURL*>> LCU::Network::HTTP::Buffer::bfGET;

size_t LCU::Network::HTTP::Buffer::GET_WriteCallback(void* contents, size_t size, size_t nmemb, void* userdata)
{
	size_t len = size * nmemb; // "size" is always 1

	// append contents into buffer (userdata)
	((std::basic_string<unsigned char>*)userdata)->append((unsigned char*)contents, len);

	// return size of contents
	return len;
}

void LCU::Network::HTTP::Buffer::CreateBuffer_GET_WriteCallback(CURL* curl)
{
	// Add a new buffer object
	bfGET.push_back(std::pair<std::basic_string<unsigned char>, CURL*>(std::basic_string<unsigned char>(), curl));
}

std::basic_string<unsigned char>* LCU::Network::HTTP::Buffer::GetBuffer_GET_WriteCallback(CURL* curl, bool repeatOnFail)
{
	// Loop backwards to get newer buffers first
	for (int i = (int)bfGET.size() - 1; i >= 0; i--) {
		if (bfGET[i].second == curl)
			return &bfGET[i].first;
	}

	// Don't stack overflow on failure
	if (!repeatOnFail)
		return NULL;

	// Create a new buffer if none found
	CreateBuffer_GET_WriteCallback(curl);

	// Return new buffer by running GetBuffer again
	return GetBuffer_GET_WriteCallback(curl, false);
}

void LCU::Network::HTTP::GetBare(Session* session, std::string url, void* writeCallback, void* writeData)
{
	CURL* curl = session->GetCURLInstance();
	LCU::Network::HTTP::Init(curl, session, url);

	if (!curl) {
		LCU::Log::Out(LCU::Log::LogLevel::WARNING, LCU::Log::LogActivity::HTTP, "Provided CURL object is NULL. GET failed.");
		return;
	}

	// Request type
	curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");

	// Write callback
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);

	// Write data
	if (writeData)
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, writeData);

	// Perform GET
	CURLcode result = curl_easy_perform(curl);

	if (result != CURLE_OK)
		LCU::Log::Out(LCU::Log::LogLevel::WARNING, LCU::Log::LogActivity::HTTP, "GET request failed. (%i)", result);
}

std::basic_string<unsigned char> LCU::Network::HTTP::Get(Session* session, std::string url)
{
	CURL* curl = session->GetCURLInstance();

	// Get buffer
	std::basic_string<unsigned char>* buffer = Buffer::GetBuffer_GET_WriteCallback(curl);
	if (!buffer) {
		LCU::Log::Out(LCU::Log::LogLevel::WARNING, LCU::Log::LogActivity::HTTP, "Could not create a GET buffer.");
		return std::basic_string<unsigned char>();
	}
	
	// Clear buffer
	buffer->clear();
	
	// Start GET request
	GetBare(session, url, &Buffer::GET_WriteCallback, buffer);

	// Return buffer
	return *buffer;
}
