#ifndef _KAPPENDER_h
#define _KAPPENDER_h

#include "record.h"

class Appender
{
	public:
		virtual ~Appender () {}

		virtual void write (const Record& record) = 0;
};

#endif
