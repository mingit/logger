#ifndef _KRECORD_h
#define _KRECORD_h

#include <linux/unistd.h>
#include <unistd.h>
#include <sstream>
#include <iostream>
#include <string>
#include <cstring>
#include <chrono>

#include "loglevel.h"

using namespace std;

class Record
{
	public:
		Record (LOG_LEVEL, const char*, const char*, unsigned long);
		
		Record& operator << (const int);
		Record& operator << (const char);
		Record& operator << (const string);
		Record& operator << (const float);

		string getFile () const;
		string getFunction () const;
		string strLogLevel () const;
		string getTid () const;
		unsigned long getLine() const;
		const time_t getTime () const;
		const void* getObject () const;
		LOG_LEVEL getLogLevel () const;
		const string getMessage () const;
		
	private:	
		const LOG_LEVEL		m_logLevel;
		const char*			m_file;
		const char*			m_function; 
		const unsigned long m_line; 
		time_t				m_time;
		stringstream		m_message;
};

Record::Record (LOG_LEVEL llevel, const char* file, const char* function, unsigned long line)
			: m_logLevel(llevel)
			  , m_file(file)
			  , m_function(function)
			  , m_line(line)
			  , m_time (chrono::system_clock::to_time_t (chrono::system_clock::now()))
	{

	}

string Record::strLogLevel () const
{
	switch (m_logLevel)
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

const time_t Record::getTime () const
{
	return m_time;
}

string Record::getFile () const
{
	return string (m_file);
}

string Record::getFunction () const
{
	const char* funcBegin = m_function;
	const char* funcEnd = ::strchr(funcBegin, '(');

	if (funcEnd != NULL)
		return string(m_function);
	else
		funcEnd = ::strchr(funcBegin, '\0');

	for (const char* i = funcEnd - 1; i >= funcBegin; --i) // search backwards for the first space char
	{
		if (*i == ' ')
		{
			funcBegin = i + 1;
			break;
		}
	}

	return string(funcBegin, funcEnd);
} 

Record& Record::operator << (const string data)
{
	m_message << data;
	return *this;
}

Record& Record::operator << (const int data)
{
	m_message << data; 
	return *this; 
}

Record& Record::operator << (const float data)
{
	m_message << data; 
	return *this; 
}

Record& Record::operator << (const char data)
{
	char str[] = {data, 0};
	*this << str;
	return *this;
}

LOG_LEVEL Record::getLogLevel () const
{
	return m_logLevel;
}

string Record::getTid () const
{
	//this_thread::get_id() gives confusing id if there is no other threads in addition to the main thread.
	//pthread_self()
	//static_cast<unsigned long>(::syscall(__NR_gettid))

	stringstream ss;
	ss << pthread_self();

	return ss.str();
}

unsigned long Record::getLine() const
{
	return m_line;
}

const string Record::getMessage () const
{
	return m_message.str();
}

#endif
