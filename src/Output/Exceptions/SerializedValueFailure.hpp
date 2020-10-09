#pragma once
#include <exception>

namespace LCU {
	namespace Exception {
		struct SerializedValueFailure : public std::exception
		{
			SerializedValueFailure(std::string exReasonArg) { exReason = exReasonArg; }
			const char* what() const throw ()
			{
				return "LibLCU failed while handling a serialized object.";
			}
			std::string& reason() {
				return exReason;
			}
		private:
			std::string exReason;
		};
	}
}