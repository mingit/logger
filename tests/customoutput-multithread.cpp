#include <string>
#include <thread>
#include <iostream>
#include <list>

#include "klog.h"
#include "custom/customappender.h"

using namespace std;

void writeLogThread (KLog* log, long num)
{
	for (auto i = 1; i <= num; i++)
	{
		switch (i%6)
		{
			case 0://LOG_LEVEL::FATAL
				log->write (LOGF << i << " Hello world!");
				break;
			case 1://LOG_LEVEL::ERROR
				log->write (LOGE << i << " Hello world!");
				break;
			case 2://LOG_LEVEL::WARN
				log->write (LOGW << i << " Hello world!");
				break;
			case 3://LOG_LEVEL::DEBUG
				log->write (LOGD << i << " Hello world!");
				break;
			case 4://LOG_LEVEL::INFO
				log->write (LOGI << i << " Hello world!");
				break;
			case 5://LOG_LEVEL::VERBOSE
				log->write (LOGV << i << " Hello world!");
				break;
			default:
				break;
		}
	}
}

void printThread (CustomListAppender<TextFormatter>* appender)
{
	appender->print();
}

int main (void)
{
	const long num_threads = 10;
	const long messages_per_thread = 100;

	KLog log (LOG_LEVEL::VERBOSE);

	CustomListAppender<TextFormatter> customListAppender(100);//only store the latest 100 records

	log.addAppender (&customListAppender);

	vector<thread> threads;
	threads.reserve (num_threads*2);
    for (auto i = 0; i < num_threads; i++)	
	{
		threads.emplace_back(writeLogThread, &log, messages_per_thread);
		threads.emplace_back(printThread, &customListAppender);
	}
	
	for( auto& t : threads ) 
		t.join() ;

	return 1;
}
