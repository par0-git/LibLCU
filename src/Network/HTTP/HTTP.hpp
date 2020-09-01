#pragma once
#include <curl/curl.h>
#include <vector>
#include <string>
#include "../../Session/Session.hpp"
#include "../../Output/Logging.hpp"

namespace LCU {
	namespace Network {
		namespace HTTP {
			void GetBare(Session* session, std::string url, void* writeCallback, void* writeData);
			
			void Post(Session* session, std::string url, std::string data);
			void Put(Session* session, std::string url, std::string data);
			std::basic_string<unsigned char> Get(Session* session, std::string url);
			void Init(CURL* curl, Session* session, std::string url);

			namespace Buffer {
				size_t GET_WriteCallback(void* contents, size_t size, size_t nmemb, void* userdata);
				std::basic_string<unsigned char>* GetBuffer_GET_WriteCallback(CURL* curl, bool repeatOnFail = true);
				void CreateBuffer_GET_WriteCallback(CURL* curl);
				extern std::vector<std::pair<std::basic_string<unsigned char>, CURL*>> bfGET;
			}
		}
	}
}