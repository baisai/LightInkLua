


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

#ifndef LIGHTINK_LUAENGINE_LUAREF_H_
#define LIGHTINK_LUAENGINE_LUAREF_H_

#include "Common/Type.h"
#include "LuaEngine/LuaStateProtect.h"
#include "LuaEngine/LuaStack.h"


namespace LightInk
{
	class LIGHTINK_DECL LuaRef : public SmallObject
	{
	private:
		class LuaTableRef : public SmallObject
		{
		public:
			LuaTableRef(lua_State * L, int tableRef) : m_L(L), m_tableRef(tableRef), m_keyRef(luaL_ref(L, LUA_REGISTRYINDEX))
			{ LogTrace("LuaRef::LuaTableRef::LuaTableRef(lua_State * L, int tableRef)"); LogTraceReturnVoid; }
			LuaTableRef(const LuaTableRef & cp) : m_L(cp.m_L), m_tableRef(cp.m_tableRef)
			{
				LogTrace("LuaRef::LuaTableRef::LuaTableRef(const LuaTableRef & cp)");
				lua_rawgeti(m_L, LUA_REGISTRYINDEX, cp.m_keyRef);
				m_keyRef = luaL_ref(m_L, LUA_REGISTRYINDEX);
				LogTraceReturnVoid;
			}
			~LuaTableRef()
			{
				LogTrace("LuaRef::LuaTableRef::~LuaTableRef()");
				luaL_unref(m_L, LUA_REGISTRYINDEX, m_keyRef);
				LogTraceReturnVoid;
			}

			inline int create_ref() const
			{
				LogTrace("int LuaRef::LuaTableRef::create_ref() const");
				if (m_tableRef == LUA_REFNIL || m_keyRef == LUA_REFNIL)
				{
					LogTraceReturn(LUA_REFNIL);
				}
				push();
				LogTraceReturn(luaL_ref(m_L, LUA_REGISTRYINDEX));
			}

			template <typename T>
			LuaTableRef & operator = (const T & v)
			{
				LogTrace("LuaTableRef & LuaRef::LuaTableRef::operator =<T> (const T & v)");
				LuaStateProtect lsp(m_L);
				lua_rawgeti(m_L, LUA_REGISTRYINDEX, m_tableRef);
				lua_rawgeti(m_L, LUA_REGISTRYINDEX, m_keyRef);
				LuaStack<const T>::push(m_L, v);
				lua_settable(m_L, -3);
				lsp.reset();
				LogTraceReturn(*this);
			}

			template <typename T>
			LuaTableRef & rawset (const T & v)
			{
				LogTrace("LuaTableRef & LuaRef::LuaTableRef::rawset<T> (const T & v)");
				LuaStateProtect lsp(m_L);
				lua_rawgeti(m_L, LUA_REGISTRYINDEX, m_tableRef);
				lua_rawgeti(m_L, LUA_REGISTRYINDEX, m_keyRef);
				LuaStack<const T>::push(m_L, v);
				lua_rawset(m_L, -3);
				lsp.reset();
				LogTraceReturn(*this);
			}

			inline lua_State * state() const
			{ LogTrace("lua_State * LuaRef::LuaTableRef::state()"); LogTraceReturn(m_L); }

			void push() const
			{
				LogTrace("LuaRef::LuaTableRef::push() const");
				lua_rawgeti(m_L, LUA_REGISTRYINDEX, m_tableRef);
				lua_rawgeti(m_L, LUA_REGISTRYINDEX, m_keyRef);
				lua_gettable(m_L, -2);
				lua_remove(m_L, -2); // remove the table
				LogTraceReturnVoid;
			}

			LuaRef get_ref() const
			{
				LogTrace("LuaRef LuaRef:;LuaTableRef::get_ref()");
				LogTraceReturn(LuaRef(*this));
			}

		private:
			lua_State * m_L;
			int m_tableRef;
			int m_keyRef;
		};

		friend struct LuaStack<const LuaTableRef>;
	public:
		LuaRef(lua_State * L) : m_L(L), m_ref(LUA_REFNIL)
		{ LogTrace("LuaRef::LuaRef(lua_State * L)"); LogTraceReturnVoid; }
		LuaRef(lua_State * L, bool fromStack) : m_L(L), m_ref(luaL_ref(L, LUA_REGISTRYINDEX))
		{ LogTrace("LuaRef::LuaRef(lua_State * L, bool fromStack)"); LogTraceReturnVoid; }
		LuaRef(lua_State * L, int idx) : m_L(L), m_ref(LUA_REFNIL)
		{
			LogTrace("LuaRef::LuaRef(lua_State * L, int idx)");
			lua_pushvalue(L, idx);
			m_ref = luaL_ref(L, LUA_REGISTRYINDEX);
			LogTraceReturnVoid;
		}
		template <typename T>
		LuaRef(lua_State * L, const T & v) : m_L(L)
		{
			LogTrace("LuaRef::LuaRef<T>(lua_State * L, const T v)");
			LuaStack<const T>::push(m_L, v);
			m_ref = luaL_ref(L, LUA_REGISTRYINDEX);
			LogTraceReturnVoid;
		}
		LuaRef(const LuaTableRef & v) : m_L(v.state()), m_ref(v.create_ref())
		{ LogTrace("LuaRef::LuaRef(const LuaTableRef & v)"); LogTraceReturnVoid; }
		LuaRef(const LuaRef & cp) : m_L(cp.m_L), m_ref(cp.create_ref())
		{ LogTrace("LuaRef::LuaRef(const LuaRef & cp)"); LogTraceReturnVoid; }
		~LuaRef()
		{
			LogTrace("LuaRef::~LuaRef()");
			luaL_unref(m_L, LUA_REGISTRYINDEX, m_ref);
			LogTraceReturnVoid;
		}

		inline int create_ref() const
		{
			LogTrace("int LuaRef::create_ref() const");
			if (m_ref == LUA_REFNIL)
			{
				LogTraceReturn(m_ref);
			}
			push();
			LogTraceReturn(luaL_ref(m_L, LUA_REGISTRYINDEX));
		}

		inline void set_nil()
		{
			LogTrace("LuaRef::set_nil()");
			if (m_ref != LUA_REFNIL)
			{
				luaL_unref(m_L, LUA_REGISTRYINDEX, m_ref);
				m_ref = LUA_REFNIL;
			}
			LogTraceReturnVoid;
		}

