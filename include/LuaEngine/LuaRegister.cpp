


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

#ifndef LIGHTINK_LUAENGINE_LUAREGISTER_CPP_
#define LIGHTINK_LUAENGINE_LUAREGISTER_CPP_

#include "LuaEngine/LuaRegister.h"
#include "LuaEngine/LuaClassInfo.h"
#include "LuaEngine/LuaDefAutoTool.h"
#include "LuaEngine/LuaDefTool.h"
#include "LuaEngine/LuaDefTraits.h"
#include "LuaEngine/LuaNewClassTraits.h"
#include "LuaEngine/LuaMetatableTraits.h"
#include "LuaEngine/LuaIndexMetatable.h"
#include "LuaEngine/LuaCFunctionTraits.h"

namespace LightInk
{

	template <typename ClassType, typename CtorType>
	LuaRegister<ClassType, CtorType>::LuaRegister(lua_State * L, const std::string & name) : m_lua(L), LuaRegisterNode(L)
	{
		LogTrace("LuaRegister<ClassType, CtorType>::LuaRegister(lua_State * L, const std::string & name)");
		LuaStateProtect lsp(L, true);
		init_class(name);
		//pop metatable, class table, parent class table
		LogTraceReturnVoid;
	}

	template <typename ClassType, typename CtorType>
	template <typename BaseType>
	LuaRegister<ClassType, CtorType>::LuaRegister(lua_State * L, const std::string & name, BaseClassStrategy<BaseType>) : m_lua(L), LuaRegisterNode(L)
	{
		LogTrace("LuaRegister<ClassType, CtorType>::LuaRegister(lua_State * L, const std::string & name, BaseClassStrategy<BaseType>)");
		LuaStateProtect lsp(L, true);
		init_class(name);
		int top = lua_gettop(L);
		if (!LuaClassInfo<BaseType>::get_class_table(L))
		{
			LogError("Error!!!Get Base Class Table Failed!!!");
		}
		rawgetfield(L, -1, "metatable__");
		lua_pushnil(L);
		while (lua_next(L, -2))
		{
			lua_pushvalue(L, -2);
			lua_rawget(L, top);
			if(lua_isnil(L, -1)) //no this field
			{
				lua_pushvalue(L, -3);
				lua_pushvalue(L, -3);
				lua_rawset(L, top);
			}
			lua_pop(L, 2);
		}

		lua_pushnil(L);
		while (lua_next(L, -3))
		{
			lua_pushvalue(L, -2);
			lua_rawget(L, top - 1);
			if (lua_isnil(L, -1))
			{
				lua_pushvalue(L, -3);
				lua_pushvalue(L, -3);
				lua_rawset(L, top - 1);
			}
			lua_pop(L, 2);
		}

		//pop metatable, class table, parent class table
		LogTraceReturnVoid;
	}

	template <typename ClassType, typename CtorType>
	LuaRegister<ClassType, CtorType>::LuaRegister(const LuaRegister<ClassType, CtorType> & cp) : LuaRegisterNode(cp), m_lua(cp.m_lua)
	{
		LogTrace("LuaRegister<ClassType, CtorType>::LuaRegister(const LuaRegister<ClassType, CtorType> & cp)");
		LogTraceReturnVoid;
	}

	template <typename ClassType, typename CtorType>
	LuaRegister<ClassType, CtorType> & LuaRegister<ClassType, CtorType>::operator = (const LuaRegister<ClassType, CtorType> & right)
	{
		LogTrace("LuaRegister<ClassType, CtorType> & LuaRegister<ClassType, CtorType>::operator = (const LuaRegister<ClassType, CtorType> & right)");
		LuaRegisterNode::operator=(right);
		m_lua = right.m_lua;
		LogTraceReturn(*this);
	}

	template <typename ClassType, typename CtorType>
	template <typename T>
	LuaRegister<ClassType, CtorType> & LuaRegister<ClassType, CtorType>::def(T obj, const std::string & name)
	{
		LogTrace("LuaRegister<ClassType, CtorType> & LuaRegister<ClassType, CtorType>::def(T obj, const std::string & name)");
		LuaDefTraits<T>::call(this, m_lua, obj, name);
		LogTraceReturn(*this);
	}

