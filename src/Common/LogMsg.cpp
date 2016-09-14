


/* Copyright ChenDong(Wilbur), email <baisaichen@live.com>. All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */
#include "Common/LogMsg.h"
#include <string.h>
#include <ctime>
#include "Common/WinSnprintf.h"

namespace LightInk
{
	///////////////////////////////////////////////////////////////////
	//LogMsg
	/////////////////////////////////////////////////////////////////
	LogMsg::LogMsg():  m_level(~0), m_writer(NULL)
	{
	}

	LogMsg::~LogMsg()
	{
	}

	LogMsg * LogMsg::get_instance()
	{
		static LogMsg s_log;
		return &s_log;
	}

	void LogMsg::set_writer(WriterCallType writer)
	{
		m_writer = writer;
	}

	int LogMsg::debug(const char * file, unsigned int line, const char * mess)
	{
		if (is_debug())
		{
			char messAll[CacheChar] = {0};
			time_t t = time(NULL);
			tm* aTm = localtime(&t);
			snprintf(messAll, CacheChar, "[DEBUG]:%s", mess);
			writer_log(file, line, LogMsg_Debug, messAll);
		}
		return 0;
	}

	int LogMsg::message(const char * file, unsigned int line, const char * mess)
	{
		if (is_message())
		{
			char messAll[CacheChar] = {0};
			snprintf(messAll, CacheChar, "[MESSAGE]:%s", mess);
			writer_log(file, line, LogMsg_Message, messAll);
		}
		return 0;
	}

	int LogMsg::warning(const char * file, unsigned int line, const char * mess)
	{
		if (is_warning())
		{
			char messAll[CacheChar] = {0};
			snprintf(messAll, CacheChar, "[WARNING]:%s", mess);
			writer_log(file, line, LogMsg_Message, messAll);
		}
		return 0;
	}

	int LogMsg::error(const char * file, unsigned int line, const char * mess)
	{
		if (is_error())
		{
			char messAll[CacheChar] = {0};
			time_t t = time(NULL);
			tm* aTm = localtime(&t);
			snprintf(messAll, CacheChar, "[ERROR]:%s", mess);
			writer_log(file, line, LogMsg_Error, messAll);
		}
		return 0;
	}

	int LogMsg::script_debug(const char * file, unsigned int line, const char * mess)
	{
		if (is_script_debug())
		{
			char messAll[CacheChar] = {0};
			snprintf(messAll, CacheChar, "[DEBUG]:[LUA]:%s", mess);
			writer_log(file, line, LogMsg_ScriptDebug, messAll);
		}
		return 0;
	}

	int LogMsg::script_message(const char * file, unsigned int line, const char * mess)
	{
		if (is_script_message())
		{
			char messAll[CacheChar] = {0};
			snprintf(messAll, CacheChar, "[MESSAGE]:[LUA]:%s", mess);
			writer_log(file, line, LogMsg_ScriptMessage, messAll);
		}
		return 0;
	}

	int LogMsg::script_warning(const char * file, unsigned int line, const char * mess)
	{
		if (is_script_warning())
		{
			char messAll[CacheChar] = {0};
			snprintf(messAll, CacheChar, "[WARNING]:[LUA]:%s", mess);
			writer_log(file, line, LogMsg_ScriptMessage, messAll);
		}
		return 0;
	}

	int LogMsg::script_error(const char * file, unsigned int line, const char * mess)
	{
		if (is_script_error())
		{
			char messAll[CacheChar] = {0};
			snprintf(messAll, CacheChar, "[ERROR]:[LUA]:%s",  mess);
			writer_log(file, line, LogMsg_ScriptError, messAll);
		}
		return 0;
	}

	int LogMsg::trace_in(const char * file, unsigned int line, const char * mess)
	{
		if (is_trace())
		{
			char messAll[CacheChar] = {0};
			snprintf(messAll, CacheChar, "[TRACE]:call function[%s]", mess);
			writer_log(file, line, LogMsg_Trace, messAll);
		}
		return 0;
	}

	int LogMsg::trace_out(const char * file, unsigned int line, const char * mess)
	{
		if (is_trace())
		{
			char messAll[CacheChar] = {0};
			snprintf(messAll, CacheChar, "[TRACE]:leave function[%s]", mess);
			writer_log(file, line, LogMsg_Trace, messAll);
		}
		return 0;
	}

	int LogMsg::writer_log(const char * file, unsigned int line, int type, const char * mess)
	{
		if (m_writer)
		{
			m_writer(file, line, type, mess);
		}
		else
		{
			time_t t = time(NULL);
			tm* aTm = localtime(&t);
			char timeStr[48] = {0};
			snprintf(timeStr, 48, "[%-4d-%02d-%02d %02d:%02d:%02d]", aTm->tm_year+1900,aTm->tm_mon+1,aTm->tm_mday,aTm->tm_hour,aTm->tm_min,aTm->tm_sec);
			printf("%s%s\n", timeStr, mess);
		}
		return 0;
	}

	///////////////////////////////////////////////////////////////////
	//LogMsgTrace
	/////////////////////////////////////////////////////////////////
	LogMsgTrace::LogMsgTrace(char * file, unsigned int line, char * func): m_file(file), m_line(line), m_func(func)
	{
		LightInkLog->trace_in(file, line, func);
	}

	LogMsgTrace::~LogMsgTrace()
	{
		LightInkLog->trace_out(m_file, m_line, m_func);
	}

	////////////////////////////////////////////////////////////////
	//LogMsgMgr
	///////////////////////////////////////////////////////////////


}