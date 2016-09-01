#ifndef _CUSTOMFORMATTER_h 
#define _CUSTOMFORMATTER_h 

////Custom formatter example - shows how to format messages according to user's preference 

#include <list>
#include <string>
#include <iostream>

#include "appender/appender.h"
#include "record.h"

using namespace std;

class CustomFormatter
{
	public:
		static string header() // This method returns a header for a new file.
		{
			//return string("CustomFormatter is used.\n\"message\"\n\n");
			return string();
		}

		static string format(const Record& record)
		{
			stringstream ss;
			ss << "\"" << record.getMessage().c_str() << "\"" << "\n"; 
			return ss.str();
		}
};

#endif
