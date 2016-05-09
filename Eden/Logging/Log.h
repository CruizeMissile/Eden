#ifndef H_LOGGER_LOG_H
#define H_LOGGER_LOG_H

#include "Precompiled.h"

namespace edn
{
	inline std::string NowTime();

	enum LogLevel
	{
		LOG_ERROR,
		LOG_WARNING,
		LOG_INFO,
		LOG_DEBUG,
		LOG_DEBUG2,
		LOG_DEBUG3,
		LOG_DEBUG4
	};

	class Logger : public NonCopyable
	{
	public:
		Logger();
		~Logger();
		std::ostringstream & Get(LogLevel level = LOG_INFO);

	public:
		static LogLevel & ReportingLevel();
		static String ToString(LogLevel level);
		static LogLevel FromString(const String & level); 

	protected:
		std::ostringstream os;
	};

	//
	// Implementation
	//
	inline Logger::Logger()
	{

	}

	inline std::ostringstream& Logger::Get(LogLevel level)
	{
		os << "- " << NowTime();
		os << " " << ToString(level) << ": ";
		return os;
	}

	inline Logger::~Logger()
	{
		os << std::endl;
		fprintf_s(stderr, "%s", os.str().c_str());
		fflush(stderr);
	}

	inline LogLevel & Logger::ReportingLevel()
	{
		static LogLevel reporting_level = LOG_DEBUG4;
		return reporting_level;
	}

	inline String Logger::ToString(LogLevel level)
	{
		static const char* const buffer[] = { "ERROR", "WARNING", "INFO", "DEBUG", "DEBUG2", "DEBUG3", "DEBUG4" };
		return buffer[level];
	}

	inline LogLevel Logger::FromString(const String & level)
	{
		if (level == "DEBUG4")
			return LOG_DEBUG4;
		if (level == "DEBUG3")
			return LOG_DEBUG3;
		if (level == "DEBUG2")
			return LOG_DEBUG2;
		if (level == "DEBUG")
			return LOG_DEBUG;
		if (level == "INFO")
			return LOG_INFO;
		if (level == "WARNING")
			return LOG_WARNING;
		if (level == "ERROR")
			return LOG_ERROR;
		Logger().Get(LOG_WARNING) << "Unknown logging level '" << level << "'. Using INFO Level as default.";
		return LOG_INFO;
	}

#if defined(EDN_WINDOWS)
	inline String NowTime()
	{
		const int MAX_LEN = 200;
		char buffer[MAX_LEN];
		if (GetTimeFormatA(LOCALE_USER_DEFAULT, 0, 0,
			"HH':'mm':'ss", buffer, MAX_LEN) == 0)
			return "Error in NowTime()";

		char result[100] = { 0 };
		static DWORD first = GetTickCount();
		sprintf_s(result, 100, "%s.%03ld", buffer, (long)(GetTickCount() - first) % 1000);
		return result;
	}

#else

	#include <sys/time.h>

	inline std::string NowTime()
	{
		char buffer[11];
		time_t t;
		time(&t);
		tm r = { 0 };
		strftime(buffer, sizeof(buffer), "%X", localtime_r(&t, &r));
		struct timeval tv;
		gettimeofday(&tv, 0);
		char result[100] = { 0 };
		std::sprintf(result, "%s.%03ld", buffer, (long)tv.tv_usec / 1000);
		return result;
	}
#endif

}

#define Loglvl(level) \
	if (level > Logger::ReportingLevel()); \
	else Logger().Get(level)

#define Log() Loglvl(LogLevel::LOG_INFO)
#define LogDebug() Loglvl(LogLevel::LOG_DEBUG)
#define LogError() Loglvl(LogLevel::LOG_ERROR)
#define LogWarn() Loglvl(LogLevel::LOG_WARNING)

#endif