	template <typename ClassType, typename CtorType>
	LuaModuleByClass<ClassType, CtorType> LuaRegister<ClassType, CtorType>::def_module(const std::string & name)
	{
		LogTrace("LuaModuleByClass<ClassType, CtorType> LuaRegister<ClassType, CtorType>::def_module(const std::string & name)");
		if (get_class_table() != RE_Success)
		{
			LogError("Error!!!Get Class Table Failed!!!");
		}
		LuaRef lr = LuaRef::new_table(m_lua);
		lr.push();
		rawsetfieldlen(m_lua, -2, name.c_str(), name.size());
		LogTraceReturn((LuaModuleByClass<ClassType, CtorType>(m_lua, name, lr, *this)));
	}

	template <typename ClassType, typename CtorType>
	LuaRegister<ClassType, CtorType> & LuaRegister<ClassType, CtorType>::disable_new()
	{
		LogTrace("LuaRegister<ClassType, CtorType> & LuaRegister<ClassType, CtorType>::disable_new()");
		LuaStateProtect lsp(m_lua, true);
		if (get_class_table() != RE_Success)
		{
			LogError("Error!!!Get Class Table Failed!!!");
		}
		lua_pushnil(m_lua);
		rawsetfield(m_lua, -2, "new__");
		lua_getmetatable(m_lua, -1);
		lua_pushnil(m_lua);
		rawsetfield(m_lua, -2, "__call");
		LogTraceReturn(*this);
	}

	template <typename ClassType, typename CtorType>
	LuaRegister<ClassType, CtorType> & LuaRegister<ClassType, CtorType>::def_cclosure(lua_CFunction obj, const std::string & name)
	{
		LogTrace("LuaRegister<ClassType, CtorType> & LuaRegister<ClassType, CtorType>::def_cclosure(lua_CFunction obj, const std::string & name)");
		LuaStateProtect lsp(m_lua, true);
		if (get_class_table() != RE_Success)
		{
			LogError("Error!!!Get Class Table Failed!!!");
		}
		LuaDefAutoTool::def(m_lua, obj, name);
		LogTraceReturn(*this);
	}

	template <typename ClassType, typename CtorType>
	template <typename T>
	LuaRegister<ClassType, CtorType> & LuaRegister<ClassType, CtorType>::def_class_func(T obj, const std::string & name)
	{
		LogTrace("LuaRegister<ClassType, CtorType> & LuaRegister<ClassType, CtorType>::def_class_func(T obj, const std::string & name)");
		LuaStateProtect lsp(m_lua, true);
		if (get_class_metatable() != RE_Success)
		{
			LogError("Error!!!Get Class Metatable Failed!!!");
		}
		new (lua_newuserdata(m_lua, sizeof(LuaClassFunctionInfo<T>))) LuaClassFunctionInfo<T>(obj);
		lua_pushcclosure(m_lua, &LuaCFunctionTraits<T>::call, 1);
		rawsetfieldlen(m_lua, -2, name.c_str(), name.size());
		LogTraceReturn(*this);
	}

	template <typename ClassType, typename CtorType>
	template <typename T>
	LuaRegister<ClassType, CtorType> & LuaRegister<ClassType, CtorType>::def_class_property(T ClassType::* obj, const std::string & name)
	{
		LogTrace("LuaRegister<ClassType, CtorType> & LuaRegister<ClassType, CtorType>::def_class_property(T ClassType::* obj, const std::string & name)");
		typedef LuaClassPropertyInfoImp<T ClassType::*> LCPI;
		LuaStateProtect lsp(m_lua, true);
		if (get_class_metatable() != RE_Success)
		{
			LogError("Error!!!Get Class Metatable Failed!!!");
		}
		LCPI  * p = (LCPI *)lua_newuserdata(m_lua, sizeof(LCPI));
		new (p) LCPI(LuaClassPropertyTraits<ClassType, T>::pt_index_function, LuaClassPropertyTraits<ClassType, T>::pt_newindex_function, NULL);
		p->m_imp = obj;
		p->m_property = p;
		rawsetfieldlen(m_lua, -2, name.c_str(), name.size());
		LogTraceReturn(*this);
	}

