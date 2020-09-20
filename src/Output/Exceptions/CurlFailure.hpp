#pragma once
#include <exception>

namespace LCU {
	namespace Exception {
		struct LCUCurlFailure : public std::exception
		{
			const char* what() const throw ()
			{
				return "cURL failed to do a request.";
			}
		};
	}
}