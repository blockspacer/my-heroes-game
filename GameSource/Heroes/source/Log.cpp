// Heroes Game
// Author: Samuel Hall
// Last Commented IN PROGRESS

#include <stdio.h>
#include <string>
#include <SDL_timer.h> // GetTicks

#include "Engine/Log.h"

namespace Heroes
{
	namespace Engine
	{

		// useful constants for the name and access mode of the log file
		const char* LOG_FILE = "Logs/HeroesLog";
		const char* LOG_FILE_MODE = "w"; // this will create a blank document everytime

		Log::Log()
		{
			std::lock_guard<std::mutex> lock(m_mutex);

			std::string fileName;
			fileName = std::string(LOG_FILE) + "_Time[" + std::string(__TIME__) + "].xml";
			fileName[22] = '-'; // replace the ":"
			fileName[25] = '-'; // replace the ":"

			m_outputFile.open(fileName);
			
			// print xml log header
			m_logPrinter.ClearBuffer();

			m_logPrinter.PushHeader(true, true);
			m_logPrinter.PushComment("Written using Log.cpp");

			std::string generatedComment;
			generatedComment = "Generated from code compiled on " + std::string(__DATE__) + " at " + std::string(__TIME__);
			m_logPrinter.PushComment(generatedComment.c_str());

			m_logPrinter.OpenElement("GameLog");

			m_logPrinter.OpenElement("LogHeader");

				m_logPrinter.OpenElement("DebugLevel");

					std::string debugLevel = "Debug Level is " + std::string(g_DEBUG_LEVEL_DESCRIPTION);
					m_logPrinter.PushText(debugLevel.c_str());

				m_logPrinter.CloseElement();

				m_logPrinter.OpenElement("Session");

					m_logPrinter.OpenElement("Started");

						m_logPrinter.OpenElement("Time");

							std::string time = std::string(__TIME__);
							m_logPrinter.PushText(time.c_str());

						m_logPrinter.CloseElement();

						m_logPrinter.OpenElement("Date");

							std::string date = std::string(__DATE__);
							m_logPrinter.PushText(date.c_str());

						m_logPrinter.CloseElement();

					m_logPrinter.CloseElement();

					m_logPrinter.OpenElement("Configuration");
					m_logPrinter.CloseElement();

				m_logPrinter.CloseElement();

			m_logPrinter.CloseElement();

			m_outputFile << m_logPrinter.CStr();
			m_outputFile.flush();

			m_logPrinter.ClearBuffer();
		}

		Log::~Log()
		{
			m_logPrinter.CloseElement();

			m_outputFile << m_logPrinter.CStr();
			m_outputFile.flush();
			
			m_outputFile.close();
		}

		void Log::WriteLogEntry(int iEntryType, std::string logEvent, std::string strSourceFile, std::string strFunction, int iSourceLine, std::string strMessage)
		{
			std::lock_guard<std::mutex> lock(m_mutex);

			m_logPrinter.ClearBuffer();

			// Log Event
			m_logPrinter.OpenElement("LogEvent");

			m_logPrinter.PushAttribute("chronological_id", m_logEventID++);
			m_logPrinter.PushAttribute("debug_type", iEntryType);
			m_logPrinter.PushAttribute("log_event_type", logEvent.c_str());

			m_logPrinter.OpenElement("TimeIndex");
			m_logPrinter.PushText(std::to_string(SDL_GetTicks()).c_str());
			m_logPrinter.CloseElement();

			m_logPrinter.OpenElement("Location");
			std::string location = "SOURCE: " + strSourceFile + ", FUNCTION: " + strFunction + ", LINE: " + std::to_string(iSourceLine);
			m_logPrinter.PushText(location.c_str());
			m_logPrinter.CloseElement();

			m_logPrinter.OpenElement("Message");
			m_logPrinter.PushText(strMessage.c_str());
			m_logPrinter.CloseElement();

			m_logPrinter.CloseElement();

			m_outputFile << m_logPrinter.CStr();
			m_outputFile.flush();

			m_logPrinter.ClearBuffer();
		}

	} // namespace Engine
} // namespace Heroes