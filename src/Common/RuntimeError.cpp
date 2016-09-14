


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
#ifndef LIGHTINK_COMMON_RUNTIMEERROR_CPP_
#define LIGHTINK_COMMON_RUNTIMEERROR_CPP_

#include "Common/RuntimeError.h"



#define LIGHTINK_DEFINE_ERROR_DES(code, des) \
	template <> \
	const char * RuntimeErrorDes<code>::error = des


#define LIGHTINK_GET_ERROR_DES_BEGIN(name)\
LIGHTINK_GET_RUNTIMEERROR_DES_FUNC(name) \
{ \
	switch (e) \
	{ \

#define LIGHTINK_GET_ERROR_DES_END \
	default: \
	break; \
	} \
	return RuntimeErrorDes<RE_UnknownError>::error; \
} \

#define LIGHTINK_GET_ERROR_DES(code) \
case code:\
	return RuntimeErrorDes<code>::error;

namespace LightInk
{

	template<RuntimeError e>
	const char * RuntimeErrorDes<e>::error = "Undefined Error!!!";

	//¥ÌŒÛ√Ë ˆ
	LIGHTINK_DEFINE_ERROR_DES(RE_Success, "Sucess!!!");
	LIGHTINK_DEFINE_ERROR_DES(RE_ThreadSelfExit, "Thread Self Exit!!!");
	LIGHTINK_DEFINE_ERROR_DES(RE_UnknownError, "Error!!!Unknown --> Unknown Error!!!");

	LIGHTINK_DEFINE_ERROR_DES(RE_Memory_MemoryNotEnoughError, "Error!!!Memory --> Memory Is Not Enought!!!");
	LIGHTINK_DEFINE_ERROR_DES(RE_Memory_MemoryOutofRange, "Error!!!Memory --> Memory Is Outof Range!!!");

	LIGHTINK_DEFINE_ERROR_DES(RE_Lua_ThisStateInited, "Error!!!Lua --> This Lua State Has Already Init!!!");
	LIGHTINK_DEFINE_ERROR_DES(RE_Lua_NewStateFailed, "Error!!!Lua --> New Lua State Failed!!!");
	LIGHTINK_DEFINE_ERROR_DES(RE_Lua_StringEmpty, "Error!!!Lua --> Lua Call Arg Is Empty String!!!");
	LIGHTINK_DEFINE_ERROR_DES(RE_Lua_RuntimeError, "Error!!!Lua --> Lua Runtime Error, The Error Info Look Script Error Info!!!");
	LIGHTINK_DEFINE_ERROR_DES(RE_Lua_TheDataIsNil, "Error!!!Lua --> Lua The Data Is Nil!!!");
	LIGHTINK_DEFINE_ERROR_DES(RE_Lua_StackTopNotTable, "Error!!!Lua --> The Lua Stack Top Is Not A Table!!!");
	LIGHTINK_DEFINE_ERROR_DES(RE_Lua_ClassNotRegister, "Error!!!Lua --> The Class Not Register!!!");
	LIGHTINK_DEFINE_ERROR_DES(RE_Lua_HaveLoadedConfig, "Error!!!Lua --> Have Loaded Config!!!");
	LIGHTINK_DEFINE_ERROR_DES(RE_Lua_HaveNoLoadedConfig, "Error!!!Lua --> Have No Loaded Config!!!");
	LIGHTINK_DEFINE_ERROR_DES(RE_Lua_TypeError, "Error!!!Lua --> Lua Object Type Error!!!");
	LIGHTINK_DEFINE_ERROR_DES(RE_Lua_ConfigCommentError, "Error!!!Lua --> The Config Comment Error!!!");
	LIGHTINK_DEFINE_ERROR_DES(RE_Lua_LuaEngineNotInit, "Error!!!Lua --> The Lua Engine Is Not Inited!!!");
	LIGHTINK_DEFINE_ERROR_DES(RE_Lua_CheckConfigError, "Error!!!Lua --> Check Server Config Error!!!Config Have Some Problem!!!");


	//¥ÌŒÛ¥˙¬Î∫Õ¥ÌŒÛ√Ë ˆ”≥…‰
	LIGHTINK_GET_ERROR_DES_BEGIN(get_runtime_error)


	LIGHTINK_GET_ERROR_DES(RE_Success)
	LIGHTINK_GET_ERROR_DES(RE_ThreadSelfExit)
	LIGHTINK_GET_ERROR_DES(RE_UnknownError)


	LIGHTINK_GET_ERROR_DES(RE_Memory_MemoryNotEnoughError)
	LIGHTINK_GET_ERROR_DES(RE_Memory_MemoryOutofRange)

	LIGHTINK_GET_ERROR_DES(RE_Lua_ThisStateInited)
	LIGHTINK_GET_ERROR_DES(RE_Lua_NewStateFailed)
	LIGHTINK_GET_ERROR_DES(RE_Lua_StringEmpty)
	LIGHTINK_GET_ERROR_DES(RE_Lua_RuntimeError)
	LIGHTINK_GET_ERROR_DES(RE_Lua_TheDataIsNil)
	LIGHTINK_GET_ERROR_DES(RE_Lua_StackTopNotTable)
	LIGHTINK_GET_ERROR_DES(RE_Lua_ClassNotRegister)
	LIGHTINK_GET_ERROR_DES(RE_Lua_HaveLoadedConfig)
	LIGHTINK_GET_ERROR_DES(RE_Lua_HaveNoLoadedConfig)
	LIGHTINK_GET_ERROR_DES(RE_Lua_TypeError)
	LIGHTINK_GET_ERROR_DES(RE_Lua_ConfigCommentError)
	LIGHTINK_GET_ERROR_DES(RE_Lua_LuaEngineNotInit)
	LIGHTINK_GET_ERROR_DES(RE_Lua_CheckConfigError)


	LIGHTINK_GET_ERROR_DES_END

	LIGHTINK_GET_RUNTIMEERROR_DES_FUNC_INT(get_runtime_error_int)
	{
		return get_runtime_error((RuntimeError)e);
	}
}

#undef LIGHTINK_DEFINE_ERROR_DES
#undef LIGHTINK_GET_ERROR_DES_BEGIN
#undef LIGHTINK_GET_ERROR_DES
#undef LIGHTINK_GET_ERROR_DES_END

#endif