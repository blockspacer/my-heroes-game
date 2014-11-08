#pragma once

#define g_HEROES_DEBUG_LEVEL 3

// 3 levels of debugging to the log file
#if g_HEROES_DEBUG_LEVEL == 3
#	define Log_Write_L1(linetype, linetext) Log::GetSingletonInstance().WriteLogEntry( (linetype),  __FILE__, __FUNCTION__, __LINE__, (linetext) )
#	define Log_Write_L2(linetype, linetext) Log::GetSingletonInstance().WriteLogEntry( (linetype),  __FILE__, __FUNCTION__, __LINE__, (linetext) )
#	define Log_Write_L3(linetype, linetext) Log::GetSingletonInstance().WriteLogEntry( (linetype),  __FILE__, __FUNCTION__, __LINE__, (linetext) )
#elif g_HEROES_DEBUG_LEVEL == 2
#	define Log_Write_L1(linetype, linetext) Log::GetSingletonInstance().WriteLogEntry( (linetype),  __FILE__, __FUNCTION__, __LINE__, (linetext) )
#	define Log_Write_L2(linetype, linetext) Log::GetSingletonInstance().WriteLogEntry( (linetype),  __FILE__, __FUNCTION__, __LINE__, (linetext) )
#	define Log_Write_L3(linetype, linetext)
#elif g_HEROES_DEBUG_LEVEL == 1
#	define Log_Write_L1(linetype, linetext) Log::GetSingletonInstance().WriteLogEntry( (linetype),  __FILE__, __FUNCTION__, __LINE__, (linetext) )
#	define Log_Write_L2(linetype, linetext)
#	define Log_Write_L3(linetype, linetext)
#else
#	define Log_Write_L1(linetype, linetext)
#	define Log_Write_L2(linetype, linetext)
#	define Log_Write_L3(linetype, linetext)
#endif

#include <string>
#include <iostream>

#include <tinyxml2.h>

namespace Heroes
{
	namespace Engine
	{
		//const char* LOG_FILE = "HeroesLog.xml";

		class Log final
		{
		public:

			/*
			 * This is the singleton access method, must be declared within the class
			 */
			static Log& GetSingletonInstance()
			{
				static Log instance;
				return instance;
			}

			/*
			 * This is the WriteLogEntry method it writes a Log Event the the HeroesLog.xml file. The user should never call this directly
			 * and should instead use the preprocessor macros Log_Write_L1, Log_Write_L2, Log_Write_L3 to write information to log.
			 */
			void WriteLogEntry(int iEntryType, std::string strSourceFile, std::string strFunction, int iSourceLine, std::string strMessage);

		private:

			/*
			 * Private constructor to control when this class can be made
			 */
			Log();

			// Dont forget to declare these two. You want to make sure they
			// are unaccessable otherwise you may accidently get copies of
			// your singleton appearing.
			Log(Log const&); // no implementation
			void operator=(Log const&); // no implementation

			tinyxml2::XMLDocument m_logDocument;
		};
	} // namespace Engine
} // namespace Heroes