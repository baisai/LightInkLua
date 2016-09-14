


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

#ifndef LIGHTINK_LUAENGINE_LUACLASSINFO_H_
#define LIGHTINK_LUAENGINE_LUACLASSINFO_H_

#include <string.h>
#include "LuaEngine/lua/lua.hpp"
#include "LuaEngine/LuaStateProtect.h"

namespace LightInk
{
	template <typename T>
	class LIGHTINK_TEMPLATE_DECL LuaClassInfo
	{
	public:
		inline static const char * get_class_name()
		{
			LogTrace("const char * LuaClassInfo<T>::get_class_name()");
			LogTraceReturn(m_className);
		}
		static bool set_class_name(const char * name)
		{
			LogTrace("bool LuaClassInfo<T>::set_class_name(const char * name)");
			if (is_registered())
			{
				LogTraceReturn(true);
			}
			strncpy(m_className, name, 128);
			LogTraceReturn(false);
		}
		inline static void * get_class_key()
		{
			LogTrace("void * LuaClassInfo<T>::get_class_key()");
			LogTraceReturn(&m_key);
		}

		inline static bool is_registered()
		{
			LogTrace("bool LuaClassInfo<T>::is_registered()");
			LogTraceReturn((m_className[0] != '\0'));
		}

		static bool get_class_table(lua_State * L)
		{
			LogTrace("bool LuaClassInfo<T>::get_class_table(lua_State * L)");
			if (!is_registered() || m_classTable == LUA_REFNIL)
			{
				LogScriptError("Error!!!This  class %s is not register!!!", m_className);
				LogTraceReturn(false);
			}
			lua_rawgeti(L, LUA_REGISTRYINDEX, m_classTable);
			LogTraceReturn(true);
		}

		static bool get_class_metatable(lua_State * L)
		{
			LogTrace("bool LuaClassInfo<T>::get_class_metatable(lua_State * L)");
			if (!get_class_table(L))
			{
				LogTraceReturn(false);
			}
			lua_pushstring(L, "metatable__");
			lua_rawget(L, -2);
			lua_remove(L, -2);
			LogTraceReturn(true);
		}

		static bool set_class_table(lua_State * L, int idx)
		{
			LogTrace("LuaClassInfo<T>::set_class_table(lua_State * L, int idx)");
			if (m_classTable != LUA_REFNIL)
			{
				luaL_unref(L, LUA_REGISTRYINDEX, m_classTable);
			}
			{
				LuaStateProtect lsp(L, true);
				lua_pushvalue(L, idx);
				lua_pushstring(L, "metatable__");
				lua_rawget(L, -2);
				if (!lua_istable(L, -1))
				{
					LogScriptError("Error!!!This  class %s do not have metatable__!!!", m_className);
					LogTraceReturn(false);
				}
				lua_pushstring(L, "key__");
				lua_rawget(L, -2);
				lua_pushlightuserdata(L, &m_key);
				if (!lua_rawequal(L, -1, -2))
				{
					LogScriptError("Error!!!This  class %s do not have metatable__!!!", m_className);
					LogTraceReturn(false);
				}
			}
			lua_pushvalue(L, idx);
			m_classTable = luaL_ref(L, LUA_REGISTRYINDEX);
			LogTraceReturn(true);
		}
	private:
		static char m_key;
		static char m_className[128];
		static int m_classTable;
	};

	template<typename T>
	char LuaClassInfo<T>::m_key = 0;
	template<typename T>
	char LuaClassInfo<T>::m_className[128] = { 0 };
	template<typename T>
	int LuaClassInfo<T>::m_classTable = LUA_REFNIL;
}

#endif