#include "pch.h"

#include "Log.h"

#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"

namespace Core {

	Log::Log(bool logToFile)
		: m_LogToFile(logToFile)
	{
	}

	Log::~Log()
	{
	}

	void Log::Create()
	{
		std::vector<spdlog::sink_ptr> sinks;

		// Console sink
		auto consoleSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
		consoleSink->set_pattern("%^[%T]: %v%$");
		sinks.push_back(consoleSink);

		// File sink with timestamp as filename
		if (m_LogToFile)
		{
			// Get the current time for the file name
			auto now = std::chrono::system_clock::now();
			std::time_t now_time = std::chrono::system_clock::to_time_t(now);
			std::tm tm = *std::localtime(&now_time);
			std::ostringstream oss;
			oss << std::put_time(&tm, "%Y-%m-%d_%H-%M-%S");

			std::string filename = "logs/logfile_" + oss.str() + ".txt";
			auto fileSink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(filename, true);

			sinks.push_back(fileSink);
		}

		// Create and configure logger
		auto logger = std::make_shared<spdlog::logger>("core", sinks.begin(), sinks.end());
		logger->set_level(spdlog::level::trace);
		logger->flush_on(spdlog::level::trace);
		spdlog::register_logger(logger);
	}

	void Log::Destroy()
	{
		spdlog::shutdown();
	}

}