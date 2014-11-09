#pragma once

#define g_DEBUG_LEVEL_ZERO 0
#define g_DEBUG_LEVEL_ONE 1
#define g_DEBUG_LEVEL_TWO 2
#define g_DEBUG_LEVEL_THREE 3

#define g_DEBUG_LEVEL g_DEBUG_LEVEL_TWO

// Level 1 Log Events
#define LOG_CONSTRUCTION_EVENT "ConstructionEvent"
#define LOG_DESTRUCTION_EVENT "DestructionEvent"
#define LOG_INITIALIZATION_EVENT "InitializationEvent"
#define LOG_UNINITIALIZATION_EVENT "UninitializationEvent"

// Level 2 Log Events
#define LOG_FILE_LOAD_EVENT "FileLoaded"
#define LOG_FILE_UNLOAD_EVENT "FileUnloaded"

// 3 levels of debugging to the log file
#if g_DEBUG_LEVEL == 3
#	define g_DEBUG_LEVEL_DESCRIPTION "High (3)"
#	define g_Log_Write_L1(logEvent, lineText) Engine::Log::GetSingletonInstance().WriteLogEntry( g_DEBUG_LEVEL_ONE, logEvent, __FILE__, __FUNCTION__, __LINE__, lineText)
#	define g_Log_Write_L2(logEvent, lineText) Engine::Log::GetSingletonInstance().WriteLogEntry( g_DEBUG_LEVEL_TWO, logEvent, __FILE__, __FUNCTION__, __LINE__, lineText)
#	define g_Log_Write_L3(logEvent, lineText) Engine::Log::GetSingletonInstance().WriteLogEntry( g_DEBUG_LEVEL_THREE, logEvent, __FILE__, __FUNCTION__, __LINE__, lineText)
#elif g_DEBUG_LEVEL == 2
#	define g_DEBUG_LEVEL_DESCRIPTION "Medium (2)"
#	define g_Log_Write_L1(logEvent, lineText) Engine::Log::GetSingletonInstance().WriteLogEntry( g_DEBUG_LEVEL_ONE, logEvent, __FILE__, __FUNCTION__, __LINE__, lineText)
#	define g_Log_Write_L2(logEvent, lineText) Engine::Log::GetSingletonInstance().WriteLogEntry( g_DEBUG_LEVEL_TWO, logEvent, __FILE__, __FUNCTION__, __LINE__, lineText)
#	define g_Log_Write_L3(logEvent, lineText)
#elif g_DEBUG_LEVEL == 1
#	define g_DEBUG_LEVEL_DESCRIPTION "Low (1)"
#	define g_Log_Write_L1(logEvent, lineText) Engine::Log::GetSingletonInstance().WriteLogEntry( g_DEBUG_LEVEL_ONE, logEvent, __FILE__, __FUNCTION__, __LINE__, lineText)
#	define g_Log_Write_L2(logEvent, lineText)
#	define g_Log_Write_L3(logEvent, lineText)
#else
#	define g_DEBUG_LEVEL_DESCRIPTION "None (0)"
#	define g_Log_Write_L1(logEvent, lineText)
#	define g_Log_Write_L2(logEvent, lineText)
#	define g_Log_Write_L3(logEvent, lineText)
#endif



#include <fstream>
#include <mutex>

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
			void WriteLogEntry(int iEntryType, std::string logEvent, std::string strSourceFile, std::string strFunction, int iSourceLine, std::string strMessage);

		private:

			/*
			 * Private constructor to control when this class can be made
			 */
			Log();

			/*
			 *
			 */
			~Log();

			// Dont forget to declare these two. You want to make sure they
			// are unaccessable otherwise you may accidently get copies of
			// your singleton appearing.
			Log(Log const&); // no implementation
			void operator=(Log const&); // no implementation

			int m_logEventID{ 0 };
			std::mutex m_mutex;
			std::ofstream m_outputFile;
			tinyxml2::XMLPrinter m_logPrinter;
		};
	} // namespace Engine
} // namespace Heroes