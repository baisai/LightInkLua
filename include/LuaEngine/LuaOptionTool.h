
#ifndef LIGHTINK_LUAENGINE_LUAOPTIONTOOL_H_
#define LIGHTINK_LUAENGINE_LUAOPTIONTOOL_H_

#include "Common/Type.h"
#include "LuaEngine/lua/lua.hpp"
#include "Common/StlType.h"
#include "Common/Log.h"

namespace LightInk
{
	class LIGHTINK_DECL LuaStateProtect
	{
	public:
		LuaStateProtect(lua_State * L, bool autoPop = false) : m_lua(L), m_top(lua_gettop(L)), m_autoPop(autoPop) { ; }
		~LuaStateProtect() {if (m_autoPop) lua_settop(m_lua, m_top);}
		void reset() { lua_settop(m_lua, m_top); }
	private:
		lua_State * m_lua;
		int m_top;
		bool m_autoPop;
	LIGHTINK_DISABLE_COPY(LuaStateProtect)
	};

	struct LIGHTINK_DECL LuaDefTool
	{
		template <typename T>
		static void def(lua_State * L, T obj, const string & name)
		{
			LogTrace("void LuaDefTool::def<T>(lua_State * L, T obj, const string & name)");
			LuaDefTraits<T>::call(L, obj, name);
			LogTraceReturnVoid;
		}

		template <>
		static void def<lua_CFunction>(lua_State * L, lua_CFunction obj, const string & name)
		{
			LogTrace("void LuaDefTool::def<lua_CFunction>(lua_State * L, lua_CFunction obj, const string & name)");
			LuaStateProtect lsp(L);
			if (!lua_istable(L, -1))
			{
				//lua_getglobal(L, "_G");
				lua_pushvalue(L, LUA_GLOBALSINDEX);
			}
			else
			{
				lua_pushvalue(L, -1);
			}
			lua_pushlstring(L, name.c_str(), name.size());
			lua_pushcclosure(L, obj, 0);
			lua_rawset(L, -3);
			LogTraceReturnVoid;
		}

		template <typename T>
		static void def_func(lua_State * L, T obj, const string & name)
		{
			LogTrace("void LuaDefTool::def_func<T>(lua_State * L, T & obj, const string & name)");
			LuaStateProtect lsp(L);
			if (!lua_istable(L, -1))
			{
				//lua_getglobal(L, "_G");
				lua_pushvalue(L, LUA_GLOBALSINDEX);
			}
			else
			{
				lua_pushvalue(L, -1);
			}
			new (lua_newuserdata(L, sizeof(T))) T(obj);
			lua_pushcclosure(L, &LuaCFunctionTraits<T>::call, 1);
			rawsetfieldlen(L, -2, name.c_str(), name.size());
			LogTraceReturnVoid;
		}

		template <typename T>
		static void def_property(lua_State * L, T * obj, const string & name)
		{
			LogTrace("void LuaDefTool::def_property<T>(lua_State * L, T * obj, const string & name)");
			LuaStateProtect lsp(L);
			if (!lua_istable(L, -1))
			{
				//lua_getglobal(L, "_G");
				lua_pushvalue(L, LUA_GLOBALSINDEX);
			}
			else
			{
				lua_pushvalue(L, -1);
			}
			new (lua_newuserdata(L, sizeof(LuaClassPropertyInfo))) LuaClassPropertyInfo(LuaClassPropertyTraits<T, void>::pt_index_function, 
																						LuaClassPropertyTraits<T, void>::pt_newindex_function, obj);
			rawsetfieldlen(L, -2, name.c_str(), name.size());
			LogTraceReturnVoid;
		}
	};



#if LUA_VERSION_NUM < 502
	inline static int lua_absindex (lua_State* L, int idx)
	{
		if (idx > LUA_REGISTRYINDEX && idx < 0)
		return lua_gettop (L) + idx + 1;
		else
		return idx;
	}

	inline static void lua_rawgetp (lua_State* L, int idx, void const* p)
	{
		idx = lua_absindex (L, idx);
		lua_pushlightuserdata (L, const_cast <void*> (p));
		lua_rawget (L,idx);
	}

	inline static void lua_rawsetp (lua_State* L, int idx, void const* p)
	{
		idx = lua_absindex (L, idx);
		lua_pushlightuserdata (L, const_cast <void*> (p));
		// put key behind value
		lua_insert (L, -2);
		lua_rawset (L, idx);
	}


#else
	inline static int lua_objlen (lua_State* L, int idx)
	{
		return lua_rawlen(L, idx);
	}

#endif


	
	//Get a table value, bypassing metamethods.
	inline void rawgetfield (lua_State* L, int index, const char * key)
	{
	  index = lua_absindex (L, index);
	  lua_pushstring (L, key);
	  lua_rawget (L, index);
	}

	//Set a table value, bypassing metamethods.
	inline void rawsetfield (lua_State* L, int index, const char * key)
	{
	  index = lua_absindex (L, index);
	  lua_pushstring (L, key);
	  lua_insert (L, -2);
	  lua_rawset (L, index);
	}

	//Get a table value, bypassing metamethods.
	inline void rawgetfieldlen (lua_State* L, int index, const char * key, size_t l)
	{
	  index = lua_absindex (L, index);
	  lua_pushlstring (L, key, l);
	  lua_rawget (L, index);
	}

	//Set a table value, bypassing metamethods.
	inline void rawsetfieldlen (lua_State* L, int index, const char * key, size_t l)
	{
	  index = lua_absindex (L, index);
	  lua_pushlstring (L, key, l);
	  lua_insert (L, -2);
	  lua_rawset (L, index);
	}

	//Returns true if the value is a full userdata (not light).
	inline bool isfulluserdata (lua_State* L, int index)
	{
	  return lua_isuserdata (L, index) && !lua_islightuserdata (L, index);
	}

	inline void lock_metatable(lua_State * L, int index)
	{
		index = lua_absindex(L, index);
		lua_pushstring(L, "__metatable");
		lua_pushstring(L, "error!!!metatable is locked!!!");
		lua_rawset(L, index);
	}
	/*
	inline int pcall_callback(lua_State * L)
	{
		LogTrace("int pcall_callback(lua_State * L)");
		lua_Debug debug= {};  
		int ret = lua_getstack(L, 2, &debug); // 0是pcall_callback_err_fun自己, 1是error函数, 2是真正出错的函数  
		lua_getinfo(L, "Sln", &debug);  
  
		string err = lua_tostring(L, -1);  
		lua_pop(L, 1);  
		std::stringstream msg;  
		msg << debug.short_src << ":line " << debug.currentline;  
		if (debug.name != 0) {  
		msg << "(" << debug.namewhat << " " << debug.name << ")";  
		}  
  
		msg << " [" << err << "]";  
		lua_pushstring(L, msg.str().c_str());  
		LogTraceReturn(1);
	}*/
	
}

#endif