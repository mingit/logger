#ifndef _CUSTOMAPPENDER_h 
#define _CUSTOMAPPENDER_h 

////Custom Appender example - shows how to add a custom outputer in the log stream

#include <list>
#include <mutex>
#include <string>
#include <fcntl.h>
#include <iostream>
#include <sys/stat.h>

#include "record.h"
#include "appender/appender.h"

using namespace std;

template<class Formatter>                                                        
class CustomListAppender : public Appender//All appenders MUST inherit Appender interface
{
	public:
		CustomListAppender(long maxItems):m_maxItems (maxItems)
	{
	}

		~CustomListAppender ()
		{
		}

		virtual void write(const Record& record)//write is a method from Appender that MUST be implemented 
		{
			m_mutex.lock();

			if (m_messages.size () >= m_maxItems)
				m_messages.pop_front ();//remove oldest item

			m_messages.push_back(TextFormatter::format(record));

		    m_mutex.unlock();	
		}

		void print ()
		{
			m_mutex.lock();
		
			for (auto& message: m_messages)
				cout << message;
			cout << flush;
			m_mutex.unlock ();
		}

	private:
		unsigned long     m_maxItems;//upper limit of a list container 
		list<string>      m_messages;
		mutex			  m_mutex;
};

#endif
