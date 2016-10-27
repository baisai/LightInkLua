


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
#include "LuaEngine/LuaModule.h"
#include "LuaEngine/LuaDefTool.h"

namespace LightInk
{
	////////////////////////////////////////////////////////////////////////
	//LuaRegisterNode
	///////////////////////////////////////////////////////////////////////
	LuaRegisterNode::LuaRegisterNode(lua_State * L) : m_key(L), m_value(L), m_next(NULL)
	{
		LogTrace("LuaRegisterNode::LuaRegisterNode(lua_State * L)");
		LogTraceReturnVoid;
	}
	LuaRegisterNode::LuaRegisterNode(const LuaRef & key, const LuaRef & value) : m_key(key), m_value(value), m_next(NULL)
	{
		LogTrace("LuaRegisterNode::LuaRegisterNode(const LuaRef & key, const LuaRef & value)");
		LogTraceReturnVoid;
	}
	LuaRegisterNode::LuaRegisterNode(const LuaRegisterNode & cp) : m_key(cp.m_key), m_value(cp.m_value), m_next(NULL)
	{
		LogTrace("LuaRegisterNode::LuaRegisterNode(const LuaRegisterNode & cp)");
		LogTraceReturnVoid;
	}
	LuaRegisterNode::~LuaRegisterNode()
	{
		LogTrace("LuaRegisterNode::~LuaRegisterNode()");
		LogTraceReturnVoid;
	}

	void LuaRegisterNode::set_key(int idx)
	{
		LogTrace("void LuaRegisterNode::set_key(int idx)");
		lua_pushvalue(m_key.state(), idx);
		m_key.pop();
		LogTraceReturnVoid;
	}

	void LuaRegisterNode::set_value(int idx)
	{
		LogTrace("void LuaRegisterNode::set_value(int idx)");
		lua_pushvalue(m_value.state(), idx);
		m_value.pop();
		LogTraceReturnVoid;
	}

	void LuaRegisterNode::push() const
	{
		LogTrace("void LuaRegisterNode::push() const");
		m_key.push();
		m_value.push();
		LogTraceReturnVoid;
	}

	void LuaRegisterNode::push_key() const
	{
		LogTrace("void LuaRegisterNode::push_key() const");
		m_key.push();
		LogTraceReturnVoid;
	}

	void LuaRegisterNode::push_value() const
	{
		LogTrace("void LuaRegisterNode::push_value() const");
		m_value.push();
		LogTraceReturnVoid;
	}

	LuaRegisterNode & LuaRegisterNode::def_end(int idx)
	{
		LogTrace("LuaRegisterNode & LuaRegisterNode::def_end(int idx");
		lua_State * L = m_key.state();
		if (!lua_istable(L, idx))
		{
			LogError("Error!!!LuaRegisterNode::def_end call the Lua Stack %d is not a table!!!", idx);
			LogTraceReturn(*this);
		}
		LuaStateProtect lsp(L, true);
		lua_pushvalue(L, idx);
		push();
		lua_rawset(L, -3);
		LogTraceReturn(*this);
	}

	LuaRegisterNode & LuaRegisterNode::def_end()
	{
		LogTrace("LuaRegisterNode & LuaRegisterNode::def_end()");
		lua_State * L = m_key.state();
		LuaStateProtect lsp(L, true);
		//lua_getglobal(L, "_G");
		lua_pushvalue(L, LUA_GLOBALSINDEX);
		push();
		lua_rawset(L, -3);
		LogTraceReturn(*this);
	}

	void LuaRegisterNode::next(LuaRegisterNode * n)
	{
		LogTrace("void LuaRegisterNode::next(LuaRegisterNode * n)");
		m_next = n;
		LogTraceReturnVoid;
	}
	const LuaRegisterNode * LuaRegisterNode::next() const
	{
		LogTrace("const LuaRegisterNode * LuaRegisterNode::next() const");
		LogTraceReturn(m_next);
	}

	LuaRegisterNode & LuaRegisterNode::operator <= (LuaRegisterNode & right)
	{
		LogTrace("LuaRegisterNode & LuaRegisterNode::operator ,(const LuaRegisterNode & right)");
		right.m_next = this;
		LogTraceReturn(right);
	}

	LuaRegisterNode & LuaRegisterNode::operator = (const LuaRegisterNode & right)
	{
		LogTrace("LuaRegisterNode & LuaRegisterNode::operator <= (const LuaRegisterNode & right)");
		m_key = right.m_key;
		m_value = right.m_value;
		m_next = NULL;
		LogTraceReturn(*this);
	}

	LuaRegisterNode & LuaRegisterNode::self()
	{
		LogTrace("LuaRegisterNode & LuaRegisterNode::self()");
		LogTraceReturn(*this);
	}



	////////////////////////////////////////////////////////////////////////
	//LuaModule
	///////////////////////////////////////////////////////////////////////
	LuaModule::LuaModule(lua_State * L, const std::string & moduleName) : m_lua(L), m_top(lua_gettop(L)), LuaRegisterNode(LuaRef(L, moduleName), LuaRef::new_table(L))
	{
		LogTrace("LuaModule::LuaModule(lua_State * L, const std::string & moduleName)");
		LogTraceReturnVoid;
	}
	LuaModule::LuaModule(lua_State * L, const std::string & moduleName, const LuaRef & table) : m_lua(L), m_top(lua_gettop(L)), LuaRegisterNode(LuaRef(L, moduleName), table)
	{
		LogTrace("LuaModule::LuaModule(lua_State * L, const string & moduleName, const LuaRef & table)");
		LogTraceReturnVoid;
	}
	LuaModule::~LuaModule()
	{
		LogTrace("LuaModule::~LuaModule()");
		release_module();
		LogTraceReturnVoid;
	}

	LuaModule & LuaModule::operator[](const LuaRegisterNode & key)
	{
		LogTrace("LuaModule & LuaModule::operator[](const LuaRegisterNode & key)");
		register_field(key);
		LogTraceReturn(*this);
	}

	void LuaModule::release_module()
	{
		LogTrace("void LuaModule::release_module()");
		if (m_lua)
		{
			lua_settop(m_lua, m_top);
			m_lua = NULL;
		}
		LogTraceReturnVoid;
	}

	void LuaModule::register_field(const LuaRegisterNode & head)
	{
		LogTrace("void LuaModule::register_field(LuaRegisterNode * head)");
		LuaStateProtect lsp(m_lua, true);
		const LuaRegisterNode * p = &head;
		push_value();
		while (p)
		{
			p->push();
			lua_rawset(m_lua, -3);
			p = p->next();
		}
		LogTraceReturnVoid;
	}
}