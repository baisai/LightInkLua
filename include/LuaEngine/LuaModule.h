


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

#ifndef LIGHTINK_LUAENGINE_LUAMODULE_H_
#define LIGHTINK_LUAENGINE_LUAMODULE_H_

#include "Common/Type.h"
#include "LuaEngine/lua/lua.hpp"
#include "Common/Log.h"
#include "LuaEngine/LuaRef.h"
/***************************************************
LightInk::LuaModule(L, "llll")
	[
		LightInk::LuaRegister<LuaClass, void()>(L, "lightinkLuaClass", LightInk::BaseClassStrategy<LuaBase>())
			.def(&LuaClass::test, "test")
			<=
		LightInk::LuaRegister<LuaBase, void()>(L, "lightinkLuaBase")
			.def(&LuaBase::n, "n")
			<=
		LightInk::LuaRegister<lightTest, void()>(L, "lightinktest")
			.def(&lightTest::m_dou, "dou")
			
	].def_end();
���Class�м̳й�ϵ,��ô�����÷�����������,���������ܻ��Ż�������Ĺ���˳��:
�Ƚ����е�LuaRegister�������,Ȼ���ٵ��ø��Ե�def,������<=,������ʹ����ķ����ͱ���,�޷��������̳�;
���ʱ�����ʹ���������ַ���:
LightInk::LuaRegister<lightTest, void()> a(L, "lightinktest");
	a.def(&lightTest::m_dou, "dou");
LightInk::LuaRegister<LuaBase, void()> b(L, "lightinkLuaBase");
	b.def(&LuaBase::n, "n");
LightInk::LuaRegister<LuaClass, void()> c(L, "lightinkLuaClass", LightInk::BaseClassStrategy<LuaBase>());
	c.def(&LuaClass::test, "test");
LightInk::LuaModule(L, "llll")
	[
		c <= b <= b
	].def_end();
****************************************************/

namespace LightInk
{

	class LIGHTINK_DECL LuaRegisterNode
	{
	public:
		LuaRegisterNode(lua_State * L);
		LuaRegisterNode(const LuaRef & key, const LuaRef & value);
		LuaRegisterNode(const LuaRegisterNode & cp);
		~LuaRegisterNode();

		template <typename T>
		inline void set_key(const T & t)
		{
			LogTrace("LuaRegisterNode::set_key<T>(const T & t)");
			m_key = t;
			LogTraceReturnVoid;
		}

		void set_key(int idx);

		template <typename T>
		inline void set_value(const T & t)
		{
			LogTrace("LuaRegisterNode::set_value<T>(const T & t)");
			m_value = t;
			LogTraceReturnVoid;
		}

		void set_value(int idx);
		void push() const;
		void push_key() const;
		void push_value() const;

		LuaRegisterNode & def_end(int idx);
		LuaRegisterNode & def_end();

		void next(LuaRegisterNode * n);
		const LuaRegisterNode * next() const;

		LuaRegisterNode & operator <= (LuaRegisterNode & right);
		LuaRegisterNode & operator = (const LuaRegisterNode & right);

		LuaRegisterNode & self();

	protected:
		LuaRef m_key;
		LuaRef m_value;
		LuaRegisterNode * m_next;
	};

	class LIGHTINK_DECL LuaModule : public LuaRegisterNode
	{
	public:
		LuaModule(lua_State * L, const std::string & moduleName);
		LuaModule(lua_State * L, const std::string & moduleName, const LuaRef & table);
		virtual ~LuaModule();

		LuaModule & operator[](const LuaRegisterNode & key);

	protected:
		void release_module();
		void register_field(const LuaRegisterNode & head);
	protected:
		lua_State * m_lua;
		int m_top;
	LIGHTINK_DISABLE_COPY(LuaModule)
	};

}

#endif