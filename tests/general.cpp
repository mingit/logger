#include <string>
#include <thread>
#include <iostream>

#include "klog.h"/////////////////// Step1: Add header
#include "custom/customformatter.h"// add it if you want to try the custom formatter

using namespace std;

int main (void)
{
	KLog log (LOG_LEVEL::WARN);///// Step2: create a KLog object

	/*
	Multiple KLog objects can be used in the same program. Each object has separate configuration.
	   */
	//KLog log2 (LOG_LEVEL::INFO);

	size_t maxFileSize = 1000 * 1000 * 1;//about 1MB
	long maxFileNum = 10;

	//////////////////////////////// Step3: Create appender(s) and give formatter(s)
	RollingFileAppender<TextFormatter> fileAppender("data/RollingFileLogs.dat", maxFileSize, maxFileNum);
	ConsoleAppender<CustomFormatter> consoleAppender;

	//////////////////////////////// Step4: Add appenders to KLog object
	log.addAppender (&fileAppender)
	   .addAppender (&consoleAppender);

	for (auto i = 1; i <= 20; i++)
	{
		switch (i%6)
		{
			case 0:///////////////// Step 5: Use macro to organize a Record object and then add it to KLog object
				log.write (LOGF << i << " Hello world!");
				break;
			case 1:
				log.write (LOGE << i << " Hello world!");
				break;
			case 2:
				log.write (LOGW << i << " Hello world!");
				break;
			case 3:
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

	return 1;
}


