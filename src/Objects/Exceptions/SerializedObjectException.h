#pragma once
#include <exception>
#include <string>
namespace LCU {
	namespace Exception {
		struct SerializedObjectException : public std::exception
		{
			SerializedObjectException(std::string argReason) : failReason(argReason) {}
			std::string& reason() {
				return failReason;
			}
		private:
			std::string failReason;
		};

		struct SerializedValueFailure : public SerializedObjectException
		{
			using SerializedObjectException::SerializedObjectException;
			const char* what() const throw ()
			{
				return "LibLCU failed while handling a serialized object.";
			}
		};

		struct SerializedContainerOutOfRange : public SerializedObjectException
		{
			using SerializedObjectException::SerializedObjectException;
			const char* what() const throw ()
			{
				return "LibLCU failed while searching for a serialized object.";
			}
		};

		struct SerializedContainerCreationFailure : public SerializedObjectException
		{
			using SerializedObjectException::SerializedObjectException;
			const char* what() const throw ()
			{
				return "LibLCU failed while creating a container.";
			}
		};
	}
}