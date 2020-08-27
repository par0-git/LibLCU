#include "Logging.hpp"
LCU::Log::LogLevel LCU::Log::logLevels[sizeof(LCU::Log::LogActivity)];

void LCU::Log::Out(LogLevel level, LogActivity activity, const char* text, ...)
{
	if (level > logLevels[activity])
		return;

	printf("liblcu: %s\n", text);
}
