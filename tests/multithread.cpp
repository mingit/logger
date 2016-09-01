#include <string>
#include <thread>
#include <iostream>

#include "klog.h"

using namespace std;

void helloThread (KLog* log, long num)
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

int main (void)
{
	const long num_threads = 20;
	const long messages_per_thread = 1000;

	KLog log (LOG_LEVEL::VERBOSE);

	size_t maxFileSize = 1000 * 1000 * 1;//about 1MB
	long maxFileNum = 10;
	RollingFileAppender<TextFormatter> fileAppender("data/RollingFileLogs.dat", maxFileSize, maxFileNum);
	ConsoleAppender<TextFormatter> consoleAppender;

	log.addAppender (&fileAppender);
	log.addAppender (&consoleAppender);

	vector<thread> threads;
	threads.reserve (num_threads);
    for (auto i = 0; i < num_threads; i++)	
		threads.emplace_back(helloThread, &log, messages_per_thread);

	for( auto& t : threads ) 
		t.join() ;

	return 1;
}