	template <typename ClassType, typename CtorType>
	template <typename T>
	LuaRegister<ClassType, CtorType> & LuaRegister<ClassType, CtorType>::def_func(T obj, const std::string & name)
	{
		LogTrace("LuaRegister<ClassType, CtorType> & LuaRegister<ClassType, CtorType>::def_func(T obj, const std::string & name)");
		LuaStateProtect lsp(m_lua, true);
		if (get_class_table() != RE_Success)
		{
			LogError("Error!!!Get Class Table Failed!!!");
		}
		new (lua_newuserdata(m_lua, sizeof(T))) T(obj);
		lua_pushcclosure(m_lua, &LuaCFunctionTraits<T>::call, 1);
		rawsetfieldlen(m_lua, -2, name.c_str(), name.size());
		LogTraceReturn(*this);
	}


	template <typename ClassType, typename CtorType>
	template <typename T>
	LuaRegister<ClassType, CtorType> & LuaRegister<ClassType, CtorType>::def_property(T * obj, const std::string & name)
	{
		LogTrace("LuaRegister<ClassType, CtorType> & LuaRegister<ClassType, CtorType>::def_property(T ClassType::* obj, const std::string & name)");
		LuaStateProtect lsp(m_lua, true);
		if (get_class_table() != RE_Success)
		{
			LogError("Error!!!Get Class Table Failed!!!");
		}
		if (!lua_getmetatable(m_lua, -1))
		{
			LogError("Error!!!The Class Table Have Not Metatable!!!");
		}
		new (lua_newuserdata(m_lua, sizeof(LuaClassPropertyInfo))) LuaClassPropertyInfo(LuaClassPropertyTraits<T, void>::pt_index_function, 
																						LuaClassPropertyTraits<T, void>::pt_newindex_function, obj);
		rawsetfieldlen(m_lua, -2, name.c_str(), name.size());
		LogTraceReturn(*this);
	}

	template <typename ClassType, typename CtorType>
	RuntimeError LuaRegister<ClassType, CtorType>::get_class_table()
	{
		LogTrace("RuntimeError LuaRegister<ClassType, CtorType>::get_class_table()");
		push_value();
		if (!lua_istable(m_lua, -1))
		{
			LogTraceReturn(RE_Lua_ClassNotRegister);
		}
		LogTraceReturn(RE_Success);
	}

	template <typename ClassType, typename CtorType>
	RuntimeError LuaRegister<ClassType, CtorType>::get_class_metatable()
	{
		LogTrace("RuntimeError LuaRegister<ClassType, CtorType>::get_class_metatable()");
		if (get_class_table()!= RE_Success)
		{
			LogTraceReturn(RE_Lua_ClassNotRegister);
		}
		rawgetfield(m_lua, -1, "metatable__");
		if (!lua_istable(m_lua, -1))
		{
			LogTraceReturn(RE_Lua_ClassNotRegister);
		}
		LogTraceReturn(RE_Success);
	}


