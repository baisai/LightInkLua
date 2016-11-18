


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

#ifndef LIGHTINK_COMMON_LOG_H_
#define LIGHTINK_COMMON_LOG_H_

#include "Common/Config.h"
#include <stdio.h>

/////////////////////////////////
//系统日志
////////////////////////////////

////////////////////////////
//Trace
///////////////////////////
#ifdef LightInkNoTrace
#define LogTrace(ft, ...)
#define LogTraceReturn(v) return v
#define LogTraceReturnVoid return
#define LogTraceEnd

#else
#define LogTrace(ft, ...) printf(ft, ##__VA_ARGS__);printf("\n")
#define LogTraceReturn(v) return v
#define LogTraceReturnVoid return
#define LogTraceEnd
#endif

////////////////////////
//Debug
///////////////////////
#ifdef LightInkNoDebug
#define LogDebug(ft, ...)
#else
#define LogDebug(ft, ...) printf(ft, ##__VA_ARGS__);printf("\n")

#endif

////////////////////////
//Message
///////////////////////
#ifdef LightInkNoMessage
#define LogMessage(ft, ...)
#else
#define LogMessage(ft, ...) printf(ft, ##__VA_ARGS__);printf("\n")

#endif

////////////////////////
//Warning
///////////////////////
#ifdef LightInkNoWarning
#define LogWarning(ft, ...)
#else
#define LogWarning(ft, ...) printf(ft, ##__VA_ARGS__);printf("\n")

#endif


////////////////////////
//Error
///////////////////////
#ifdef LightInkNoError
#define LogError(ft, ...)
#else
#define LogError(ft, ...) printf(ft, ##__VA_ARGS__);printf("\n")

#endif

////////////////////////
//Fatal
///////////////////////
#ifdef LightInkNoFatal
#define LogFatal(ft, ...)
#else
#define LogFatal(ft, ...) printf(ft, ##__VA_ARGS__);printf("\n")

#endif



////////////////////////
//ScriptDebug
///////////////////////
#ifdef LightInkNoScriptDebug
#define LogScriptDebug(ft, ...)
#else
#define LogScriptDebug(ft, ...) printf(ft, ##__VA_ARGS__);printf("\n")

#endif



////////////////////////
//ScriptMessage
///////////////////////
#ifdef LightInkNoScriptMessage
#define LogScriptMessage(ft, ...)
#else
#define LogScriptMessage(ft, ...) printf(ft, ##__VA_ARGS__);printf("\n")

#endif

////////////////////////
//ScriptWarning
///////////////////////
#ifdef LightInkNoScriptWarning
#define LogScriptWarning(ft, ...)
#else
#define LogScriptWarning(ft, ...) printf(ft, ##__VA_ARGS__);printf("\n")

#endif


////////////////////////
//ScriptError
///////////////////////
#ifdef LightInkNoScriptError
#define LogScriptError(ft, ...)
#else
#define LogScriptError(ft, ...) printf(ft, ##__VA_ARGS__);printf("\n")
	
#endif


////////////////////////
//Fatal
///////////////////////
#ifdef LightInkNoScriptFatal
#define LogScriptFatal(ft, ...)
#else
#define LogScriptFatal(ft, ...) printf(ft, ##__VA_ARGS__);printf("\n")

#endif


/////////////////////////
//ScriptError and Jump
////////////////////////
#ifdef LightInkNoScriptErrorJump
#define LogScriptErrorJump(L, fmt, ...) LogScriptError(fmt, ##__VA_ARGS__)
#else
#define LogScriptErrorJump(L, fmt, ...) luaL_error(L, fmt, ##__VA_ARGS__)
#endif

#endif