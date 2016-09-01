#ifndef _CUSTOMTYPE_h
#define _CUSTOMTYPE_h

//Custom Type example - shows how to output a custom type to the log stream                                                                          
#include "appender/appender.h"
#include "record.h"

using namespace std;

struct Point                                                                                                                      
{
	int x;
	int y;
};

Record& operator << (Record& record, const Point& pt) // Implement a stream operator for our type.
{   
	return record << "(" << pt.x << ", " << pt.y << ")";
}

#endif
