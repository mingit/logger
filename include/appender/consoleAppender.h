#ifndef _CONSOLEAPPENDER_h
#define _CONSOLEAPPENDER_h

#include <mutex>
#include <iostream>

#include "appender/appender.h"
#include "formatter/textFormatter.h"

using namespace std;

template<class Formatter>
class ConsoleAppender : public Appender
{
	public:
		ConsoleAppender()
		{
		}

		virtual void write(const Record& record)
		{
			m_mutex.lock();
			cout << Formatter::format(record) << flush;//std::cout is thread safe in c++11
			m_mutex.unlock();
		}
	private:
		mutex     m_mutex;
};

#endif
