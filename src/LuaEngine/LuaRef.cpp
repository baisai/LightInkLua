


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



#include "LuaEngine/LuaRef.h"
#include "LuaEngine/LuaTableRef.h"

namespace LightInk
{
	LuaRef::LuaRef(lua_State * L) : m_L(L), m_ref(LUA_REFNIL)
	{ 
		LogTrace("LuaRef::LuaRef(lua_State * L)"); 
		LogTraceReturnVoid; 
	}

	LuaRef::LuaRef(lua_State * L, bool fromStack) : m_L(L), m_ref(luaL_ref(L, LUA_REGISTRYINDEX))
	{ 
		LogTrace("LuaRef::LuaRef(lua_State * L, bool fromStack)"); 
		LogTraceReturnVoid; 
	}

	LuaRef::LuaRef(lua_State * L, int idx) : m_L(L), m_ref(LUA_REFNIL)
	{
		LogTrace("LuaRef::LuaRef(lua_State * L, int idx)");
		lua_pushvalue(L, idx);
		m_ref = luaL_ref(L, LUA_REGISTRYINDEX);
		LogTraceReturnVoid;
	}

	LuaRef::LuaRef(const LuaTableRef & v) : m_L(v.state()), m_ref(v.create_ref())
	{ 
		LogTrace("LuaRef::LuaRef(const LuaTableRef & v)");
		LogTraceReturnVoid;
	}

	LuaRef::LuaRef(const LuaRef & cp) : m_L(cp.m_L), m_ref(cp.create_ref())
	{
		LogTrace("LuaRef::LuaRef(const LuaRef & cp)"); 
		LogTraceReturnVoid;
	}

	LuaRef::~LuaRef()
	{
		LogTrace("LuaRef::~LuaRef()");
		if (m_L) { luaL_unref(m_L, LUA_REGISTRYINDEX, m_ref); }
		LogTraceReturnVoid;
	}

	void LuaRef::clear_lua()
	{
		LogTrace("void LuaRef::LuaTableRef::clear_lua()");
		m_L = NULL;
		m_ref = LUA_REFNIL;
		LogTraceReturnVoid;
	}

	int LuaRef::create_ref() const
	{
		LogTrace("int LuaRef::create_ref() const");
		if (m_ref == LUA_REFNIL)
		{
			LogTraceReturn(m_ref);
		}
		push();
		LogTraceReturn(luaL_ref(m_L, LUA_REGISTRYINDEX));
	}

	void LuaRef::set_nil()
	{
		LogTrace("LuaRef::set_nil()");
		if (m_ref != LUA_REFNIL)
		{
			luaL_unref(m_L, LUA_REGISTRYINDEX, m_ref);
			m_ref = LUA_REFNIL;
		}
		LogTraceReturnVoid;
	}

	LuaRef & LuaRef::operator = (const LuaRef & right)
	{
		LogTrace("LuaRef & LuaRef::operator = (const LuaRef & right)");
		luaL_unref(m_L, LUA_REGISTRYINDEX, m_ref);
		right.push();
		m_L = right.state();
		m_ref = luaL_ref(m_L, LUA_REGISTRYINDEX);
		LogTraceReturn(*this);
	}

	LuaRef & LuaRef::operator = (const LuaTableRef & right)
	{
		LogTrace("LuaRef & LuaRef::operator = (const LuaTableRef & right)");
		luaL_unref(m_L, LUA_REGISTRYINDEX, m_ref);
		right.push();
		m_L = right.state();
		m_ref = luaL_ref(m_L, LUA_REGISTRYINDEX);
		LogTraceReturn(*this);
	}


	LuaRef LuaRef::new_table(lua_State * L, int narr, int nrec)
	{
		LogTrace("LuaRef LuaRef::new_table(lua_State * L, int narr, int nrec)");
		lua_createtable(L, narr, nrec);
		LogTraceReturn(LuaRef(L, true));
	}
	LuaRef LuaRef::get_global_var(lua_State * L, const char * name)
	{
		LogTrace("LuaRef LuaRef::get_global_var(lua_State * L, const char * name)");
		lua_getglobal(L, name);
		LogTraceReturn(LuaRef(L, true));
	}