		LuaRef & operator = (const LuaRef & right)
		{
			LogTrace("LuaRef & LuaRef::operator = (const LuaRef & right)");
			luaL_unref(m_L, LUA_REGISTRYINDEX, m_ref);
			right.push();
			m_L = right.state();
			m_ref = luaL_ref(m_L, LUA_REGISTRYINDEX);
			LogTraceReturn(*this);
		}

		template <typename T>
		LuaRef & operator = (const T & right)
		{
			LogTrace("LuaRef & LuaRef::operator = <T>(const T & right)");
			luaL_unref(m_L, LUA_REGISTRYINDEX, m_ref);
			LuaStack<const T>::push(m_L, right);
			m_ref = luaL_ref(m_L, LUA_REGISTRYINDEX);
			LogTraceReturn(*this);
		}


		static inline LuaRef new_table(lua_State * L, int narr = 0, int nrec = 0)
		{
			LogTrace("LuaRef LuaRef::new_table(lua_State * L, int narr, int nrec)");
			lua_createtable(L, narr, nrec);
			LogTraceReturn(LuaRef(L, true));
		}
		static inline LuaRef get_global_var(lua_State * L, const char * name)
		{
			LogTrace("LuaRef LuaRef::get_global_var(lua_State * L, const char * name)");
			lua_getglobal(L, name);
			LogTraceReturn(LuaRef(L, true));
		}


