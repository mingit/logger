#ifndef _MESSAGEFORMATTER_h 
#define _MESSAGEFORMATTER_h

#include <iomanip>
#include <string>

#include "record.h"
#include "loglevel.h"

using namespace std;

class TextFormatter
{
	public:
		static string header ()
		{
			//return string ("TextFormatter is used.\nLog level|Data Time|Thread ID|File name|Function name|Line number|\"Message\"\n\n");
			return string ();
		}

		static string format(const Record& record)
		{
			const time_t time_rd = record.getTime();
			stringstream ss;

			ss << record.strLogLevel ()
			   << "|" << put_time (localtime (&time_rd), "%Y-%m-%d %X") 
			   << "|" << record.getTid ()
			   << "|" << record.getFile() 
			   << "|" << record.getFunction() 
			   << "|" << record.getLine() 
			   << "|" << "\"" << record.getMessage() << "\"" << "\n";
			
			return ss.str();
		}
};

#endif