	template <typename ClassType, typename CtorType>
	void LuaRegister<ClassType, CtorType>::init_class(const std::string & name)
	{
		LogTrace("void LuaRegister<ClassType, CtorType>::init_class(const std::string & name)");
		set_key(name);
		if(LuaClassInfo<ClassType>::set_class_name(name.c_str())) //have this name
		{
			LuaClassInfo<ClassType>::get_class_table(m_lua);
			rawgetfield(m_lua, -1, "metatable__");
			set_value(-2);
			//lua_rawgetp(m_lua, -1, LuaClassInfo<ClassType>::get_class_key());
		}
		else
		{
			lua_createtable(m_lua, 0, 3); //class table
			set_value(-1);
			lua_pushcclosure(m_lua, &LuaNewClassTraits<ClassType, false, CtorType>::call, 0);
			rawsetfield(m_lua, -2, "new__"); //class table
			lua_pushlstring (m_lua, name.c_str(), name.size());
			rawsetfield(m_lua, -2, "type__");

			lua_createtable(m_lua, 0, 3); //class table
			lua_pushcclosure(m_lua, &LuaNewClassTraits<ClassType, true, CtorType>::call, 0);
			rawsetfield(m_lua, -2, "__call"); //class table
			lua_pushcclosure(m_lua, &LuaIndexMetatable::ct_index_function, 0);
			rawsetfield(m_lua, -2, "__index");
			lua_pushcclosure(m_lua, &LuaIndexMetatable::ct_newindex_function, 0);
			rawsetfield(m_lua, -2, "__newindex");

			lua_setmetatable(m_lua, -2);


			lua_createtable(m_lua, 0, 8); // userdata metatable
			lua_pushvalue(m_lua, -1);
			rawsetfield(m_lua, -3, "metatable__");
			//lua_rawsetp(m_lua, -3, LuaClassInfo<ClassType>::get_class_key());

			lua_pushlstring (m_lua, name.c_str(), name.size());
			rawsetfield(m_lua, -2, "type__");

			lua_pushlightuserdata(m_lua, LuaClassInfo<ClassType>::get_class_key());
			rawsetfield(m_lua, -2, "key__");

			lua_pushcclosure(m_lua, &LuaMetatableTraits<ClassType>::mt_isdelete_function, 0);
			rawsetfield(m_lua, -2, "isdelete__");

			lua_pushcclosure(m_lua, &LuaMetatableTraits<ClassType>::mt_delete_function, 0);
			rawsetfield(m_lua, -2, "delete__");

			lua_pushcclosure(m_lua, &LuaMetatableTraits<ClassType>::mt_force_delete_function, 0);
			rawsetfield(m_lua, -2, "force_delete__");

			lua_pushcclosure(m_lua, &LuaIndexMetatable::mt_index_function, 0);
			rawsetfield(m_lua, -2, "__index");

			lua_pushcclosure(m_lua, &LuaIndexMetatable::mt_newindex_function, 0);
			rawsetfield(m_lua, -2, "__newindex");

			lua_pushcclosure(m_lua, &LuaMetatableTraits<ClassType>::mt_gc_function, 0);
			rawsetfield(m_lua, -2, "__gc");

			LuaClassInfo<ClassType>::set_class_table(m_lua, -2);
		}
		LogTraceReturnVoid;
	}


	//////////////////////////////////////////////////////////////////////////////////////
	//LuaModuleByClass
	//////////////////////////////////////////////////////////////////////////////////////
	template <typename ClassType, typename CtorType>
	LuaModuleByClass<ClassType, CtorType>::LuaModuleByClass(lua_State * L, const std::string & moduleName, const LuaRef & table, LuaRegister<ClassType, CtorType> & c) : LuaModule(L, moduleName, table), m_class(c)
	{
		LogTrace("LuaModuleByClass<ClassType, CtorType>::LuaModuleByClass(lua_State * L, const std::string & moduleName, const LuaRef & table, LuaRegister<ClassType, CtorType> & c)");
		LogTraceReturnVoid;
	}

	template <typename ClassType, typename CtorType>
	LuaModuleByClass<ClassType, CtorType>::~LuaModuleByClass()
	{
		LogTrace("LuaModuleByClass<ClassType, CtorType>::~LuaModuleByClass()");
		LogTraceReturnVoid;
	}

	template <typename ClassType, typename CtorType>
	inline LuaRegister<ClassType, CtorType> & LuaModuleByClass<ClassType, CtorType>::module_end()
	{
		LogTrace("LuaRegister<ClassType, CtorType> & LuaModuleByClass<ClassType, CtorType>::module_end()");
		LogTraceReturn(m_class);
	}

	template <typename ClassType, typename CtorType>
	template <typename T>
	LuaModuleByClass<ClassType, CtorType> & LuaModuleByClass<ClassType, CtorType>::def(T obj, const std::string & name)
	{
		LogTrace("LuaModuleByClass<ClassType, CtorType> & LuaModuleByClass<ClassType, CtorType>::def(T obj, const std::string & name)");
		push_value();
		LuaDefAutoTool::def(m_lua, obj, name);
		lua_pop(m_lua, 1);
		LogTraceReturn(*this);
	}

	template <typename ClassType, typename CtorType>
	template <typename T>
	inline LuaRegister<ClassType, CtorType> & LuaModuleByClass<ClassType, CtorType>::operator[](const T & idx)
	{
		LogTrace("LuaRegister<ClassType, CtorType> & LuaModuleByClass<ClassType, CtorType>::operator[](T & idx)");
		LuaModule::operator[](idx);
		LogTraceReturn(m_class);
	}

}

#endif