#pragma once
#include <curl/curl.h>
#include <vector>
#include <string>
#include "../../Output/Logging.hpp"

namespace LCU {
	namespace Network {
		namespace HTTP {
			void GetBare(CURL* curl, std::string url, void* writeCallback, void* writeData);
			std::basic_string<unsigned char> Get(CURL* curl, std::string url);

			void Init(CURL* curl, std::string url);

			namespace Buffer {
				size_t GET_WriteCallback(void* contents, size_t size, size_t nmemb, void* userdata);
				std::basic_string<unsigned char>* GetBuffer_GET_WriteCallback(CURL* curl, bool repeatOnFail = true);
				void CreateBuffer_GET_WriteCallback(CURL* curl);
				extern std::vector<std::pair<std::basic_string<unsigned char>, CURL*>> bfGET;
			}
		}
	}
}