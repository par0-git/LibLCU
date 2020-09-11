#pragma once
#include <stdio.h>

namespace LCU {
	namespace Log {
		enum LogLevel {
			INFO,
			WARNING,
			ERR,
			FATAL,			
		};

		enum LogActivity {
			HTTP,
			INIT,
			CLASS_CREATION,
			INVALID_INPUT
		};
		
		extern LogLevel logLevels[sizeof(LogActivity)];
		void Out(LogLevel level, LogActivity activity, const char* text, ...);
	}
}