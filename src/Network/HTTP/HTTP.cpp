#include "HTTP.hpp"

void LCU::Network::HTTP::Init(CURL* curl, std::string url)
{
	if (!curl)
		curl = curl_easy_init();
}