	std::string LuaRef::to_string() const
	{
		LogTrace("std::string LuaRef::to_string() const");
		LuaStateProtect lsp(m_L);
		lua_getglobal(m_L, "tostring");
		push();
		if (lua_pcall(m_L, 1, 1, 0))
		{
			const char * errStr = lua_tostring(m_L, -1);
			if (errStr) LogScriptError(errStr);
			LogTraceReturn(std::string());
		}
		const char * str = lua_tostring(m_L, -1);
		lsp.reset();
		LogTraceReturn(std::string(str));
	}
	void LuaRef::print() const
	{
		LogTrace("LuaRef::print(std::ostream & os) const");
		switch (type())
		{
		case LUA_TNIL:
			LogScriptMessage("nil");break;
		case LUA_TNUMBER:
			LogScriptMessage(to_string().c_str());break;
		case LUA_TBOOLEAN:
			LogScriptMessage(cast<bool>() ? "true" : "false");break;
		case LUA_TSTRING:
			LogScriptMessage("\"%s\"", cast<std::string>().c_str());break;
		case LUA_TTABLE:
			LogScriptMessage("table : %s", to_string().c_str());break;
		case LUA_TFUNCTION:
			LogScriptMessage("function : %s", to_string().c_str());break;
		case LUA_TUSERDATA:
			LogScriptMessage("userdata : %s", to_string().c_str());break;
		case LUA_TTHREAD:
			LogScriptMessage("thread : %s", to_string().c_str());break;
		case LUA_TLIGHTUSERDATA:
			LogScriptMessage("lightuserdata : %s", to_string().c_str());break;
		default:
			LogScriptMessage("unknown");break;
		}
		LogTraceReturnVoid;
	}
	lua_State * LuaRef::state() const
	{ LogTrace("lua_State * LuaRef::state()"); LogTraceReturn(m_L); }
	void LuaRef::push() const
	{
		LogTrace("LuaRef::push() const");
		lua_rawgeti(m_L, LUA_REGISTRYINDEX, m_ref);
		LogTraceReturnVoid;
	}
	void LuaRef::pop()
	{
		LogTrace("LuaRef::pop() const");
		luaL_unref(m_L, LUA_REGISTRYINDEX, m_ref);
		m_ref = luaL_ref(m_L, LUA_REGISTRYINDEX);
		LogTraceReturnVoid;
	}
	int LuaRef::type() const
	{
		LogTrace("int LuaRef::type() const");
		if (m_ref == LUA_REFNIL)
		{
			LogTraceReturn(LUA_TNIL);
		}
		LuaStateProtect lsp(m_L, true);
		push();
		LogTraceReturn(lua_type(m_L, -1));
	}

	bool LuaRef::is_nil() const
	{
		LogTrace("bool LuaRef::is_nil() const"); 
		LogTraceReturn((type() == LUA_TNIL));
	}
	bool LuaRef::is_number() const
	{
		LogTrace("bool LuaRef::is_number() const");
		LogTraceReturn((type() == LUA_TNUMBER));
	}
	bool LuaRef::is_string() const
	{
		LogTrace("bool LuaRef::is_string() const"); 
		LogTraceReturn((type() == LUA_TSTRING));
	}
	bool LuaRef::is_table() const
	{
		LogTrace("bool LuaRef::is_table() const"); 
		LogTraceReturn((type() == LUA_TTABLE));
	}
	bool LuaRef::is_function() const
	{
		LogTrace("bool LuaRef::is_function() const"); 
		LogTraceReturn((type() == LUA_TFUNCTION));
	}
	bool LuaRef::is_userdata() const
	{
		LogTrace("bool LuaRef::is_userdata() const"); 
		LogTraceReturn((type() == LUA_TUSERDATA));
	}
	bool LuaRef::is_thread() const
	{
		LogTrace("bool LuaRef::is_thread() const"); 
		LogTraceReturn((type() == LUA_TTHREAD));
	}
	bool LuaRef::is_lightuserdata() const
	{
		LogTrace("bool LuaRef::is_lightuserdata() const"); 
		LogTraceReturn((type() == LUA_TLIGHTUSERDATA));
	}
	bool LuaRef::is_bool() const
	{
		LogTrace("bool LuaRef::is_bool() const"); 
		LogTraceReturn((type() == LUA_TBOOLEAN));
	}

	bool LuaRef::is_cfunction() const
	{
		LogTrace("bool LuaRef::is_cfunction() const");
		if (m_ref == LUA_REFNIL)
		{
			LogTraceReturn(false);
		}
		LuaStateProtect lsp(m_L, true);
		push();
		LogTraceReturn(lua_iscfunction(m_L, -1) == 1);
	}


	size_t LuaRef::length() const
	{
		LogTrace("LuaRef::length() const");
		LuaStateProtect lsp(m_L, true);
		push();
		size_t len = lua_objlen(m_L, -1);
		lsp.reset();
		LogTraceReturn(len);
	}

		
	const LuaRef LuaRef::operator () () const
	{
		LogTrace("const LuaRef LuaRef::operator () () const");
		push();
		if (lua_pcall(m_L, 0, 1, 0))
		{
			const char * errStr = lua_tostring(m_L, -1);
			if (errStr) LogScriptError(errStr);
			LogTraceReturn(LuaRef(m_L));
		}
		LogTraceReturn(LuaRef(m_L, true));
	}

}
