


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
#include "LuaEngine/LuaEngine.h"
#include "LuaEngine/LuaDefTool.h"
#include "Common/SmallObject.h"

namespace LightInk
{
	LuaEngine::LuaEngine() : m_lua(NULL)
	{
		LogTrace("LuaEngine::LuaEngine()");
		LogTraceReturnVoid;
	}

	LuaEngine::~LuaEngine()
	{
		LogTrace("LuaEngine::~LuaEngine()");
		close();
		LogTraceReturnVoid;
	}

	lua_State * LuaEngine::get_lua_state()
	{
		LogTrace("lua_State * LuaEngine::get_lua_state()");
		LogTraceReturn(m_lua);
	}

	bool LuaEngine::is_inited()
	{
		LogTrace("bool LuaEngine::is_inited()");
		LogTraceReturn(m_lua != NULL);
	}

	RuntimeError LuaEngine::init()
	{
		LogTrace("RuntimeError LuaEngine::init()");
		if (m_lua)
		{
			LogTraceReturn(RE_Lua_ThisStateInited);
		}
		m_lua = lua_newstate(LuaEngine::lua_allocator, this);
		if (!m_lua)
		{
			LogTraceReturn(RE_Lua_NewStateFailed);
		}
		lua_atpanic(m_lua, LuaEngine::lua_error_catch);
		luaL_openlibs(m_lua);
		register_global_func("get_userdata_property", &LuaIndexMetatable::gt_index_function);
		register_global_func("set_userdata_property", &LuaIndexMetatable::gt_newindex_function);
		LuaDefTool::def_func(m_lua, get_runtime_error_int, "get_runtime_error");
		register_global_func("print", &lua_replace_print);
		register_global_func("print_debug", &lua_print_debug);
		register_global_func("print_warning", &lua_print_warning);
		register_global_func("print_error", &lua_print_error);
		register_global_func("print_fatal", &lua_print_fatal);
		LogTraceReturn(do_init());
	}

	void LuaEngine::close()
	{
		LogTrace("void LuaEngine::close()");
		if (m_lua)
		{
			do_close();
			lua_close(m_lua);
			m_lua = NULL;
		}
		LogTraceReturnVoid;
	}

	void * LuaEngine::lua_allocator(void * ud, void * ptr, size_t osize, size_t nsize)
	{
		LogTrace("void * LuaEngine::lua_allocator(void * ud, void * ptr, size_t osize, size_t nsize)");
		LuaEngine * p = (LuaEngine *)ud;
		LogTraceReturn(p->do_lua_allocator(ptr, osize, nsize));
	}

	int LuaEngine::lua_error_catch(lua_State * L)
	{
		LogTrace("int LuaEngine::lua_error_catch(lua_State * L)");
		const char * errStr = lua_tostring(L, -1);
		LogError("Error!!!Lua Error Catch \"%s\"", errStr);
		throw RE_Lua_RuntimeError;
		LogTraceReturn(0);
	}

	int LuaEngine::log_string(lua_State * L, LogLevel::LEVEL level)
	{
		LogTrace("int LuaEngine::log_string(lua_State * L, LogMsg::LEVEL level)");
		int n = lua_gettop(L) + 1;  /* number of arguments */
		lua_getglobal(L, "tostring");
	
		const char * s = NULL;

		std::string str;
	
		for (int i = 1; i < n; i++)
		{
		
			lua_pushvalue(L, -1);  /* function to be called */
			lua_pushvalue(L, i);   /* value to print */
			lua_call(L, 1, 1);
		
			s = lua_tostring(L, -1);  /* get result */
			if (s == NULL)
			{
				LogTraceReturn(luaL_error(L, "\'tostring\' must return a string to \'print\'"));
			}

			str += s;
			str.push_back('\t');
		
			lua_pop(L, 1);  /* pop result */
		}
	
		switch (level)
		{
		case LogLevel::LogMsg_Debug:
			LogScriptDebug(str.c_str());
			break;
		case LogLevel::LogMsg_Message:
			LogScriptMessage(str.c_str());
			break;
		case LogLevel::LogMsg_Warning:
			LogScriptWarning(str.c_str());
			break;
		case LogLevel::LogMsg_Error:
			LogScriptError(str.c_str());
			break;
		case LogLevel::LogMsg_Fatal:
			LogScriptFatal(str.c_str());
			break;
		default:
			break;
		}
		LogTraceReturn(0);
	}

	int LuaEngine::lua_print_debug(lua_State * L)
	{
		LogTrace("int LuaEngine::lua_print_debug(lua_State * L)");
		LogTraceReturn(LuaEngine::log_string(L, LogLevel::LogMsg_Debug));
	}
	int LuaEngine::lua_replace_print(lua_State * L)
	{
		LogTrace("int LuaEngine::lua_replace_print(lua_State * L)");
		LogTraceReturn(LuaEngine::log_string(L, LogLevel::LogMsg_Message));
	}
	int LuaEngine::lua_print_warning(lua_State * L)
	{
		LogTrace("int LuaEngine::lua_print_warning(lua_State * L)");
		LogTraceReturn(LuaEngine::log_string(L, LogLevel::LogMsg_Warning));
	}
	int LuaEngine::lua_print_error(lua_State * L)
	{
		LogTrace("int LuaEngine::lua_print_error(lua_State * L)");
		LogTraceReturn(LuaEngine::log_string(L, LogLevel::LogMsg_Error));
	}
	int LuaEngine::lua_print_fatal(lua_State * L)
	{
		LogTrace("int LuaEngine::lua_print_fatal(lua_State * L)");
		LogTraceReturn(LuaEngine::log_string(L, LogLevel::LogMsg_Fatal));
	}

