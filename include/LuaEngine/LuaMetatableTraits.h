


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
#ifndef LIGHTINK_LUAENGINE_LUAMETATABLETRAITS_H_
#define LIGHTINK_LUAENGINE_LUAMETATABLETRAITS_H_

#include "Common/Type.h"
#include "Common/Log.h"
#include "LuaEngine/LuaClassInfo.h"
#include "LuaEngine/LuaUserdataForClass.h"
#include "LuaEngine/LuaFixFunction.h"

namespace LightInk
{
	////////////////////////////////////////////////////////////////////////////////////////////////////////
	//LuaMetatableTraits
	////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 生成一些元方法的实现类
	template<typename ClassType>
	struct LuaMetatableTraits
	{
		static LuaUserdataForClass<ClassType> * userdata_to_imp(lua_State * L, int idx)
		{
			LogTrace("LuaUserdataForClass<ClassType> * LuaMetatableTraits<ClassType>::userdata_to_imp(lua_State * L, int idx)");
			if (!LuaClassInfo<ClassType>::is_registered(L))
			{
				LogScriptErrorJump(L, "Error!!!The Class has not registered to lua!!!!");
				LogTraceReturn(NULL);
			}
			LuaStateProtect lsp(L);
			if (lua_isnothing(L, idx))
			{
				LogTraceReturn(NULL);
			}
			else if (!lua_isuserdata(L, idx))
			{
				LogScriptErrorJump(L, "Error!!!The arg %d is not userdata!!!", idx);
				LogTraceReturn(NULL);
			}
			void * userdata = lua_touserdata(L, idx);

			if (userdata == NULL)
			{
				LogScriptErrorJump(L, "Error!!!The arg %d is userdata, but pointer is null!!!", idx);
				LogTraceReturn(NULL);
			}
			if (!lua_getmetatable(L, idx))
			{
				LogScriptErrorJump(L, "Error!!!The arg %d is userdata, but not metatable!!!", idx);
				LogTraceReturn(NULL);
			}
			
			lua_pushstring(L, "key__");
			lua_rawget(L, -2);
			if (!lua_islightuserdata(L, -1))
			{
				LogScriptErrorJump(L, "Error!!!The arg %d is userdata, but metatable is error!!!", idx);
				LogTraceReturn(NULL);
			}
			/*因为可能是继承关系
			lua_pushlightuserdata(L, LuaClassInfo<ClassType>::get_class_key());
			if (!lua_rawequal(L, -1, -2))
			{
				lsp.give_up();
				LogScriptErrorJump(L, "Error!!!The arg %d is userdata, but CPP Type is error!!!", idx);
				LogTraceReturn(NULL);
			}*/
			LuaUserdataForClass<ClassType> * p = (LuaUserdataForClass<ClassType>*) userdata;
			lsp.reset();
			LogTraceReturn(p);
		}

		static ClassType * userdata_to_object(lua_State* L, int idx)
		{
			LogTrace("ClassType * LuaMetatableTraits<ClassType>::userdata_to_object(lua_State * L, int idx)");
			LuaUserdataForClass<ClassType> * p = userdata_to_imp(L, idx);
			if (p)
			{
				LogTraceReturn(p->m_obj);
			}
			LogTraceReturn(NULL);
		}
		static int mt_isdelete_function(lua_State * L)
		{
			LogTrace("int LuaMetatableTraits<ClassType>::mt_isdelete_function(lua_State * L)");
			LuaUserdataForClass<ClassType> * p = userdata_to_imp(L, 1);
			if (p && p->m_obj)
			{
				lua_pushboolean(L, 0);
			}
			else
			{
				lua_pushboolean(L, 1);
			}
			LogTraceReturn(1);
		}

		static int mt_delete_function(lua_State * L)
		{
			LogTrace("int LuaMetatableTraits<ClassType>::mt_delete_function(lua_State * L)");
			LuaUserdataForClass<ClassType> * p = userdata_to_imp(L, 1);
			if (p && p->m_obj && !p->m_luaGC)
			{
				delete p->m_obj;
				p->m_obj = NULL;
			}
			LogTraceReturn(0);
		}

		static int mt_force_delete_function(lua_State * L)
		{
			LogTrace("int LuaMetatableTraits<ClassType>::mt_force_delete_function(lua_State * L)");
			LuaUserdataForClass<ClassType> * p = userdata_to_imp(L, 1);
			if (p && p->m_obj)
			{
				delete p->m_obj;
				p->m_obj = NULL;
			}
			LogTraceReturn(0);
		}

		static int mt_gc_function(lua_State * L)
		{
			LogTrace("int LuaMetatableTraits<ClassType>::mt_gc_function(lua_State * L)");
			LuaUserdataForClass<ClassType> * p = userdata_to_imp(L, 1);
			if (p)
			{
				p->~LuaUserdataForClass();
			}
			LogTraceReturn(0);
		}
	};
}


#endif