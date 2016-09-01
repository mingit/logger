#include <string>
#include <thread>
#include <iostream>

#include "klog.h"
#include "custom/customtype.h"

using namespace std;

int main (void)
{
	KLog log (LOG_LEVEL::VERBOSE);

	size_t maxFileSize = 1000 * 1000 * 1;//about 1MB
	long maxFileNum = 10;
	RollingFileAppender<TextFormatter> fileAppender("data/RollingFileLogs.dat", maxFileSize, maxFileNum);
	ConsoleAppender<TextFormatter> consoleAppender;

	log.addAppender (&fileAppender);
	log.addAppender (&consoleAppender);

	Point pt1 = {1, 2};//Custom type defined in custom/customtype.h
	Point pt2 = {3, 4};

	for (auto i = 1; i <= 1000; i++)
	{
		switch (i%6)
		{
			case 0:
				log.write (LOGF << i << " Custom type! " << pt1 << pt2);
				break;
			case 1:
				log.write (LOGE << i << " Custom type! " << pt1 << pt2);
				break;
			case 2:
				log.write (LOGW << i << " Custom type! " << pt1 << pt2);
				break;
			case 3:
				log.write (LOGD << i << " Custom type! " << pt1 << pt2);
				break;
			case 4:
				log.write (LOGI << i << " Custom type! " << pt1 << pt2);
				break;
			case 5:
				log.write (LOGV << i << " Custom type! " << pt1 << pt2);
				break;
			default:
				break;
		}
	}

	return 1;
}


