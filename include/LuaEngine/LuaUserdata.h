


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
#ifndef LIGHTINK_LUAENGINE_LUAUSERDATA_H_
#define LIGHTINK_LUAENGINE_LUAUSERDATA_H_

#include "Common/Type.h"
#include "Common/Log.h"
#include "LuaEngine/lua/lua.hpp"
#include "LuaEngine/LuaClassInfo.h"
#include "LuaEngine/LuaMetatableTraits.h"

namespace LightInk
{
	struct LuaUserdata
	{
		template <typename T>
		static void push(lua_State * L, const T & t)
		{
			LogTrace("void LuaUserdata<T>::push(lua_State * L, const T & t)");
			if (!LuaClassInfo<T>::get_class_metatable(L))
			{
				LogScriptErrorJump(L, "Error!!!LuaUserdata<T>::push Can not get class metatable!!!!");
			}
			void * userdataPtr = lua_newuserdata(L, sizeof(LuaUserdataForClass<T>));
			lua_insert(L, -2);
			lua_setmetatable(L, -2);
			new(userdataPtr) LuaUserdataForClass<T>(new T(t), true);
			LogTraceReturnVoid;
		}
		
		template <typename T>
		static T get(lua_State * L, int idx)
		{
			LogTrace("T LuaUserdata<T>::get(lua_State * L, int idx)");
			T * p = LuaMetatableTraits<T>::userdata_to_object(L, idx);
			if (!p)
			{
				LogScriptErrorJump(L, "Error!!!LuaUserdata<T>::get get pointer is null!!!!");
			}
			LogTraceReturn(*p);
		}
	};

	struct LuaUserdataPtr
	{
		template <typename T>
		static void push(lua_State * L, const T * t)
		{
			LogTrace("void LuaUserdataPtr<T>::push(lua_State * L, const T & t)");
			if (!LuaClassInfo<T>::get_class_metatable(L))
			{
				LogScriptErrorJump(L, "Error!!!LuaUserdataPtr<T>::push Can not get class metatable!!!!");
			}
			if (t)
			{
				void * userdataPtr = lua_newuserdata(L, sizeof(LuaUserdataForClass<T>));
				lua_insert(L, -2);
				lua_setmetatable(L, -2);
				new(userdataPtr) LuaUserdataForClass<T>(t, false);
			}
			else
			{
				lua_pop(L, 1);
				lua_pushnil(L);
			}
			LogTraceReturnVoid;
		}
		
		template <typename T>
		static T * get(lua_State * L, int idx)
		{
			LogTrace("T LuaUserdataPtr<T>::get(lua_State * L, int idx)");
			LogTraceReturn(LuaMetatableTraits<T>::userdata_to_object(L, idx));
		}
	};

}

#endif