		std::string to_string() const
		{
			LogTrace("string LuaRef::to_string() const");
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
		void print() const
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
		inline lua_State * state() const
		{ LogTrace("lua_State * LuaRef::state()"); LogTraceReturn(m_L); }
		inline void push() const
		{
			LogTrace("LuaRef::push() const");
			lua_rawgeti(m_L, LUA_REGISTRYINDEX, m_ref);
			LogTraceReturnVoid;
		}
		inline void pop()
		{
			LogTrace("LuaRef::pop() const");
			luaL_unref(m_L, LUA_REGISTRYINDEX, m_ref);
			m_ref = luaL_ref(m_L, LUA_REGISTRYINDEX);
			LogTraceReturnVoid;
		}
		inline int type() const
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
		inline bool is_nil() const
		{LogTrace("bool LuaRef::is_nil() const"); LogTraceReturn((type() == LUA_TNIL));}
		inline bool is_number() const
		{LogTrace("bool LuaRef::is_number() const"); LogTraceReturn((type() == LUA_TNUMBER));}
		inline bool is_string() const
		{LogTrace("bool LuaRef::is_string() const"); LogTraceReturn((type() == LUA_TSTRING));}
		inline bool is_table() const
		{LogTrace("bool LuaRef::is_table() const"); LogTraceReturn((type() == LUA_TTABLE));}
		inline bool is_function() const
		{LogTrace("bool LuaRef::is_function() const"); LogTraceReturn((type() == LUA_TFUNCTION));}
		inline bool is_userdata() const
		{LogTrace("bool LuaRef::is_userdata() const"); LogTraceReturn((type() == LUA_TUSERDATA));}
		inline bool is_thread() const
		{LogTrace("bool LuaRef::is_thread() const"); LogTraceReturn((type() == LUA_TTHREAD));}
		inline bool is_lightuserdata() const
		{LogTrace("bool LuaRef::is_lightuserdata() const"); LogTraceReturn((type() == LUA_TLIGHTUSERDATA));}
		inline bool is_bool() const
		{LogTrace("bool LuaRef::is_bool() const"); LogTraceReturn((type() == LUA_TBOOLEAN));}
		inline bool is_cfunction() const
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

		template <typename T>
		T cast() const
		{
			LogTrace("T LuaRef::cast<T>() const");
			LuaStateProtect lsp(m_L);
			push();
			T t(LuaStack<const T>::get(m_L, -1));
			lsp.reset();
			LogTraceReturn(t);
		}
		template <typename T>
		inline operator T () const
		{ LogTrace("LuaRef::operator T<T> () const"); LogTraceReturn(cast<T>()); }


		template <typename T>
		bool operator == (const T & right) const
		{
			LogTrace("bool LuaRef::operator ==<T> (const T & right) const");
			LuaStateProtect lsp(m_L);
			push();
			LuaStack<const T>::push(m_L, right);
			bool eq = lua_equal(m_L, -1, -2) == 1;
			lsp.reset();
			LogTraceReturn(eq);
		}
		template <typename T>
		inline bool operator != (const T & right) const
		{
			LogTrace("bool LuaRef::operator !=<T> (const T & right) const");
			LogTraceReturn(!((*this) == right));
		}
		template <typename T>
		bool operator < (const T & right) const
		{
			LogTrace("bool LuaRef::operator <<T> (const T & right) const");
			LuaStateProtect lsp(m_L);
			push();
			LuaStack<const T>::push(m_L, right);
			bool lt = lua_lessthan(m_L, -2, -1) == 1;
			lsp.reset();
			LogTraceReturn(lt);
		}
		template <typename T>
		bool operator <= (const T & right) const
		{
			LogTrace("bool LuaRef::operator <=<T> (const T & right) const");
			LuaStateProtect lsp(m_L);
			push();
			LuaStack<const T>::push(m_L, right);
			bool elt = lua_equal(m_L, -2, -1) == 1 || lua_lessthan(m_L, -2, -1) == 1;
			lsp.reset();
			LogTraceReturn(elt);
		}
		template <typename T>
		bool operator > (const T & right) const
		{
			LogTrace("bool LuaRef::operator ><T> (const T & right) const");
			LuaStateProtect lsp(m_L);
			push();
			LuaStack<const T>::push(m_L, right);
			bool mt = lua_lessthan(m_L, -1, -2) == 1;
			lsp.reset();
			LogTraceReturn(mt);
		}
		template <typename T>
		bool operator >= (const T & right) const
		{
			LogTrace("bool LuaRef::operator >=<T> (const T & right) const");
			LuaStateProtect lsp(m_L);
			push();
			LuaStack<const T>::push(m_L, right);
			bool emt = lua_equal(m_L, -1, -2) == 1 || lua_lessthan(m_L, -1, -2) == 1;
			lsp.reset();
			LogTraceReturn(emt);
		}
		template <typename T>
		bool rawequal(const T & right) const
		{
			LogTrace("bool LuaRef::rawequal<T>(const T & right) const");
			LuaStateProtect lsp(m_L);
			push();
			LuaStack<const T>::push(m_L, right);
			bool req = lua_rawequal(m_L, -1, -2) == 1;
			lsp.reset();
			LogTraceReturn(req);
		}


		template <typename T>
		void append(const T & v) const
		{
			LogTrace("LuaRef::append<T>(const T & v) const");
			LuaStateProtect lsp(m_L);
			push();
			LuaStack<const T>::push(m_L, v);
			luaL_ref(m_L, -2);
			lsp.reset();
			LogTraceReturnVoid;
		}
		size_t length() const
		{
			LogTrace("LuaRef::length() const");
			LuaStateProtect lsp(m_L, true);
			push();
			size_t len = lua_objlen(m_L, -1);
			lsp.reset();
			LogTraceReturn(len);
		}

		template <typename T>
		LuaRef rawget(const T & key) const
		{
			LogTrace("LuaRef LuaRef::rawget<T>(const T & key) const");
			LuaStateProtect lsp(m_L);
			push();
			LuaStack<const T>::push(m_L, key);
			lua_rawget(m_L, -2);
			LuaRef t(m_L, true);
			lsp.reset();
			LogTraceReturn(t);
		}

		template <typename T>
		LuaTableRef operator[] (const T & key) const
		{
			LogTrace("LuaTableRef LuaRef::operator [] (const T & key) const");
			LuaStack<const T>::push(m_L, key);
			LogTraceReturn(LuaTableRef(m_L, m_ref));
		}
		const LuaRef operator () () const
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
/*
--lua生成
function create_traits(count)

	local str = ""

	for k = 1, count do
		local arg1, arg2, arg3 = "", "", ""
		for ki = 1, k do
			arg1 = string.format("%stypename Arg%d, ", arg1, ki)
			arg2 = string.format("%sconst Arg%d & arg%d, ", arg2, ki, ki)
			arg3 = string.format("%s\t\t\tLuaStack<const Arg%d>::push(m_L, arg%d);\n", arg3, ki, ki)
		end
		arg1 = string.sub(arg1, 1, #arg1-2)
		arg2 = string.sub(arg2, 1, #arg2-2)


		local temp = {}
		table.insert(temp, "\t\ttemplate <")
		table.insert(temp, arg1)
		table.insert(temp, ">\n\t\tconst LuaRef operator()(")
		table.insert(temp, arg2)
		table.insert(temp, ") const\n\t\t{\n\t\t\tLogTrace(\"const LuaRef ")
		table.insert(temp, "LuaRef::operator()(")
		table.insert(temp, arg2)
		table.insert(temp, ") const\");\n\t\t\tpush();\n")
		table.insert(temp, arg3)
		table.insert(temp, string.format("\t\t\tif (lua_pcall(m_L, %d, 1, 0))\n\t\t\t{\n", k))
		table.insert(temp, "\t\t\t\tconst char * errStr = lua_tostring(m_L, -1);\n\t\t\t\tif (errStr) LogScriptError(errStr);\n")
		table.insert(temp, "\t\t\t\tLogTraceReturn(LuaRef(m_L));\n\t\t\t}\n\t\t\tLogTraceReturn(LuaRef(m_L, true));\n\t\t}\n\n")

		str = str .. table.concat(temp)
	end

	print(str)

end

create_traits(20)
*/		
		template <typename Arg1>
		const LuaRef operator()(const Arg1 & arg1) const
		{
			LogTrace("const LuaRef LuaRef::operator()(const Arg1 & arg1) const");
			push();
			LuaStack<const Arg1>::push(m_L, arg1);
			if (lua_pcall(m_L, 1, 1, 0))
			{
				const char * errStr = lua_tostring(m_L, -1);
				if (errStr) LogScriptError(errStr);
				LogTraceReturn(LuaRef(m_L));
			}
			LogTraceReturn(LuaRef(m_L, true));
		}

		template <typename Arg1, typename Arg2>
		const LuaRef operator()(const Arg1 & arg1, const Arg2 & arg2) const
		{
			LogTrace("const LuaRef LuaRef::operator()(const Arg1 & arg1, const Arg2 & arg2) const");
			push();
			LuaStack<const Arg1>::push(m_L, arg1);
			LuaStack<const Arg2>::push(m_L, arg2);
			if (lua_pcall(m_L, 2, 1, 0))
			{
				const char * errStr = lua_tostring(m_L, -1);
				if (errStr) LogScriptError(errStr);
				LogTraceReturn(LuaRef(m_L));
			}
			LogTraceReturn(LuaRef(m_L, true));
		}

		template <typename Arg1, typename Arg2, typename Arg3>
		const LuaRef operator()(const Arg1 & arg1, const Arg2 & arg2, const Arg3 & arg3) const
		{
			LogTrace("const LuaRef LuaRef::operator()(const Arg1 & arg1, const Arg2 & arg2, const Arg3 & arg3) const");
			push();
			LuaStack<const Arg1>::push(m_L, arg1);
			LuaStack<const Arg2>::push(m_L, arg2);
			LuaStack<const Arg3>::push(m_L, arg3);
			if (lua_pcall(m_L, 3, 1, 0))
			{
				const char * errStr = lua_tostring(m_L, -1);
				if (errStr) LogScriptError(errStr);
				LogTraceReturn(LuaRef(m_L));
			}
			LogTraceReturn(LuaRef(m_L, true));
		}

		template <typename Arg1, typename Arg2, typename Arg3, typename Arg4>
		const LuaRef operator()(const Arg1 & arg1, const Arg2 & arg2, const Arg3 & arg3, const Arg4 & arg4) const
		{
			LogTrace("const LuaRef LuaRef::operator()(const Arg1 & arg1, const Arg2 & arg2, const Arg3 & arg3, const Arg4 & arg4) const");
			push();
			LuaStack<const Arg1>::push(m_L, arg1);
			LuaStack<const Arg2>::push(m_L, arg2);
			LuaStack<const Arg3>::push(m_L, arg3);
			LuaStack<const Arg4>::push(m_L, arg4);
			if (lua_pcall(m_L, 4, 1, 0))
			{
				const char * errStr = lua_tostring(m_L, -1);
				if (errStr) LogScriptError(errStr);
				LogTraceReturn(LuaRef(m_L));
			}
			LogTraceReturn(LuaRef(m_L, true));
		}

		template <typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5>
		const LuaRef operator()(const Arg1 & arg1, const Arg2 & arg2, const Arg3 & arg3, const Arg4 & arg4, const Arg5 & arg5) const
		{
			LogTrace("const LuaRef LuaRef::operator()(const Arg1 & arg1, const Arg2 & arg2, const Arg3 & arg3, const Arg4 & arg4, const Arg5 & arg5) const");
			push();
			LuaStack<const Arg1>::push(m_L, arg1);
			LuaStack<const Arg2>::push(m_L, arg2);
			LuaStack<const Arg3>::push(m_L, arg3);
			LuaStack<const Arg4>::push(m_L, arg4);
			LuaStack<const Arg5>::push(m_L, arg5);
			if (lua_pcall(m_L, 5, 1, 0))
			{
				const char * errStr = lua_tostring(m_L, -1);
				if (errStr) LogScriptError(errStr);
				LogTraceReturn(LuaRef(m_L));
			}
			LogTraceReturn(LuaRef(m_L, true));
		}

		template <typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6>
		const LuaRef operator()(const Arg1 & arg1, const Arg2 & arg2, const Arg3 & arg3, const Arg4 & arg4, const Arg5 & arg5, const Arg6 & arg6) const
		{
			LogTrace("const LuaRef LuaRef::operator()(const Arg1 & arg1, const Arg2 & arg2, const Arg3 & arg3, const Arg4 & arg4, const Arg5 & arg5, const Arg6 & arg6) const");
			push();
			LuaStack<const Arg1>::push(m_L, arg1);
			LuaStack<const Arg2>::push(m_L, arg2);
			LuaStack<const Arg3>::push(m_L, arg3);
			LuaStack<const Arg4>::push(m_L, arg4);
			LuaStack<const Arg5>::push(m_L, arg5);
			LuaStack<const Arg6>::push(m_L, arg6);
			if (lua_pcall(m_L, 6, 1, 0))
			{
				const char * errStr = lua_tostring(m_L, -1);
				if (errStr) LogScriptError(errStr);
				LogTraceReturn(LuaRef(m_L));
			}
			LogTraceReturn(LuaRef(m_L, true));
		}

		template <typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7>
		const LuaRef operator()(const Arg1 & arg1, const Arg2 & arg2, const Arg3 & arg3, const Arg4 & arg4, const Arg5 & arg5, const Arg6 & arg6, const Arg7 & arg7) const
		{
			LogTrace("const LuaRef LuaRef::operator()(const Arg1 & arg1, const Arg2 & arg2, const Arg3 & arg3, const Arg4 & arg4, const Arg5 & arg5, const Arg6 & arg6, const Arg7 & arg7) const");
			push();
			LuaStack<const Arg1>::push(m_L, arg1);
			LuaStack<const Arg2>::push(m_L, arg2);
			LuaStack<const Arg3>::push(m_L, arg3);
			LuaStack<const Arg4>::push(m_L, arg4);
			LuaStack<const Arg5>::push(m_L, arg5);
			LuaStack<const Arg6>::push(m_L, arg6);
			LuaStack<const Arg7>::push(m_L, arg7);
			if (lua_pcall(m_L, 7, 1, 0))
			{
				const char * errStr = lua_tostring(m_L, -1);
				if (errStr) LogScriptError(errStr);
				LogTraceReturn(LuaRef(m_L));
			}
			LogTraceReturn(LuaRef(m_L, true));
		}

		template <typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7, typename Arg8>
		const LuaRef operator()(const Arg1 & arg1, const Arg2 & arg2, const Arg3 & arg3, const Arg4 & arg4, const Arg5 & arg5, const Arg6 & arg6, const Arg7 & arg7, const Arg8 & arg8) const
		{
			LogTrace("const LuaRef LuaRef::operator()(const Arg1 & arg1, const Arg2 & arg2, const Arg3 & arg3, const Arg4 & arg4, const Arg5 & arg5, const Arg6 & arg6, const Arg7 & arg7, const Arg8 & arg8) const");
			push();
			LuaStack<const Arg1>::push(m_L, arg1);
			LuaStack<const Arg2>::push(m_L, arg2);
			LuaStack<const Arg3>::push(m_L, arg3);
			LuaStack<const Arg4>::push(m_L, arg4);
			LuaStack<const Arg5>::push(m_L, arg5);
			LuaStack<const Arg6>::push(m_L, arg6);
			LuaStack<const Arg7>::push(m_L, arg7);
			LuaStack<const Arg8>::push(m_L, arg8);
			if (lua_pcall(m_L, 8, 1, 0))
			{
				const char * errStr = lua_tostring(m_L, -1);
				if (errStr) LogScriptError(errStr);
				LogTraceReturn(LuaRef(m_L));
			}
			LogTraceReturn(LuaRef(m_L, true));
		}

		template <typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7, typename Arg8, typename Arg9>
		const LuaRef operator()(const Arg1 & arg1, const Arg2 & arg2, const Arg3 & arg3, const Arg4 & arg4, const Arg5 & arg5, const Arg6 & arg6, const Arg7 & arg7, const Arg8 & arg8, const Arg9 & arg9) const
		{
			LogTrace("const LuaRef LuaRef::operator()(const Arg1 & arg1, const Arg2 & arg2, const Arg3 & arg3, const Arg4 & arg4, const Arg5 & arg5, const Arg6 & arg6, const Arg7 & arg7, const Arg8 & arg8, const Arg9 & arg9) const");
			push();
			LuaStack<const Arg1>::push(m_L, arg1);
			LuaStack<const Arg2>::push(m_L, arg2);
			LuaStack<const Arg3>::push(m_L, arg3);
			LuaStack<const Arg4>::push(m_L, arg4);
			LuaStack<const Arg5>::push(m_L, arg5);
			LuaStack<const Arg6>::push(m_L, arg6);
			LuaStack<const Arg7>::push(m_L, arg7);
			LuaStack<const Arg8>::push(m_L, arg8);
			LuaStack<const Arg9>::push(m_L, arg9);
			if (lua_pcall(m_L, 9, 1, 0))
			{
				const char * errStr = lua_tostring(m_L, -1);
				if (errStr) LogScriptError(errStr);
				LogTraceReturn(LuaRef(m_L));
			}
			LogTraceReturn(LuaRef(m_L, true));
		}

		template <typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7, typename Arg8, typename Arg9, typename Arg10>
		const LuaRef operator()(const Arg1 & arg1, const Arg2 & arg2, const Arg3 & arg3, const Arg4 & arg4, const Arg5 & arg5, const Arg6 & arg6, const Arg7 & arg7, const Arg8 & arg8, const Arg9 & arg9, const Arg10 & arg10) const
		{
			LogTrace("const LuaRef LuaRef::operator()(const Arg1 & arg1, const Arg2 & arg2, const Arg3 & arg3, const Arg4 & arg4, const Arg5 & arg5, const Arg6 & arg6, const Arg7 & arg7, const Arg8 & arg8, const Arg9 & arg9, const Arg10 & arg10) const");
			push();
			LuaStack<const Arg1>::push(m_L, arg1);
			LuaStack<const Arg2>::push(m_L, arg2);
			LuaStack<const Arg3>::push(m_L, arg3);
			LuaStack<const Arg4>::push(m_L, arg4);
			LuaStack<const Arg5>::push(m_L, arg5);
			LuaStack<const Arg6>::push(m_L, arg6);
			LuaStack<const Arg7>::push(m_L, arg7);
			LuaStack<const Arg8>::push(m_L, arg8);
			LuaStack<const Arg9>::push(m_L, arg9);
			LuaStack<const Arg10>::push(m_L, arg10);
			if (lua_pcall(m_L, 10, 1, 0))
			{
				const char * errStr = lua_tostring(m_L, -1);
				if (errStr) LogScriptError(errStr);
				LogTraceReturn(LuaRef(m_L));
			}
			LogTraceReturn(LuaRef(m_L, true));
		}

		template <typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7, typename Arg8, typename Arg9, typename Arg10, typename Arg11>
		const LuaRef operator()(const Arg1 & arg1, const Arg2 & arg2, const Arg3 & arg3, const Arg4 & arg4, const Arg5 & arg5, const Arg6 & arg6, const Arg7 & arg7, const Arg8 & arg8, const Arg9 & arg9, const Arg10 & arg10, const Arg11 & arg11) const
		{
			LogTrace("const LuaRef LuaRef::operator()(const Arg1 & arg1, const Arg2 & arg2, const Arg3 & arg3, const Arg4 & arg4, const Arg5 & arg5, const Arg6 & arg6, const Arg7 & arg7, const Arg8 & arg8, const Arg9 & arg9, const Arg10 & arg10, const Arg11 & arg11) const");
			push();
			LuaStack<const Arg1>::push(m_L, arg1);
			LuaStack<const Arg2>::push(m_L, arg2);
			LuaStack<const Arg3>::push(m_L, arg3);
			LuaStack<const Arg4>::push(m_L, arg4);
			LuaStack<const Arg5>::push(m_L, arg5);
			LuaStack<const Arg6>::push(m_L, arg6);
			LuaStack<const Arg7>::push(m_L, arg7);
			LuaStack<const Arg8>::push(m_L, arg8);
			LuaStack<const Arg9>::push(m_L, arg9);
			LuaStack<const Arg10>::push(m_L, arg10);
			LuaStack<const Arg11>::push(m_L, arg11);
			if (lua_pcall(m_L, 11, 1, 0))
			{
				const char * errStr = lua_tostring(m_L, -1);
				if (errStr) LogScriptError(errStr);
				LogTraceReturn(LuaRef(m_L));
			}
			LogTraceReturn(LuaRef(m_L, true));
		}

		template <typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7, typename Arg8, typename Arg9, typename Arg10, typename Arg11, typename Arg12>
		const LuaRef operator()(const Arg1 & arg1, const Arg2 & arg2, const Arg3 & arg3, const Arg4 & arg4, const Arg5 & arg5, const Arg6 & arg6, const Arg7 & arg7, const Arg8 & arg8, const Arg9 & arg9, const Arg10 & arg10, const Arg11 & arg11, const Arg12 & arg12) const
		{
			LogTrace("const LuaRef LuaRef::operator()(const Arg1 & arg1, const Arg2 & arg2, const Arg3 & arg3, const Arg4 & arg4, const Arg5 & arg5, const Arg6 & arg6, const Arg7 & arg7, const Arg8 & arg8, const Arg9 & arg9, const Arg10 & arg10, const Arg11 & arg11, const Arg12 & arg12) const");
			push();
			LuaStack<const Arg1>::push(m_L, arg1);
			LuaStack<const Arg2>::push(m_L, arg2);
			LuaStack<const Arg3>::push(m_L, arg3);
			LuaStack<const Arg4>::push(m_L, arg4);
			LuaStack<const Arg5>::push(m_L, arg5);
			LuaStack<const Arg6>::push(m_L, arg6);
			LuaStack<const Arg7>::push(m_L, arg7);
			LuaStack<const Arg8>::push(m_L, arg8);
			LuaStack<const Arg9>::push(m_L, arg9);
			LuaStack<const Arg10>::push(m_L, arg10);
			LuaStack<const Arg11>::push(m_L, arg11);
			LuaStack<const Arg12>::push(m_L, arg12);
			if (lua_pcall(m_L, 12, 1, 0))
			{
				const char * errStr = lua_tostring(m_L, -1);
				if (errStr) LogScriptError(errStr);
				LogTraceReturn(LuaRef(m_L));
			}
			LogTraceReturn(LuaRef(m_L, true));
		}

		template <typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7, typename Arg8, typename Arg9, typename Arg10, typename Arg11, typename Arg12, typename Arg13>
		const LuaRef operator()(const Arg1 & arg1, const Arg2 & arg2, const Arg3 & arg3, const Arg4 & arg4, const Arg5 & arg5, const Arg6 & arg6, const Arg7 & arg7, const Arg8 & arg8, const Arg9 & arg9, const Arg10 & arg10, const Arg11 & arg11, const Arg12 & arg12, const Arg13 & arg13) const
		{
			LogTrace("const LuaRef LuaRef::operator()(const Arg1 & arg1, const Arg2 & arg2, const Arg3 & arg3, const Arg4 & arg4, const Arg5 & arg5, const Arg6 & arg6, const Arg7 & arg7, const Arg8 & arg8, const Arg9 & arg9, const Arg10 & arg10, const Arg11 & arg11, const Arg12 & arg12, const Arg13 & arg13) const");
			push();
			LuaStack<const Arg1>::push(m_L, arg1);
			LuaStack<const Arg2>::push(m_L, arg2);
			LuaStack<const Arg3>::push(m_L, arg3);
			LuaStack<const Arg4>::push(m_L, arg4);
			LuaStack<const Arg5>::push(m_L, arg5);
			LuaStack<const Arg6>::push(m_L, arg6);
			LuaStack<const Arg7>::push(m_L, arg7);
			LuaStack<const Arg8>::push(m_L, arg8);
			LuaStack<const Arg9>::push(m_L, arg9);
			LuaStack<const Arg10>::push(m_L, arg10);
			LuaStack<const Arg11>::push(m_L, arg11);
			LuaStack<const Arg12>::push(m_L, arg12);
			LuaStack<const Arg13>::push(m_L, arg13);
			if (lua_pcall(m_L, 13, 1, 0))
			{
				const char * errStr = lua_tostring(m_L, -1);
				if (errStr) LogScriptError(errStr);
				LogTraceReturn(LuaRef(m_L));
			}
			LogTraceReturn(LuaRef(m_L, true));
		}

		template <typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7, typename Arg8, typename Arg9, typename Arg10, typename Arg11, typename Arg12, typename Arg13, typename Arg14>
		const LuaRef operator()(const Arg1 & arg1, const Arg2 & arg2, const Arg3 & arg3, const Arg4 & arg4, const Arg5 & arg5, const Arg6 & arg6, const Arg7 & arg7, const Arg8 & arg8, const Arg9 & arg9, const Arg10 & arg10, const Arg11 & arg11, const Arg12 & arg12, const Arg13 & arg13, const Arg14 & arg14) const
		{
			LogTrace("const LuaRef LuaRef::operator()(const Arg1 & arg1, const Arg2 & arg2, const Arg3 & arg3, const Arg4 & arg4, const Arg5 & arg5, const Arg6 & arg6, const Arg7 & arg7, const Arg8 & arg8, const Arg9 & arg9, const Arg10 & arg10, const Arg11 & arg11, const Arg12 & arg12, const Arg13 & arg13, const Arg14 & arg14) const");
			push();
			LuaStack<const Arg1>::push(m_L, arg1);
			LuaStack<const Arg2>::push(m_L, arg2);
			LuaStack<const Arg3>::push(m_L, arg3);
			LuaStack<const Arg4>::push(m_L, arg4);
			LuaStack<const Arg5>::push(m_L, arg5);
			LuaStack<const Arg6>::push(m_L, arg6);
			LuaStack<const Arg7>::push(m_L, arg7);
			LuaStack<const Arg8>::push(m_L, arg8);
			LuaStack<const Arg9>::push(m_L, arg9);
			LuaStack<const Arg10>::push(m_L, arg10);
			LuaStack<const Arg11>::push(m_L, arg11);
			LuaStack<const Arg12>::push(m_L, arg12);
			LuaStack<const Arg13>::push(m_L, arg13);
			LuaStack<const Arg14>::push(m_L, arg14);
			if (lua_pcall(m_L, 14, 1, 0))
			{
				const char * errStr = lua_tostring(m_L, -1);
				if (errStr) LogScriptError(errStr);
				LogTraceReturn(LuaRef(m_L));
			}
			LogTraceReturn(LuaRef(m_L, true));
		}

		template <typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7, typename Arg8, typename Arg9, typename Arg10, typename Arg11, typename Arg12, typename Arg13, typename Arg14, typename Arg15>
		const LuaRef operator()(const Arg1 & arg1, const Arg2 & arg2, const Arg3 & arg3, const Arg4 & arg4, const Arg5 & arg5, const Arg6 & arg6, const Arg7 & arg7, const Arg8 & arg8, const Arg9 & arg9, const Arg10 & arg10, const Arg11 & arg11, const Arg12 & arg12, const Arg13 & arg13, const Arg14 & arg14, const Arg15 & arg15) const
		{
			LogTrace("const LuaRef LuaRef::operator()(const Arg1 & arg1, const Arg2 & arg2, const Arg3 & arg3, const Arg4 & arg4, const Arg5 & arg5, const Arg6 & arg6, const Arg7 & arg7, const Arg8 & arg8, const Arg9 & arg9, const Arg10 & arg10, const Arg11 & arg11, const Arg12 & arg12, const Arg13 & arg13, const Arg14 & arg14, const Arg15 & arg15) const");
			push();
			LuaStack<const Arg1>::push(m_L, arg1);
			LuaStack<const Arg2>::push(m_L, arg2);
			LuaStack<const Arg3>::push(m_L, arg3);
			LuaStack<const Arg4>::push(m_L, arg4);
			LuaStack<const Arg5>::push(m_L, arg5);
			LuaStack<const Arg6>::push(m_L, arg6);
			LuaStack<const Arg7>::push(m_L, arg7);
			LuaStack<const Arg8>::push(m_L, arg8);
			LuaStack<const Arg9>::push(m_L, arg9);
			LuaStack<const Arg10>::push(m_L, arg10);
			LuaStack<const Arg11>::push(m_L, arg11);
			LuaStack<const Arg12>::push(m_L, arg12);
			LuaStack<const Arg13>::push(m_L, arg13);
			LuaStack<const Arg14>::push(m_L, arg14);
			LuaStack<const Arg15>::push(m_L, arg15);
			if (lua_pcall(m_L, 15, 1, 0))
			{
				const char * errStr = lua_tostring(m_L, -1);
				if (errStr) LogScriptError(errStr);
				LogTraceReturn(LuaRef(m_L));
			}
			LogTraceReturn(LuaRef(m_L, true));
		}

		template <typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7, typename Arg8, typename Arg9, typename Arg10, typename Arg11, typename Arg12, typename Arg13, typename Arg14, typename Arg15, typename Arg16>
		const LuaRef operator()(const Arg1 & arg1, const Arg2 & arg2, const Arg3 & arg3, const Arg4 & arg4, const Arg5 & arg5, const Arg6 & arg6, const Arg7 & arg7, const Arg8 & arg8, const Arg9 & arg9, const Arg10 & arg10, const Arg11 & arg11, const Arg12 & arg12, const Arg13 & arg13, const Arg14 & arg14, const Arg15 & arg15, const Arg16 & arg16) const
		{
			LogTrace("const LuaRef LuaRef::operator()(const Arg1 & arg1, const Arg2 & arg2, const Arg3 & arg3, const Arg4 & arg4, const Arg5 & arg5, const Arg6 & arg6, const Arg7 & arg7, const Arg8 & arg8, const Arg9 & arg9, const Arg10 & arg10, const Arg11 & arg11, const Arg12 & arg12, const Arg13 & arg13, const Arg14 & arg14, const Arg15 & arg15, const Arg16 & arg16) const");
			push();
			LuaStack<const Arg1>::push(m_L, arg1);
			LuaStack<const Arg2>::push(m_L, arg2);
			LuaStack<const Arg3>::push(m_L, arg3);
			LuaStack<const Arg4>::push(m_L, arg4);
			LuaStack<const Arg5>::push(m_L, arg5);
			LuaStack<const Arg6>::push(m_L, arg6);
			LuaStack<const Arg7>::push(m_L, arg7);
			LuaStack<const Arg8>::push(m_L, arg8);
			LuaStack<const Arg9>::push(m_L, arg9);
			LuaStack<const Arg10>::push(m_L, arg10);
			LuaStack<const Arg11>::push(m_L, arg11);
			LuaStack<const Arg12>::push(m_L, arg12);
			LuaStack<const Arg13>::push(m_L, arg13);
			LuaStack<const Arg14>::push(m_L, arg14);
			LuaStack<const Arg15>::push(m_L, arg15);
			LuaStack<const Arg16>::push(m_L, arg16);
			if (lua_pcall(m_L, 16, 1, 0))
			{
				const char * errStr = lua_tostring(m_L, -1);
				if (errStr) LogScriptError(errStr);
				LogTraceReturn(LuaRef(m_L));
			}
			LogTraceReturn(LuaRef(m_L, true));
		}

		template <typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7, typename Arg8, typename Arg9, typename Arg10, typename Arg11, typename Arg12, typename Arg13, typename Arg14, typename Arg15, typename Arg16, typename Arg17>
		const LuaRef operator()(const Arg1 & arg1, const Arg2 & arg2, const Arg3 & arg3, const Arg4 & arg4, const Arg5 & arg5, const Arg6 & arg6, const Arg7 & arg7, const Arg8 & arg8, const Arg9 & arg9, const Arg10 & arg10, const Arg11 & arg11, const Arg12 & arg12, const Arg13 & arg13, const Arg14 & arg14, const Arg15 & arg15, const Arg16 & arg16, const Arg17 & arg17) const
		{
			LogTrace("const LuaRef LuaRef::operator()(const Arg1 & arg1, const Arg2 & arg2, const Arg3 & arg3, const Arg4 & arg4, const Arg5 & arg5, const Arg6 & arg6, const Arg7 & arg7, const Arg8 & arg8, const Arg9 & arg9, const Arg10 & arg10, const Arg11 & arg11, const Arg12 & arg12, const Arg13 & arg13, const Arg14 & arg14, const Arg15 & arg15, const Arg16 & arg16, const Arg17 & arg17) const");
			push();
			LuaStack<const Arg1>::push(m_L, arg1);
			LuaStack<const Arg2>::push(m_L, arg2);
			LuaStack<const Arg3>::push(m_L, arg3);
			LuaStack<const Arg4>::push(m_L, arg4);
			LuaStack<const Arg5>::push(m_L, arg5);
			LuaStack<const Arg6>::push(m_L, arg6);
			LuaStack<const Arg7>::push(m_L, arg7);
			LuaStack<const Arg8>::push(m_L, arg8);
			LuaStack<const Arg9>::push(m_L, arg9);
			LuaStack<const Arg10>::push(m_L, arg10);
			LuaStack<const Arg11>::push(m_L, arg11);
			LuaStack<const Arg12>::push(m_L, arg12);
			LuaStack<const Arg13>::push(m_L, arg13);
			LuaStack<const Arg14>::push(m_L, arg14);
			LuaStack<const Arg15>::push(m_L, arg15);
			LuaStack<const Arg16>::push(m_L, arg16);
			LuaStack<const Arg17>::push(m_L, arg17);
			if (lua_pcall(m_L, 17, 1, 0))
			{
				const char * errStr = lua_tostring(m_L, -1);
				if (errStr) LogScriptError(errStr);
				LogTraceReturn(LuaRef(m_L));
			}
			LogTraceReturn(LuaRef(m_L, true));
		}

		template <typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7, typename Arg8, typename Arg9, typename Arg10, typename Arg11, typename Arg12, typename Arg13, typename Arg14, typename Arg15, typename Arg16, typename Arg17, typename Arg18>
		const LuaRef operator()(const Arg1 & arg1, const Arg2 & arg2, const Arg3 & arg3, const Arg4 & arg4, const Arg5 & arg5, const Arg6 & arg6, const Arg7 & arg7, const Arg8 & arg8, const Arg9 & arg9, const Arg10 & arg10, const Arg11 & arg11, const Arg12 & arg12, const Arg13 & arg13, const Arg14 & arg14, const Arg15 & arg15, const Arg16 & arg16, const Arg17 & arg17, const Arg18 & arg18) const
		{
			LogTrace("const LuaRef LuaRef::operator()(const Arg1 & arg1, const Arg2 & arg2, const Arg3 & arg3, const Arg4 & arg4, const Arg5 & arg5, const Arg6 & arg6, const Arg7 & arg7, const Arg8 & arg8, const Arg9 & arg9, const Arg10 & arg10, const Arg11 & arg11, const Arg12 & arg12, const Arg13 & arg13, const Arg14 & arg14, const Arg15 & arg15, const Arg16 & arg16, const Arg17 & arg17, const Arg18 & arg18) const");
			push();
			LuaStack<const Arg1>::push(m_L, arg1);
			LuaStack<const Arg2>::push(m_L, arg2);
			LuaStack<const Arg3>::push(m_L, arg3);
			LuaStack<const Arg4>::push(m_L, arg4);
			LuaStack<const Arg5>::push(m_L, arg5);
			LuaStack<const Arg6>::push(m_L, arg6);
			LuaStack<const Arg7>::push(m_L, arg7);
			LuaStack<const Arg8>::push(m_L, arg8);
			LuaStack<const Arg9>::push(m_L, arg9);
			LuaStack<const Arg10>::push(m_L, arg10);
			LuaStack<const Arg11>::push(m_L, arg11);
			LuaStack<const Arg12>::push(m_L, arg12);
			LuaStack<const Arg13>::push(m_L, arg13);
			LuaStack<const Arg14>::push(m_L, arg14);
			LuaStack<const Arg15>::push(m_L, arg15);
			LuaStack<const Arg16>::push(m_L, arg16);
			LuaStack<const Arg17>::push(m_L, arg17);
			LuaStack<const Arg18>::push(m_L, arg18);
			if (lua_pcall(m_L, 18, 1, 0))
			{
				const char * errStr = lua_tostring(m_L, -1);
				if (errStr) LogScriptError(errStr);
				LogTraceReturn(LuaRef(m_L));
			}
			LogTraceReturn(LuaRef(m_L, true));
		}

		template <typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7, typename Arg8, typename Arg9, typename Arg10, typename Arg11, typename Arg12, typename Arg13, typename Arg14, typename Arg15, typename Arg16, typename Arg17, typename Arg18, typename Arg19>
		const LuaRef operator()(const Arg1 & arg1, const Arg2 & arg2, const Arg3 & arg3, const Arg4 & arg4, const Arg5 & arg5, const Arg6 & arg6, const Arg7 & arg7, const Arg8 & arg8, const Arg9 & arg9, const Arg10 & arg10, const Arg11 & arg11, const Arg12 & arg12, const Arg13 & arg13, const Arg14 & arg14, const Arg15 & arg15, const Arg16 & arg16, const Arg17 & arg17, const Arg18 & arg18, const Arg19 & arg19) const
		{
			LogTrace("const LuaRef LuaRef::operator()(const Arg1 & arg1, const Arg2 & arg2, const Arg3 & arg3, const Arg4 & arg4, const Arg5 & arg5, const Arg6 & arg6, const Arg7 & arg7, const Arg8 & arg8, const Arg9 & arg9, const Arg10 & arg10, const Arg11 & arg11, const Arg12 & arg12, const Arg13 & arg13, const Arg14 & arg14, const Arg15 & arg15, const Arg16 & arg16, const Arg17 & arg17, const Arg18 & arg18, const Arg19 & arg19) const");
			push();
			LuaStack<const Arg1>::push(m_L, arg1);
			LuaStack<const Arg2>::push(m_L, arg2);
			LuaStack<const Arg3>::push(m_L, arg3);
			LuaStack<const Arg4>::push(m_L, arg4);
			LuaStack<const Arg5>::push(m_L, arg5);
			LuaStack<const Arg6>::push(m_L, arg6);
			LuaStack<const Arg7>::push(m_L, arg7);
			LuaStack<const Arg8>::push(m_L, arg8);
			LuaStack<const Arg9>::push(m_L, arg9);
			LuaStack<const Arg10>::push(m_L, arg10);
			LuaStack<const Arg11>::push(m_L, arg11);
			LuaStack<const Arg12>::push(m_L, arg12);
			LuaStack<const Arg13>::push(m_L, arg13);
			LuaStack<const Arg14>::push(m_L, arg14);
			LuaStack<const Arg15>::push(m_L, arg15);
			LuaStack<const Arg16>::push(m_L, arg16);
			LuaStack<const Arg17>::push(m_L, arg17);
			LuaStack<const Arg18>::push(m_L, arg18);
			LuaStack<const Arg19>::push(m_L, arg19);
			if (lua_pcall(m_L, 19, 1, 0))
			{
				const char * errStr = lua_tostring(m_L, -1);
				if (errStr) LogScriptError(errStr);
				LogTraceReturn(LuaRef(m_L));
			}
			LogTraceReturn(LuaRef(m_L, true));
		}

		template <typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7, typename Arg8, typename Arg9, typename Arg10, typename Arg11, typename Arg12, typename Arg13, typename Arg14, typename Arg15, typename Arg16, typename Arg17, typename Arg18, typename Arg19, typename Arg20>
		const LuaRef operator()(const Arg1 & arg1, const Arg2 & arg2, const Arg3 & arg3, const Arg4 & arg4, const Arg5 & arg5, const Arg6 & arg6, const Arg7 & arg7, const Arg8 & arg8, const Arg9 & arg9, const Arg10 & arg10, const Arg11 & arg11, const Arg12 & arg12, const Arg13 & arg13, const Arg14 & arg14, const Arg15 & arg15, const Arg16 & arg16, const Arg17 & arg17, const Arg18 & arg18, const Arg19 & arg19, const Arg20 & arg20) const
		{
			LogTrace("const LuaRef LuaRef::operator()(const Arg1 & arg1, const Arg2 & arg2, const Arg3 & arg3, const Arg4 & arg4, const Arg5 & arg5, const Arg6 & arg6, const Arg7 & arg7, const Arg8 & arg8, const Arg9 & arg9, const Arg10 & arg10, const Arg11 & arg11, const Arg12 & arg12, const Arg13 & arg13, const Arg14 & arg14, const Arg15 & arg15, const Arg16 & arg16, const Arg17 & arg17, const Arg18 & arg18, const Arg19 & arg19, const Arg20 & arg20) const");
			push();
			LuaStack<const Arg1>::push(m_L, arg1);
			LuaStack<const Arg2>::push(m_L, arg2);
			LuaStack<const Arg3>::push(m_L, arg3);
			LuaStack<const Arg4>::push(m_L, arg4);
			LuaStack<const Arg5>::push(m_L, arg5);
			LuaStack<const Arg6>::push(m_L, arg6);
			LuaStack<const Arg7>::push(m_L, arg7);
			LuaStack<const Arg8>::push(m_L, arg8);
			LuaStack<const Arg9>::push(m_L, arg9);
			LuaStack<const Arg10>::push(m_L, arg10);
			LuaStack<const Arg11>::push(m_L, arg11);
			LuaStack<const Arg12>::push(m_L, arg12);
			LuaStack<const Arg13>::push(m_L, arg13);
			LuaStack<const Arg14>::push(m_L, arg14);
			LuaStack<const Arg15>::push(m_L, arg15);
			LuaStack<const Arg16>::push(m_L, arg16);
			LuaStack<const Arg17>::push(m_L, arg17);
			LuaStack<const Arg18>::push(m_L, arg18);
			LuaStack<const Arg19>::push(m_L, arg19);
			LuaStack<const Arg20>::push(m_L, arg20);
			if (lua_pcall(m_L, 20, 1, 0))
			{
				const char * errStr = lua_tostring(m_L, -1);
				if (errStr) LogScriptError(errStr);
				LogTraceReturn(LuaRef(m_L));
			}
			LogTraceReturn(LuaRef(m_L, true));
		}

	private:
		lua_State * m_L;
		int m_ref;

	};


