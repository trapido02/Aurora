#pragma once

#include "spdlog/spdlog.h"

namespace Core {

	class Log
	{
	public:
		Log(bool logToFile = false);
		~Log();

		void Create();
		void Destroy();
	private:
		bool m_LogToFile;
	};

}

#define TRACE(...) spdlog::get("core")->trace(__VA_ARGS__)
#define INFO(...) spdlog::get("core")->info(__VA_ARGS__)
#define WARN(...) spdlog::get("core")->warn(__VA_ARGS__)
#define ERROR(...) spdlog::get("core")->error(__VA_ARGS__)
#define CRITICAL(...) spdlog::get("core")->critical(__VA_ARGS__)
#define DEBUG(...) spdlog::get("core")->debug(__VA_ARGS__)