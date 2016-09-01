#ifndef _KLOGGER_h
#define _KLOGGER_h

#include <iostream>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <string>
#include <vector>

#include "appender/consoleAppender.h"
#include "appender/rollingfileAppender.h"
#include "record.h"
#include "loglevel.h"

using namespace std;

#define LOG(logLevel)		 Record(logLevel, __FILE__, __FUNCTION__, __LINE__)

#define LOG_FATAL			 LOG(LOG_LEVEL::FATAL)
#define LOG_ERROR			 LOG(LOG_LEVEL::ERROR)
#define LOG_WARN			 LOG(LOG_LEVEL::WARN)
#define LOG_INFO			 LOG(LOG_LEVEL::INFO)
#define LOG_DEBUG			 LOG(LOG_LEVEL::DEBUG)
#define LOG_VERBOSE			 LOG(LOG_LEVEL::VERBOSE)

#define LOGF				 LOG_FATAL
#define LOGE				 LOG_ERROR
#define LOGW				 LOG_WARN
#define LOGI				 LOG_INFO
#define LOGD				 LOG_DEBUG
#define LOGV				 LOG_VERBOSE

class KLog
{
	public:
		KLog (LOG_LEVEL);
		~KLog ();

		KLog& addAppender (Appender*);
		void setLogLevel (LOG_LEVEL);
		KLog& operator << (const Record&);
		void write (const Record&);

	private:
		bool logAllowed (LOG_LEVEL);
		LOG_LEVEL getLogLevel () const;
		string strLogLevel (LOG_LEVEL) const;

	private:
		LOG_LEVEL m_logLevel;
		vector<Appender*> m_appenders;
};

KLog::KLog(LOG_LEVEL llevel): m_logLevel(llevel)
{

}

KLog::~KLog ()
{

}

void KLog::write (const Record& record)
{
	if (logAllowed(record.getLogLevel ()))
	{
		for (vector<Appender*>::iterator it = m_appenders.begin(); it != m_appenders.end(); it++)
			(*it)->write(record);
	}
}

string KLog::strLogLevel (LOG_LEVEL logLevel) const
{
	switch (logLevel)
	{
		case LOG_LEVEL::NONE:
			return "NONE";
		case LOG_LEVEL::FATAL:
			return "FATAL";
		case LOG_LEVEL::ERROR:
			return "ERROR";
		case LOG_LEVEL::WARN:
			return "WARN";
		case LOG_LEVEL::INFO:
			return "INFO";
		case LOG_LEVEL::DEBUG:
			return "DEBUG";
		case LOG_LEVEL::VERBOSE:
			return "VERBOSE";
		default:
			return "";
	}
}

KLog& KLog::operator << (const Record& record)
{
	return *this;	
}

bool KLog::logAllowed (const LOG_LEVEL llevel)
{
	if ( (m_logLevel == LOG_LEVEL::NONE) || (llevel == LOG_LEVEL::NONE) )
		return false;

	return llevel <= m_logLevel;
}

void KLog::setLogLevel (LOG_LEVEL llevel)
{
	m_logLevel = llevel;
}

LOG_LEVEL KLog::getLogLevel () const
{
	return m_logLevel;
}

KLog& KLog::addAppender (Appender* appender)
{
	bool find = false;
	for(vector<Appender*>::iterator it = m_appenders.begin (); it != m_appenders.end (); it++)
	{
		if ((*it) == appender)	
		{
			find = true;
			break;
		}
	}
	if (!find)
		m_appenders.push_back (appender);

	return *this;	
}

/*KLog& KLog::rmAppender (Appender* appender)
{
	for(vector<Appender*>::iterator it = m_appenders.begin (); it != m_appenders.end (); it++)
	{
		if ((*it) == appender)
		{
			m_appenders.erase(it);
			break;
		}
	}

	return *this;
}
*/

#endif
