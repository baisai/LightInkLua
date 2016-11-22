


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
	LuaRegisterNode::LuaRegisterNode(lua_State * L) : m_key(L), m_value(L), m_parent(L), m_next(NULL)
	{
		LogTrace("LuaRegisterNode::LuaRegisterNode(lua_State * L)");
		LogTraceReturnVoid;
	}
	LuaRegisterNode::LuaRegisterNode(const LuaRef & key, const LuaRef & value, const LuaRef & parent) : m_key(key), m_value(value), m_parent(parent), m_next(NULL)
	{
		LogTrace("LuaRegisterNode::LuaRegisterNode(const LuaRef & key, const LuaRef & value, const LuaRef & parent)");
		LogTraceReturnVoid;
	}
	LuaRegisterNode::LuaRegisterNode(const LuaRegisterNode & cp) : m_key(cp.m_key), m_value(cp.m_value), m_parent(cp.m_parent), m_next(NULL)
	{
		LogTrace("LuaRegisterNode::LuaRegisterNode(const LuaRegisterNode & cp)");
		LogTraceReturnVoid;
	}
	LuaRegisterNode::~LuaRegisterNode()
	{
		LogTrace("LuaRegisterNode::~LuaRegisterNode()");
		LogTraceReturnVoid;
	}

	lua_State * LuaRegisterNode::state() const
	{
		LogTrace("lua_State * LuaRegisterNode::state() const");
		LogTraceReturn(m_key.state());
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

	void LuaRegisterNode::set_parent(int idx)
	{
		LogTrace("void LuaRegisterNode::set_parent(int idx)");
		lua_pushvalue(m_parent.state(), idx);
		m_parent.pop();
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
	LuaModule::LuaModule(lua_State * L, const std::string & moduleName) : m_top(lua_gettop(L)), LuaRegisterNode(L)
	{
		LogTrace("LuaModule::LuaModule(lua_State * L, const std::string & moduleName)");
		set_key(moduleName);
		lua_pushvalue(L, LUA_GLOBALSINDEX);
		set_parent(-1);
		lua_pop(L, 1);

		LuaRef v = m_parent[m_key].get_ref();
		if (v.is_table())
		{
			set_value(v);
		}
		else
		{
			set_value(LuaRef::new_table(L));
		}

		LogTraceReturnVoid;
	}
	LuaModule::LuaModule(lua_State * L, const std::string & moduleName, const LuaRef & parent) : m_top(lua_gettop(L)), LuaRegisterNode(LuaRef(L, moduleName), LuaRef(L), parent)
	{
		LogTrace("LuaModule::LuaModule(lua_State * L, const string & moduleName, const LuaRef & parent)");
		if (!parent.is_table())
		{
			lua_pushvalue(L, LUA_GLOBALSINDEX);
			set_parent(-1);
			lua_pop(L, 1);
		}
		LuaRef v = m_parent[m_key].get_ref();
		if (v.is_table())
		{
			set_value(v);
		}
		else
		{
			set_value(LuaRef::new_table(L));
		}
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
		if (m_parent.is_table())
		{
			m_parent[m_key] = m_value;
		}
		LogTraceReturn(*this);
	}

	void LuaModule::release_module()
	{
		LogTrace("void LuaModule::release_module()");
		lua_settop(m_key.state(), m_top);
		LogTraceReturnVoid;
	}

	void LuaModule::register_field(const LuaRegisterNode & head)
	{
		LogTrace("void LuaModule::register_field(LuaRegisterNode * head)");
		lua_State * lua = m_key.state();
		LuaStateProtect lsp(lua, true);
		const LuaRegisterNode * p = &head;
		push_value();
		while (p)
		{
			p->push();
			lua_rawset(lua, -3);
			p = p->next();
		}
		LogTraceReturnVoid;
	}
}