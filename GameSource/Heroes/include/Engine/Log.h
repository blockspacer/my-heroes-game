// Heroes Game
// Author: Samuel Hall
// Last Commented 1/20/2015

#pragma once

/*
 * Preprocessor macros for the debug level of the game. These are ran in Release mode.
 * The levels affect the g_asserts that are checked in the game and the
 * number of events that are sent to the log
 * Level 0 indicates no debugging
 * Level 3 indicates maximum debugging
 */
#define g_DEBUG_LEVEL_ZERO 0
#define g_DEBUG_LEVEL_ONE 1
#define g_DEBUG_LEVEL_TWO 2
#define g_DEBUG_LEVEL_THREE 3

// This is where you actually set the Debug level
#define g_DEBUG_LEVEL g_DEBUG_LEVEL_THREE

/*
 * The following is the group of various log output events and 
 * the respective level of debugging that they will occur on. These
 * are what should be passed to the log macros defined below.
 */

// Level 1 Log Events
#define LOG_CONSTRUCTION_EVENT "ConstructionEvent"
#define LOG_DESTRUCTION_EVENT "DestructionEvent"
#define LOG_INITIALIZATION_EVENT "InitializationEvent"
#define LOG_UNINITIALIZATION_EVENT "UninitializationEvent"
#define LOG_SDL_RESOURCES "SDLResources"

// Level 2 Log Events
#define LOG_FILE_LOAD_EVENT "FileLoaded"
#define LOG_FILE_UNLOAD_EVENT "FileUnloaded"
#define LOG_SDL_ERROR "SDL_Error"
#define LOG_SDL_TTF_ERROR "SDL_TTF_Error"
#define LOG_SDL_IMG_ERROR "SDL_TTF_Error"

// Level 3 Log Events
// ...

// 3 levels of debugging to the log file
#if g_DEBUG_LEVEL == 3
#	define g_DEBUG_LEVEL_DESCRIPTION "High (3)"
#	define g_Log_Write_L1(logEvent, lineText) Engine::Log::GetSingletonInstance().WriteLogEntry( g_DEBUG_LEVEL_ONE, logEvent, __FILE__, __FUNCTION__, __LINE__, lineText)
#	define g_Log_Write_L2(logEvent, lineText) Engine::Log::GetSingletonInstance().WriteLogEntry( g_DEBUG_LEVEL_TWO, logEvent, __FILE__, __FUNCTION__, __LINE__, lineText)
#	define g_Log_Write_L3(logEvent, lineText) Engine::Log::GetSingletonInstance().WriteLogEntry( g_DEBUG_LEVEL_THREE, logEvent, __FILE__, __FUNCTION__, __LINE__, lineText)
#   define g_assert(expression) SDL_assert(expression)
#elif g_DEBUG_LEVEL == 2
#	define g_DEBUG_LEVEL_DESCRIPTION "Medium (2)"
#	define g_Log_Write_L1(logEvent, lineText) Engine::Log::GetSingletonInstance().WriteLogEntry( g_DEBUG_LEVEL_ONE, logEvent, __FILE__, __FUNCTION__, __LINE__, lineText)
#	define g_Log_Write_L2(logEvent, lineText) Engine::Log::GetSingletonInstance().WriteLogEntry( g_DEBUG_LEVEL_TWO, logEvent, __FILE__, __FUNCTION__, __LINE__, lineText)
#	define g_Log_Write_L3(logEvent, lineText)
#   define g_assert(expression) SDL_assert(expression)
#elif g_DEBUG_LEVEL == 1
#	define g_DEBUG_LEVEL_DESCRIPTION "Low (1)"
#	define g_Log_Write_L1(logEvent, lineText) Engine::Log::GetSingletonInstance().WriteLogEntry( g_DEBUG_LEVEL_ONE, logEvent, __FILE__, __FUNCTION__, __LINE__, lineText)
#	define g_Log_Write_L2(logEvent, lineText)
#	define g_Log_Write_L3(logEvent, lineText)
#   define g_assert(expression) SDL_assert(expression)
#else
#	define g_DEBUG_LEVEL_DESCRIPTION "None (0)"
#	define g_Log_Write_L1(logEvent, lineText)
#	define g_Log_Write_L2(logEvent, lineText)
#	define g_Log_Write_L3(logEvent, lineText)
#   define g_assert(expression)
#endif

#include <fstream>
#include <mutex>

#include <SDL_assert.h>
#include <tinyxml2.h>

namespace Heroes
{
	namespace Engine
	{

		/*
		 * This is a class for writing to log files. It creates a file called HeroesLog.xml using the tinyxml
		 * parsing library. This enables the rest of the program to send log events that get written to the log file
		 * in numbered order.
		 */
		class Log final
		{
		public:

			/*
			 * This is the singleton access method, must be declared within the class.
			 * This ensures that there is only one log writer during program execution.
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
			 * Private destructor so that the log class cannot be deleted until the program terminates.
			 */
			~Log();

			// Dont forget to declare these two. You want to make sure they
			// are unaccessable otherwise you may accidently get copies of
			// your singleton appearing.
			Log(Log const&); // no implementation
			void operator=(Log const&); // no implementation

			// This is a counter so that each log event will have a unique number id
			int m_logEventID{ 0 };

			// self explanatory
			std::mutex m_mutex;
			std::ofstream m_outputFile;
			tinyxml2::XMLPrinter m_logPrinter;
		};
	} // namespace Engine
} // namespace Heroes