#include "HTTP.hpp"

void LCU::Network::HTTP::Init(CURL* curl, Session* session, std::string url)
{
	if (!curl)
		curl = curl_easy_init();

	std::string webUrl;
	if (url[0] == '/')
		webUrl = std::string("https://127.0.0.1" + url);
	else
		webUrl = std::string("https://127.0.0.1/" + url);

	curl_easy_setopt(curl, CURLOPT_URL, webUrl.c_str());
	curl_easy_setopt(curl, CURLOPT_PORT, session->clientConnectionData.serverPort);

	struct curl_slist* headers = NULL;
	headers = curl_slist_append(headers, "Content-Type: application/json");
	curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

	// Reset the CURL object
	curl_easy_setopt(curl, CURLOPT_POST, 0L);
	curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");

	// Skip cert verification
	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);

	// Skip hostname verification
	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

	// Use "basic" auth
	curl_easy_setopt(curl, CURLOPT_HTTPAUTH, (long)CURLAUTH_BASIC);

	// Max redirects
	curl_easy_setopt(curl, CURLOPT_MAXREDIRS, 5);

	curl_easy_setopt(curl, CURLOPT_USERNAME, "riot");
	curl_easy_setopt(curl, CURLOPT_PASSWORD, session->clientConnectionData.auth.c_str()); // if string is passed it won't work, use c_str
}
