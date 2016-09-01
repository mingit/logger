What: C++ Logger Class
When: August 2016
Who: Dr. Ming Li (Author)
		- Email: ming.li@aalto.fi

Brief introduction:
	- This is a C++ log header only library.
	- No 3rd-party dependencies.
	- Simple, small, flexible and efficient.
	- Extendable for further development.
	- Multiple-thread safe.
	- Support custom type input and output.
	- Support multiple log objects each with separate configuration.

Programming environment: 
	- OS: Ubuntu 16.04
	- Compiler: g++ -std=c++11

Assignment requirement:
	1. Implementation language is C++ (with C++11 features available)
	2. Support multiple threads
	3. Support multiple outputs (file, console etc.)
	4. Support outputting user types
	5. Documents and validation with unit tests
	6. Work either on Windows (preferred), Max OS X, or Linux

Requirement satisfaction:
	1. C++ is used and a few C++11 features, for example, Chrono, string, auto, mutex, cout, thread, etc.
	2. Multiple threads safe
	3. Multiple outputs 
		- custom output		(e.g., class customListAppender		in ./include/custom/customappender.h)
		- console			(e.g., class ConsoleAppender		in ./include/appender/consoleAppender.h)
		- file				(e.g., class RollingFileAppender	in ./include/appender/rollingfileAppender.h)
	4. Custom types
		- custom type		(e.g., Struct Point					in ./include/custom/customtype.h) 
		- custom formatter	(e.g., Class CustomFormatter		in ./include/custom/customformatter.h)
	5. Documents and validation:
		- document: readme.txt
		- validation: YES 
	6. Only work on Linux.

Additional features:
	- Support multiple KLog objects in one program each with seperate configuration.
	- Set the log level threshold value dynamically.

File structure:
   ./ 
   |
   |---Makefile
   |
   |---readme.txt
   |
   |___obj-------*.o
   |
   |___bin-------standalone executables
   |
   |___data------*.dat (rolling log files)
   |
   |___tests-----*.cpp (each file has a main function)
   |
   |___include
             |
             |---klog.h
             |
             |---record.h
             |
             |---loglevel.h
             |
             |___formatter----textFormatter.h
             |
             |___custom-------customtype.h, customappender.h, customerformatter.h
             |
             |___appender-----appender.h, consoleAppender.h, rollingfileAppender.h

Log data flow:
   --->LOG{F|E|W|D|I|V} macro--->Record--->KLog--->Appenders--->output
									              (Formatter) 

Compile and Run:
	- Compile: 
		- make
		- (or) g++ -std=c++11 tests/XXX.cpp -I./include -lpthread -o bin/XXX
			e.g., 
		       g++ -std=c++11 tests/customtype.cpp -I./include -lpthread -o bin/customtype
			   g++ -std=c++11 tests/customoutput.cpp -I./include -lpthread -o bin/customoutput
	- Run:  
		- ./bin/XXX
		  e.g.,
			./bin/customtype
		    ./bin/customoutput

Use it in your project:
	- Add #include "klog.h"
	- Add ./include in your header path
	- Refer to ./tests/general.cpp for basic operations

Tests: 
	- four dedicated programs were made to validate the log system
		- tests/customtype.cpp
		- tests/customoutput.cpp
		- tests/multithread.cpp
		- tests/customoutput-multithread.cpp

Know problems:
	- namespace was added yet.

Further development:
	- Add more message formatters, for example, CVS and XML formatters.
	- Add new output to support remote server logging.
	- Add new functionalities for rolling log files. For example, rolling log files according to date or compressing old log files regularly.
	- Change log level threshold value in runtime. For example, adopt configuration file to manage the log level threshold.
