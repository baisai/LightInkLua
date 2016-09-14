


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
#ifndef LIGHTINK_COMMON_LOGMSG_H_
#define LIGHTINK_COMMON_LOGMSG_H_

#include <cstdio>
#include "Config.h"

namespace LightInk
{
	class LIGHTINK_DECL LogMsg
	{
	public:
		enum LEVEL
		{
			LogMsg_Trace = 0x1,
			LogMsg_Debug = 0x2,
			LogMsg_Message = 0x4,
			LogMsg_Warning = 0x8,
			LogMsg_Error = 0x10,
			LogMsg_ScriptDebug = 0x20,
			LogMsg_ScriptMessage = 0x40,
			LogMsg_ScriptWarning = 0x80,
			LogMsg_ScriptError = 0x100,
			
		};
		enum SIZE
		{
			CacheChar = 4096,
		};

		typedef int (* WriterCallType)(const char * file, unsigned int line, int type, const char * mess);

		LogMsg();

		~LogMsg();

		static LogMsg * get_instance();

		void set_writer(WriterCallType writer);

		inline bool is_trace() {return (LogMsg_Trace & m_level) != 0;}
		inline bool is_debug() {return (LogMsg_Debug & m_level) != 0;}
		inline bool is_message() {return (LogMsg_Message & m_level) != 0;}
		inline bool is_warning() {return (LogMsg_Warning & m_level) != 0;}
		inline bool is_error() {return (LogMsg_Error & m_level) != 0;}
		inline bool is_script_debug() {return (LogMsg_ScriptDebug & m_level) != 0;}
		inline bool is_script_message() {return (LogMsg_ScriptMessage & m_level) != 0;}
		inline bool is_script_warning() {return (LogMsg_ScriptWarning & m_level) != 0;}
		inline bool is_script_error() {return (LogMsg_ScriptError & m_level) != 0;}

		inline void set_trace() {m_level ^= LogMsg_Trace;}
		inline void set_debug() {m_level ^= LogMsg_Debug;}
		inline void set_message() {m_level ^= LogMsg_Message;}
		inline void set_warning() {m_level ^= LogMsg_Warning;}
		inline void set_error() {m_level ^= LogMsg_Error;}
		inline void set_script_debug() {m_level ^= LogMsg_ScriptDebug;}
		inline void set_script_message() {m_level ^= LogMsg_ScriptMessage;}
		inline void set_script_warning() {m_level ^= LogMsg_ScriptWarning;}
		inline void set_script_error() {m_level ^= LogMsg_ScriptError;}



		int debug(const char * file, unsigned int line, const char * mess);
		int message(const char * file, unsigned int line, const char * mess);
		int warning(const char * file, unsigned int line, const char * mess);
		int error(const char * file, unsigned int line, const char * mess);
		int script_debug(const char * file, unsigned int line, const char * mess);
		int script_message(const char * file, unsigned int line, const char * mess);
		int script_warning(const char * file, unsigned int line, const char * mess);
		int script_error(const char * file, unsigned int line, const char * mess);
		int trace_in(const char * file, unsigned int line, const char * mess);
		int trace_out(const char * file, unsigned int line, const char * mess);

	protected:

		int writer_log(const char * file, unsigned int line, int type, const char * mess);

	protected:
		unsigned int m_level;
		WriterCallType m_writer;
	};



	class LIGHTINK_DECL LogMsgTrace
	{
	public:
		LogMsgTrace(char * file, unsigned int line, char * func);
		inline void set_line(unsigned int line) {m_line = line;}
		~LogMsgTrace();
	protected:
		char * m_file;
		unsigned int m_line;
		char * m_func;
	};
	
}

#define LightInkLog LightInk::LogMsg::get_instance()

#endif