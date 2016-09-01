#include <string>
#include <thread>
#include <iostream>

#include "klog.h"
#include "custom/customappender.h"

using namespace std;

int main (void)
{
	KLog log (LOG_LEVEL::WARN);

	size_t maxFileSize = 1000 * 1000 * 1;//about 1MB
	long maxFileNum = 10;
	RollingFileAppender<TextFormatter> fileAppender("data/RollingFileLogs.dat", maxFileSize, maxFileNum);
	CustomListAppender<TextFormatter> customListAppender(20);// only store the latest 20 records

	log.addAppender (&fileAppender);
	log.addAppender (&customListAppender);

	for (auto i = 1; i <= 1000; i++)
	{
		switch (i%6)
		{
			case 0://LOG_LEVEL::FATAL
				log.write (LOGF << i << " Hello world!");
				break;
			case 1://LOG_LEVEL::ERROR
				log.write (LOGE << i << " Hello world!");
				break;
			case 2://LOG_LEVEL::WARN
				log.write (LOGW << i << " Hello world!");
				break;
			case 3://LOG_LEVEL::DEBUG
				log.write (LOGD << i << " Hello world!");
				break;
			case 4://LOG_LEVEL::INFO
				log.write (LOGI << i << " Hello world!");
				break;
			case 5://LOG_LEVEL::VERBOSE
				log.write (LOGV << i << " Hello world!");
				break;
			default:
				break;
		}
	}

	customListAppender.print ();

	return 1;
}


