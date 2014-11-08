
#include "Engine/Log.h"

namespace Heroes
{
	namespace Engine
	{
		const char* LOG_FILE = "HeroesLog.xml";

		Log::Log()
		{
			// open xml file write the beginning of the log (header)
			

		}

		void Log::WriteLogEntry(int iEntryType, std::string strSourceFile, std::string strFunction, int iSourceLine, std::string strMessage)
		{
			// write log event
			std::cout << iEntryType << " " << strSourceFile << " " << strFunction << " Line: " << iSourceLine << " " << strMessage << std::endl;
		}

	} // namespace Engine
} // namespace Heroes