	void * LuaEngine::do_lua_allocator(void * ptr, size_t osize, size_t nsize)
	{
		LogTrace("void * LuaEngine::do_lua_allocator(void * ptr, size_t osize, size_t nsize)");
		LogTraceReturn(SmallObject::realloc_user(ptr, osize, nsize));
	}

	RuntimeError LuaEngine::do_init()
	{ LogTrace("RuntimeError LuaEngine::do_init()"); LogTraceReturn(RE_Success); }
	void LuaEngine::do_close()
	{ LogTrace("void LuaEngine::do_close()"); LogTraceReturnVoid; }

	
	RuntimeError LuaEngine::add_package_path(const std::string & path)
	{
		LogTrace("RuntimeError LuaEngine::add_package_path(const string & path)");
		std::string new_path = "package.path = package.path .. \"";
        if (path.empty())
        {
            LogTraceReturn(RE_Lua_StringEmpty);
        }

        if (path[0] != ';')
        {
           new_path += ";";
        }

        new_path += path;
        if (path[path.length() - 1] != '/')
        {
            new_path += "/";
        }
        new_path += "?.lua\"";


		run_string(new_path.c_str());
		LogTraceReturn(RE_Success);
	}

	void LuaEngine::clear_package_path()
	{
		LogTrace("void LuaEngine::clear_package_path()");
		run_string("package.path = \";./?.lua\"");
		LogTraceReturnVoid;
	}

	void LuaEngine::dump_stack(lua_State * L)
	{
		LogTrace("void LuaEngine::dump_stack(lua_State * L)");
		 int top = lua_gettop(L);
        for (int i = 1; i <= top; i++)
        {
            int t = lua_type(L, i);
            switch (t)
            {
                case LUA_TSTRING:
                {
					LogMessage("`%s`", lua_tostring(L, i));
                }
                break;
                case LUA_TBOOLEAN:
                {
                    LogMessage(lua_toboolean(L, i) ? "true" : "false");
                }
                break;
                case LUA_TNUMBER:
                {
					LogMessage("`%g`", lua_tonumber(L, i));
                }
                break;
                case LUA_TTABLE:
                {
                	LogMessage("table begin\n");
                    lua_pushnil(L);
                    while (lua_next(L, i) != 0)
					{
						const char * key = NULL;
						if (lua_isstring(L, -2))
						{
							key = lua_tostring(L, -2);
							LogMessage("\t%s(%s) - %s\n",
								lua_typename(L, lua_type(L, -2)), key,
								lua_typename(L, lua_type(L, -1)));
						}
						else
						{
							LogMessage("\t%s - %s\n",
								lua_typename(L, lua_type(L, -2)),
								lua_typename(L, lua_type(L, -1)));
						}
						lua_pop(L, 1);
                    }
					LogMessage("table end\n");
                }
                break;
                default:
                {
					LogMessage("`%s`", lua_typename(L, t));
                }
                break;
            }
            LogMessage(" ");
        }
        LogMessage("\n");
		LogTraceReturnVoid;
	}

	RuntimeError LuaEngine::run_string(const char * chunk)
	{
		LogTrace("RuntimeError LuaEngine::run_string(const char * chunk)");
		if (luaL_dostring(m_lua, chunk))
		{
			const char * err = lua_tostring(m_lua, -1);
			LogScriptError("Call LuaEngine::run_string Error!!! error is \"%s\"", err);
			lua_pop(m_lua, 1); //pop error
			LogTraceReturn(RE_Lua_RuntimeError);
		}
		LogTraceReturn(RE_Success);
	}

	RuntimeError LuaEngine::run_file(const char * fileName)
	{
		LogTrace("RuntimeError LuaEngine::run_file(const char * fileName)");
		if (luaL_dofile(m_lua, fileName))
		{
			const char * err = lua_tostring(m_lua, -1);
			LogScriptError("Call LuaEngine::run_file Error!!! error is \"%s\" \n chunk is \"%s\"\n", err, fileName);
			lua_pop(m_lua, 1); //pop error
			LogTraceReturn(RE_Lua_RuntimeError);
		}
		LogTraceReturn(RE_Success);
	}

	RuntimeError LuaEngine::require_file(const char * fileName)
	{
		LogTrace("RuntimeError LuaEngine::require_file(const char * fileName)");
		LuaStateProtect lsp(m_lua, true);
		lua_getglobal(m_lua, "require");
		lua_pushstring(m_lua, fileName);
		if (lua_pcall(m_lua, 1, 0, 0))
		{
			const char * errStr = lua_tostring(m_lua, -1);
			if (errStr) LogScriptError(errStr);
			LogTraceReturn(RE_Lua_RuntimeError);
		}
		LogTraceReturn(RE_Success);
	}

	RuntimeError LuaEngine::register_global_func(const char * func, lua_CFunction f)
	{
		LogTrace("RuntimeError LuaEngine::register_global_func(const char * func, lua_CFunction f)");
		LuaDefAutoTool::def(m_lua, f, func);
		LogTraceReturn(RE_Success);
	}

	LuaRef LuaEngine::get_global_ref(const char * name)
	{
		LogTrace("LuaRef LuaEngine::get_global_ref(const char * name)");
		lua_getglobal(m_lua, name);
		LogTraceReturn(LuaRef(m_lua, true));
	}

	void LuaEngine::register_module(void(*func)(lua_State * lua))
	{
		LogTrace("void LuaEngine::register_module(void(*func)(lua_State * lua))");
		func(m_lua);
		LogTraceReturnVoid;
	}
}