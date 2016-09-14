


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

#include "LuaEngine/LuaIterator.h"

namespace LightInk
{
	//////////////////////////////////////////////////////////
	//LuaIterator
	/////////////////////////////////////////////////////////
	LuaIterator::LuaIterator(lua_State * L, int idx) : m_L(L), m_top(lua_gettop(L)), m_over(false), m_keyIdx(0), m_copyCount(0)
	{
		LogTrace("LuaIterator::LuaIterator(lua_State * L, int idx)");
		lua_pushvalue(L, idx);
		lua_pushnil(L);
		lua_pushnil(L);
		next();
		m_keyIdx = lua_absindex(m_L, -2);
		LogTraceReturnVoid;
	}

	void LuaIterator::set_over()
	{
		LogTrace("LuaIterator::set_over()");
		if (!m_over)
		{
			m_over = true;
			m_keyIdx = 0;
			m_copyCount = 0;
			lua_settop(m_L, m_top);
		}
		LogTraceReturnVoid;
	}
	lua_State * LuaIterator::state()
	{
		LogTrace("lua_State * LuaIterator::state()");
		LogTraceReturn(m_L);
	}
	bool LuaIterator::is_over()
	{
		LogTrace("bool LuaIterator::is_over()");
		LogTraceReturn(m_over);
	}
		

	LuaIterator & LuaIterator::operator ++ ()
	{
		LogTrace("LuaIterator & LuaIterator::operator ++ ()");
		if (!m_over)
		{
			next();
		}
		LogTraceReturn(*this);
	}

	LuaIterator & LuaIterator::operator ++ (int)
	{
		LogTrace("LuaIterator & LuaIterator::operator ++ (int)");
		if (!m_over)
		{
			next();
		}
		LogTraceReturn(*this);
	}

	void LuaIterator::next()
	{
		LogTrace("void LuaIterator::next()");
		lua_pop(m_L, 1);
		if (!lua_next(m_L, -2))
		{
			set_over();
		}
		LogTraceReturnVoid;
	}


	//////////////////////////////////////////////////////////
	//LuaRefIterator
	/////////////////////////////////////////////////////////
	LuaRefIterator::LuaRefIterator(const LuaRef & table) : m_L(table.state()), m_table(table), m_key(table.state()), m_value(table.state())
	{
		LogTrace("LuaRefIterator::LuaRefIterator(const LuaRef & table)");
		LogTraceReturnVoid;
	}

	lua_State * LuaRefIterator::state()
	{
		LogTrace("lua_State * LuaRefIterator::state()");
		LogTraceReturn(m_L);
	}

	bool LuaRefIterator::is_over()
	{
		LogTrace("bool LuaRefIterator::is_over()");
		LogTraceReturn(m_key.is_nil());
	}

	LuaRef & LuaRefIterator::get_key()
	{
		LogTrace("LuaRef & LuaRefIterator::get_key()");
		LogTraceReturn(m_key);
	}

	LuaRef & LuaRefIterator::get_value()
	{
		LogTrace("LuaRef & LuaRefIterator::get_value()");
		LogTraceReturn(m_value);
	}

	LuaRef & LuaRefIterator::operator * ()
	{
		LogTrace("LuaRef & LuaRefIterator::operator * ()");
		LogTraceReturn(m_value);
	}

	LuaRef & LuaRefIterator::operator -> ()
	{
		LogTrace("LuaRef & LuaRefIterator::operator -> ()");
		LogTraceReturn(m_value);
	}

	LuaRefIterator & LuaRefIterator::operator ++ ()
	{
		LogTrace("LuaRefIterator & LuaRefIterator::operator ++ ()");
		if (!m_key.is_nil())
		{
			next();
		}
		LogTraceReturn(*this);
	}

	LuaRefIterator & LuaRefIterator::operator ++ (int)
	{
		LogTrace("LuaRefIterator & LuaRefIterator::operator ++ (int)");
		if (!m_key.is_nil())
		{
			next();
		}
		LogTraceReturn(*this);
	}

	void LuaRefIterator::next()
	{
		LogTrace("void LuaRefIterator::next()");
		m_table.push();
		m_key.push ();
		if (lua_next (m_L, -2))
		{
			m_value.pop ();
			m_key.pop ();
		}
		else
		{
			m_key.set_nil();
			m_value.set_nil();
		}
		lua_pop(m_L, 1);
		LogTraceReturnVoid;
	}

}