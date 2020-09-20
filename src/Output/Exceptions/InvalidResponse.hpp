#pragma once
#include <exception>

namespace LCU {
	namespace Exception {
		struct LCUInvalidResponse : public std::exception
		{
			const char* what() const throw ()
			{
				return "LibLCU recieved an incorrect response from the League Client.";
			}
		};
	}
}