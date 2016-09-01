#ifndef _ROLLINGFILEAPPENDER_h
#define _ROLLINGFILEAPPENDER_h

#include <mutex>
#include <fstream>
#include <ostream>
#include <fcntl.h>
#include <iostream>
#include <sys/stat.h>

#include "record.h"
#include "appender/appender.h"
#include "formatter/textFormatter.h"

using namespace std;

template<class Formatter>
class RollingFileAppender : public Appender
{
	public:
		RollingFileAppender(const char* fileName, size_t maxFileSize, unsigned long maxFiles)
			: m_fileSize()
			  , m_maxFileSize(maxFileSize) 
			  , m_lastFileNumber(maxFiles - 1)
			  , m_firstWrite(true)
	{
		splitFileName(fileName, m_fileNameNoExt, m_fileExt);
	}

		~RollingFileAppender ()
		{
			m_file.close();
		}

		virtual void write(const Record& record)
		{
			m_mutex.lock ();

			if (m_firstWrite)
			{
				openLogFile();
				m_firstWrite = false;
			}
			else if (m_lastFileNumber > 0 && m_fileSize > m_maxFileSize)
			{
				rollLogFiles();
				openLogFile();
			}

			m_file << Formatter::format(record) << flush;
			m_file.seekg(0, m_file.end);
			m_fileSize = m_file.tellg();

			m_mutex.unlock();
		}

	private:
		void openLogFile()
		{
			m_file.open (buildFileName(), fstream::out | fstream::app);

			if (m_file && m_file.is_open() && m_file.good())
			{
				m_file.clear ();
				m_file << Formatter::header();
			}
		}

		void splitFileName(const char* fileName, string& fileNameNoExt, string& fileExt)
		{
			const char* dot = strrchr(fileName, '.');

			if (dot)
			{
				fileNameNoExt.assign(fileName, dot);
				fileExt.assign(dot + 1);
			} 
			else 
			{ 
				fileNameNoExt.assign(fileName);
				fileExt.clear();
			}
		}

		void rollLogFiles()
		{
			m_file.close();
			string lastFileName = buildFileName(m_lastFileNumber);
			::unlink(lastFileName.c_str());

			for (int fileNumber = m_lastFileNumber - 1; fileNumber >= 0; --fileNumber)
			{
				string currentFileName = buildFileName(fileNumber);
				string nextFileName = buildFileName(fileNumber + 1);
				::rename(currentFileName.c_str(), nextFileName.c_str());
			}
		}

		string buildFileName(int fileNumber = 0)//fileNumber is 0 as default
		{
			stringstream ss;
			ss << m_fileNameNoExt;

			if (fileNumber > 0)
			{
				ss << fileNumber;
			}

			if (!m_fileExt.empty())
			{
				ss << '.' << m_fileExt;
			}

			return ss.str();
		}

	private:
		size_t          m_fileSize;
		const size_t    m_maxFileSize;
		const unsigned long       m_lastFileNumber;//start from 0

		mutex			m_mutex; 
		string			m_fileExt;
		string			m_fileNameNoExt;
		bool            m_firstWrite;
		fstream			m_file; 
};

#endif