	template <>
	struct LIGHTINK_TEMPLATE_DECL LuaStack <const LuaRef>
	{
		static inline void push(lua_State * L, const LuaRef & v)
		{
			LogTrace("LuaStack<LuaRef>::push(lua_State * L, LuaRef & v)");
			if (L != v.state())
			{
				LogScriptErrorJump(L, "Error!!!The LuaStack<LuaRef>::push vm is not LuaRef vm!!!");
			}
			v.push();
			LogTraceReturnVoid;
		}
		
		static inline LuaRef get(lua_State * L, int idx)
		{
			LogTrace("LuaRef LuaStack<LuaRef>::get(lua_State * L, int idx)");
			LogTraceReturn(LuaRef(L, idx));
		}
	};
	template <>
	struct LIGHTINK_TEMPLATE_DECL LuaStack <const LuaRef::LuaTableRef>
	{
		static inline void push(lua_State * L, const LuaRef::LuaTableRef & v)
		{
			LogTrace("LuaStack<LuaRef::LuaTableRef>::push(lua_State * L, const LuaRef::LuaTableRef & v)");
			if (L != v.state())
			{
				LogScriptErrorJump(L, "Error!!!The LuaStack<LuaRef::LuaTableRef>::push vm is not LuaRef vm!!!");
			}
			v.push();
			LogTraceReturnVoid;
		}
		
	};


}

#endif