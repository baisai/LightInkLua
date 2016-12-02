


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

#ifndef LIGHTINK_LUAENGINE_LUASTACK_H_
#define LIGHTINK_LUAENGINE_LUASTACK_H_

#include <string>
#include <vector>
#include <map>
#include <set>
#include "Common/Type.h"
#include "Common/Log.h"
#include "LuaEngine/LuaUserdata.h"
#include "Common/RuntimeError.h"
#include "LuaEngine/LuaFixFunction.h"
#include "Common/CharPtrBridge.h"
#include "Common/TypeTool.h"

namespace LightInk
{
	struct LIGHTINK_DECL LuaTypeNil
	{  };

	template <typename T>
	struct LIGHTINK_TEMPLATE_DECL LuaStack;

/*
--lua生成

local type_str = {
	["char"] = "\t\t\tlua_pushinteger(L, static_cast <lua_Integer> (value));\n",
	["signed char"] = "\t\t\tlua_pushinteger(L, static_cast <lua_Integer> (value));\n",
	["unsigned char"] = "\t\t\tlua_pushinteger(L, static_cast <lua_Integer> (value));\n",
	["short"] = "\t\t\tlua_pushinteger(L, static_cast <lua_Integer> (value));\n",
	["unsigned short"] = "\t\t\tlua_pushnumber(L, static_cast <lua_Number> (value));\n",
	["int"] = "\t\t\tlua_pushinteger(L, static_cast <lua_Integer> (value));\n",
	["unsigned int"] = "\t\t\tlua_pushnumber(L, static_cast <lua_Number> (value));\n",
	["long"] = "\t\t\tlua_pushnumber(L, static_cast <lua_Number> (value));\n",
	["unsigned long"] = "\t\t\tlua_pushnumber(L, static_cast <lua_Number> (value));\n",
	["long long"] = "\t\t\tlua_pushnumber(L, static_cast <lua_Number> (value));\n",
	["unsigned long long"] = "\t\t\tlua_pushnumber(L, static_cast <lua_Number> (value));\n",
	["float"] = "\t\t\tlua_pushnumber(L, static_cast <lua_Number> (value));\n",
	["double"] = "\t\t\tlua_pushnumber(L, static_cast <lua_Number> (value));\n",
	["bool"] = "\t\t\tlua_pushboolean(L, value ? 1 : 0);\n",

	["const char"] = "\t\t\tlua_pushinteger(L, static_cast <lua_Integer> (value));\n",
	["const signed char"] = "\t\t\tlua_pushinteger(L, static_cast <lua_Integer> (value));\n",
	["const unsigned char"] = "\t\t\tlua_pushinteger(L, static_cast <lua_Integer> (value));\n",
	["const short"] = "\t\t\tlua_pushinteger(L, static_cast <lua_Integer> (value));\n",
	["const unsigned short"] = "\t\t\tlua_pushnumber(L, static_cast <lua_Number> (value));\n",
	["const int"] = "\t\t\tlua_pushinteger(L, static_cast <lua_Integer> (value));\n",
	["const unsigned int"] = "\t\t\tlua_pushnumber(L, static_cast <lua_Number> (value));\n",
	["const long"] = "\t\t\tlua_pushnumber(L, static_cast <lua_Number> (value));\n",
	["const unsigned long"] = "\t\t\tlua_pushnumber(L, static_cast <lua_Number> (value));\n",
	["const long long"] = "\t\t\tlua_pushnumber(L, static_cast <lua_Number> (value));\n",
	["const unsigned long long"] = "\t\t\tlua_pushnumber(L, static_cast <lua_Number> (value));\n",
	["const float"] = "\t\t\tlua_pushnumber(L, static_cast <lua_Number> (value));\n",
	["const double"] = "\t\t\tlua_pushnumber(L, static_cast <lua_Number> (value));\n",
	["const bool"] = "\t\t\tlua_pushboolean(L, value ? 1 : 0);\n",
}

local check_str = {
	["char"] = "\t\t\tLogTraceReturn(static_cast<char>(luaL_checkinteger(L, idx)));\n",
	["signed char"] = "\t\t\tLogTraceReturn(static_cast<signed char>(luaL_checkinteger(L, idx)));\n",
	["unsigned char"] = "\t\t\tLogTraceReturn(static_cast<unsigned char>(luaL_checkinteger(L, idx)));\n",
	["short"] = "\t\t\tLogTraceReturn(static_cast<short>(luaL_checkinteger(L, idx)));\n",
	["unsigned short"] = "\t\t\tLogTraceReturn(static_cast<unsigned short>(luaL_checknumber(L, idx)));\n",
	["int"] = "\t\t\tLogTraceReturn(static_cast<int>(luaL_checkinteger(L, idx)));\n",
	["unsigned int"] = "\t\t\tLogTraceReturn(static_cast<unsigned int>(luaL_checknumber(L, idx)));\n",
	["long"] = "\t\t\tLogTraceReturn(static_cast<long>(luaL_checknumber(L, idx)));\n",
	["unsigned long"] = "\t\t\tLogTraceReturn(static_cast<unsigned long>(luaL_checknumber(L, idx)));\n",
	["long long"] = "\t\t\tLogTraceReturn(static_cast<long long>(luaL_checknumber(L, idx)));\n",
	["unsigned long long"] = "\t\t\tLogTraceReturn(static_cast<unsigned long long>(luaL_checknumber(L, idx)));\n",
	["float"] = "\t\t\tLogTraceReturn(static_cast<float>(luaL_checknumber(L, idx)));\n",
	["double"] = "\t\t\tLogTraceReturn(static_cast<double>(luaL_checknumber(L, idx)));\n",
	["bool"] = "\t\t\tLogTraceReturn(lua_toboolean (L, idx) ? true : false);\n",

	["const char"] = "\t\t\tLogTraceReturn(static_cast<char>(luaL_checkinteger(L, idx)));\n",
	["const signed char"] = "\t\t\tLogTraceReturn(static_cast<signed char>(luaL_checkinteger(L, idx)));\n",
	["const unsigned char"] = "\t\t\tLogTraceReturn(static_cast<unsigned char>(luaL_checkinteger(L, idx)));\n",
	["const short"] = "\t\t\tLogTraceReturn(static_cast<short>(luaL_checkinteger(L, idx)));\n",
	["const unsigned short"] = "\t\t\tLogTraceReturn(static_cast<unsigned short>(luaL_checknumber(L, idx)));\n",
	["const int"] = "\t\t\tLogTraceReturn(static_cast<int>(luaL_checkinteger(L, idx)));\n",
	["const unsigned int"] = "\t\t\tLogTraceReturn(static_cast<unsigned int>(luaL_checknumber(L, idx)));\n",
	["const long"] = "\t\t\tLogTraceReturn(static_cast<long>(luaL_checknumber(L, idx)));\n",
	["const unsigned long"] = "\t\t\tLogTraceReturn(static_cast<unsigned long>(luaL_checknumber(L, idx)));\n",
	["const long long"] = "\t\t\tLogTraceReturn(static_cast<long long>(luaL_checknumber(L, idx)));\n",
	["const unsigned long long"] = "\t\t\tLogTraceReturn(static_cast<unsigned long long>(luaL_checknumber(L, idx)));\n",
	["const float"] = "\t\t\tLogTraceReturn(static_cast<float>(luaL_checknumber(L, idx)));\n",
	["const double"] = "\t\t\tLogTraceReturn(static_cast<double>(luaL_checknumber(L, idx)));\n",
	["const bool"] = "\t\t\tLogTraceReturn(lua_toboolean (L, idx) ? true : false);\n",
}



function create_traits(typeStr)
	local temp = {}
	table.insert(temp, "\t//")
	table.insert(temp, typeStr)
	table.insert(temp, "\n\ttemplate <>\n\tstruct LIGHTINK_TEMPLATE_DECL LuaStack <")
	table.insert(temp, typeStr)
	table.insert(temp, ">\n\t{\n\t\tstatic inline void push(lua_State * L, ")
	table.insert(temp, typeStr)
	table.insert(temp, " value)\n\t\t{\n\t\t\tLogTrace(\"void LuaStack<")
	table.insert(temp, typeStr)
	table.insert(temp, ">::push(lua_State * L, ")
	table.insert(temp, typeStr)
	table.insert(temp, " value)\");\n")
	table.insert(temp, type_str[typeStr])
	table.insert(temp, "\t\t\tLogTraceReturnVoid;\n\t\t}\n\n")

	table.insert(temp, "\t\tstatic inline ")
	table.insert(temp, typeStr)
	table.insert(temp, " get(lua_State * L, int idx)\n\t\t{\n\t\t\tLogTrace(\"")
	table.insert(temp, typeStr)
	table.insert(temp, " LuaStack<")
	table.insert(temp, typeStr)
	table.insert(temp, ">::get(lua_State * L, int idx)\");\n")
	table.insert(temp, check_str[typeStr])
	table.insert(temp, "\t\t}\n\t};\n\n\n")

	print(table.concat(temp))

end

for k, v in pairs(type_str) do
	create_traits(k)
end
*/
	//const long long
	template <>
	struct LIGHTINK_TEMPLATE_DECL LuaStack <const long long>
	{
		static inline void push(lua_State * L, const long long value)
		{
			LogTrace("void LuaStack<const long long>::push(lua_State * L, const long long value)");
			lua_pushnumber(L, static_cast <lua_Number> (value));
			LogTraceReturnVoid;
		}

		static inline const long long get(lua_State * L, int idx)
		{
			LogTrace("const long long LuaStack<const long long>::get(lua_State * L, int idx)");
			LogTraceReturn(static_cast<long long>(luaL_checknumber(L, idx)));
		}
	};



	//const unsigned int
	template <>
	struct LIGHTINK_TEMPLATE_DECL LuaStack <const unsigned int>
	{
		static inline void push(lua_State * L, const unsigned int value)
		{
			LogTrace("void LuaStack<const unsigned int>::push(lua_State * L, const unsigned int value)");
			lua_pushnumber(L, static_cast <lua_Number> (value));
			LogTraceReturnVoid;
		}

		static inline const unsigned int get(lua_State * L, int idx)
		{
			LogTrace("const unsigned int LuaStack<const unsigned int>::get(lua_State * L, int idx)");
			LogTraceReturn(static_cast<unsigned int>(luaL_checknumber(L, idx)));
		}
	};



	//const signed char
	template <>
	struct LIGHTINK_TEMPLATE_DECL LuaStack <const signed char>
	{
		static inline void push(lua_State * L, const signed char value)
		{
			LogTrace("void LuaStack<const signed char>::push(lua_State * L, const signed char value)");
			lua_pushinteger(L, static_cast <lua_Integer> (value));
			LogTraceReturnVoid;
		}

		static inline const signed char get(lua_State * L, int idx)
		{
			LogTrace("const signed char LuaStack<const signed char>::get(lua_State * L, int idx)");
			LogTraceReturn(static_cast<signed char>(luaL_checkinteger(L, idx)));
		}
	};



	//unsigned short
	template <>
	struct LIGHTINK_TEMPLATE_DECL LuaStack <unsigned short>
	{
		static inline void push(lua_State * L, unsigned short value)
		{
			LogTrace("void LuaStack<unsigned short>::push(lua_State * L, unsigned short value)");
			lua_pushnumber(L, static_cast <lua_Number> (value));
			LogTraceReturnVoid;
		}

		static inline unsigned short get(lua_State * L, int idx)
		{
			LogTrace("unsigned short LuaStack<unsigned short>::get(lua_State * L, int idx)");
			LogTraceReturn(static_cast<unsigned short>(luaL_checknumber(L, idx)));
		}
	};



	//long
	template <>
	struct LIGHTINK_TEMPLATE_DECL LuaStack <long>
	{
		static inline void push(lua_State * L, long value)
		{
			LogTrace("void LuaStack<long>::push(lua_State * L, long value)");
			lua_pushnumber(L, static_cast <lua_Number> (value));
			LogTraceReturnVoid;
		}

		static inline long get(lua_State * L, int idx)
		{
			LogTrace("long LuaStack<long>::get(lua_State * L, int idx)");
			LogTraceReturn(static_cast<long>(luaL_checknumber(L, idx)));
		}
	};



	//const bool
	template <>
	struct LIGHTINK_TEMPLATE_DECL LuaStack <const bool>
	{
		static inline void push(lua_State * L, const bool value)
		{
			LogTrace("void LuaStack<const bool>::push(lua_State * L, const bool value)");
			lua_pushboolean(L, value ? 1 : 0);
			LogTraceReturnVoid;
		}

		static inline const bool get(lua_State * L, int idx)
		{
			LogTrace("const bool LuaStack<const bool>::get(lua_State * L, int idx)");
			LogTraceReturn(lua_toboolean (L, idx) ? true : false);
		}
	};



	//int
	template <>
	struct LIGHTINK_TEMPLATE_DECL LuaStack <int>
	{
		static inline void push(lua_State * L, int value)
		{
			LogTrace("void LuaStack<int>::push(lua_State * L, int value)");
			lua_pushinteger(L, static_cast <lua_Integer> (value));
			LogTraceReturnVoid;
		}

		static inline int get(lua_State * L, int idx)
		{
			LogTrace("int LuaStack<int>::get(lua_State * L, int idx)");
			LogTraceReturn(static_cast<int>(luaL_checkinteger(L, idx)));
		}
	};



	//unsigned long long
	template <>
	struct LIGHTINK_TEMPLATE_DECL LuaStack <unsigned long long>
	{
		static inline void push(lua_State * L, unsigned long long value)
		{
			LogTrace("void LuaStack<unsigned long long>::push(lua_State * L, unsigned long long value)");
			lua_pushnumber(L, static_cast <lua_Number> (value));
			LogTraceReturnVoid;
		}

		static inline unsigned long long get(lua_State * L, int idx)
		{
			LogTrace("unsigned long long LuaStack<unsigned long long>::get(lua_State * L, int idx)");
			LogTraceReturn(static_cast<unsigned long long>(luaL_checknumber(L, idx)));
		}
	};



	//float
	template <>
	struct LIGHTINK_TEMPLATE_DECL LuaStack <float>
	{
		static inline void push(lua_State * L, float value)
		{
			LogTrace("void LuaStack<float>::push(lua_State * L, float value)");
			lua_pushnumber(L, static_cast <lua_Number> (value));
			LogTraceReturnVoid;
		}

		static inline float get(lua_State * L, int idx)
		{
			LogTrace("float LuaStack<float>::get(lua_State * L, int idx)");
			LogTraceReturn(static_cast<float>(luaL_checknumber(L, idx)));
		}
	};



	//const short
	template <>
	struct LIGHTINK_TEMPLATE_DECL LuaStack <const short>
	{
		static inline void push(lua_State * L, const short value)
		{
			LogTrace("void LuaStack<const short>::push(lua_State * L, const short value)");
			lua_pushinteger(L, static_cast <lua_Integer> (value));
			LogTraceReturnVoid;
		}

		static inline const short get(lua_State * L, int idx)
		{
			LogTrace("const short LuaStack<const short>::get(lua_State * L, int idx)");
			LogTraceReturn(static_cast<short>(luaL_checkinteger(L, idx)));
		}
	};



	//unsigned int
	template <>
	struct LIGHTINK_TEMPLATE_DECL LuaStack <unsigned int>
	{
		static inline void push(lua_State * L, unsigned int value)
		{
			LogTrace("void LuaStack<unsigned int>::push(lua_State * L, unsigned int value)");
			lua_pushnumber(L, static_cast <lua_Number> (value));
			LogTraceReturnVoid;
		}

		static inline unsigned int get(lua_State * L, int idx)
		{
			LogTrace("unsigned int LuaStack<unsigned int>::get(lua_State * L, int idx)");
			LogTraceReturn(static_cast<unsigned int>(luaL_checknumber(L, idx)));
		}
	};



	//const char
	template <>
	struct LIGHTINK_TEMPLATE_DECL LuaStack <const char>
	{
		static inline void push(lua_State * L, const char value)
		{
			LogTrace("void LuaStack<const char>::push(lua_State * L, const char value)");
			lua_pushinteger(L, static_cast <lua_Integer> (value));
			LogTraceReturnVoid;
		}

		static inline const char get(lua_State * L, int idx)
		{
			LogTrace("const char LuaStack<const char>::get(lua_State * L, int idx)");
			LogTraceReturn(static_cast<char>(luaL_checkinteger(L, idx)));
		}
	};



	//bool
	template <>
	struct LIGHTINK_TEMPLATE_DECL LuaStack <bool>
	{
		static inline void push(lua_State * L, bool value)
		{
			LogTrace("void LuaStack<bool>::push(lua_State * L, bool value)");
			lua_pushboolean(L, value ? 1 : 0);
			LogTraceReturnVoid;
		}

		static inline bool get(lua_State * L, int idx)
		{
			LogTrace("bool LuaStack<bool>::get(lua_State * L, int idx)");
			LogTraceReturn(lua_toboolean (L, idx) ? true : false);
		}
	};



	//const float
	template <>
	struct LIGHTINK_TEMPLATE_DECL LuaStack <const float>
	{
		static inline void push(lua_State * L, const float value)
		{
			LogTrace("void LuaStack<const float>::push(lua_State * L, const float value)");
			lua_pushnumber(L, static_cast <lua_Number> (value));
			LogTraceReturnVoid;
		}

		static inline const float get(lua_State * L, int idx)
		{
			LogTrace("const float LuaStack<const float>::get(lua_State * L, int idx)");
			LogTraceReturn(static_cast<float>(luaL_checknumber(L, idx)));
		}
	};



	//const unsigned long
	template <>
	struct LIGHTINK_TEMPLATE_DECL LuaStack <const unsigned long>
	{
		static inline void push(lua_State * L, const unsigned long value)
		{
			LogTrace("void LuaStack<const unsigned long>::push(lua_State * L, const unsigned long value)");
			lua_pushnumber(L, static_cast <lua_Number> (value));
			LogTraceReturnVoid;
		}

		static inline const unsigned long get(lua_State * L, int idx)
		{
			LogTrace("const unsigned long LuaStack<const unsigned long>::get(lua_State * L, int idx)");
			LogTraceReturn(static_cast<unsigned long>(luaL_checknumber(L, idx)));
		}
	};



	//const unsigned long long
	template <>
	struct LIGHTINK_TEMPLATE_DECL LuaStack <const unsigned long long>
	{
		static inline void push(lua_State * L, const unsigned long long value)
		{
			LogTrace("void LuaStack<const unsigned long long>::push(lua_State * L, const unsigned long long value)");
			lua_pushnumber(L, static_cast <lua_Number> (value));
			LogTraceReturnVoid;
		}

		static inline const unsigned long long get(lua_State * L, int idx)
		{
			LogTrace("const unsigned long long LuaStack<const unsigned long long>::get(lua_State * L, int idx)");
			LogTraceReturn(static_cast<unsigned long long>(luaL_checknumber(L, idx)));
		}
	};



	//short
	template <>
	struct LIGHTINK_TEMPLATE_DECL LuaStack <short>
	{
		static inline void push(lua_State * L, short value)
		{
			LogTrace("void LuaStack<short>::push(lua_State * L, short value)");
			lua_pushinteger(L, static_cast <lua_Integer> (value));
			LogTraceReturnVoid;
		}

		static inline short get(lua_State * L, int idx)
		{
			LogTrace("short LuaStack<short>::get(lua_State * L, int idx)");
			LogTraceReturn(static_cast<short>(luaL_checkinteger(L, idx)));
		}
	};



	//unsigned char
	template <>
	struct LIGHTINK_TEMPLATE_DECL LuaStack <unsigned char>
	{
		static inline void push(lua_State * L, unsigned char value)
		{
			LogTrace("void LuaStack<unsigned char>::push(lua_State * L, unsigned char value)");
			lua_pushinteger(L, static_cast <lua_Integer> (value));
			LogTraceReturnVoid;
		}

		static inline unsigned char get(lua_State * L, int idx)
		{
			LogTrace("unsigned char LuaStack<unsigned char>::get(lua_State * L, int idx)");
			LogTraceReturn(static_cast<unsigned char>(luaL_checkinteger(L, idx)));
		}
	};



	//const int
	template <>
	struct LIGHTINK_TEMPLATE_DECL LuaStack <const int>
	{
		static inline void push(lua_State * L, const int value)
		{
			LogTrace("void LuaStack<const int>::push(lua_State * L, const int value)");
			lua_pushinteger(L, static_cast <lua_Integer> (value));
			LogTraceReturnVoid;
		}

		static inline const int get(lua_State * L, int idx)
		{
			LogTrace("const int LuaStack<const int>::get(lua_State * L, int idx)");
			LogTraceReturn(static_cast<int>(luaL_checkinteger(L, idx)));
		}
	};



	//const long
	template <>
	struct LIGHTINK_TEMPLATE_DECL LuaStack <const long>
	{
		static inline void push(lua_State * L, const long value)
		{
			LogTrace("void LuaStack<const long>::push(lua_State * L, const long value)");
			lua_pushnumber(L, static_cast <lua_Number> (value));
			LogTraceReturnVoid;
		}

		static inline const long get(lua_State * L, int idx)
		{
			LogTrace("const long LuaStack<const long>::get(lua_State * L, int idx)");
			LogTraceReturn(static_cast<long>(luaL_checknumber(L, idx)));
		}
	};



	//char
	template <>
	struct LIGHTINK_TEMPLATE_DECL LuaStack <char>
	{
		static inline void push(lua_State * L, char value)
		{
			LogTrace("void LuaStack<char>::push(lua_State * L, char value)");
			lua_pushinteger(L, static_cast <lua_Integer> (value));
			LogTraceReturnVoid;
		}

		static inline char get(lua_State * L, int idx)
		{
			LogTrace("char LuaStack<char>::get(lua_State * L, int idx)");
			LogTraceReturn(static_cast<char>(luaL_checkinteger(L, idx)));
		}
	};



	//unsigned long
	template <>
	struct LIGHTINK_TEMPLATE_DECL LuaStack <unsigned long>
	{
		static inline void push(lua_State * L, unsigned long value)
		{
			LogTrace("void LuaStack<unsigned long>::push(lua_State * L, unsigned long value)");
			lua_pushnumber(L, static_cast <lua_Number> (value));
			LogTraceReturnVoid;
		}

		static inline unsigned long get(lua_State * L, int idx)
		{
			LogTrace("unsigned long LuaStack<unsigned long>::get(lua_State * L, int idx)");
			LogTraceReturn(static_cast<unsigned long>(luaL_checknumber(L, idx)));
		}
	};



	//signed char
	template <>
	struct LIGHTINK_TEMPLATE_DECL LuaStack <signed char>
	{
		static inline void push(lua_State * L, signed char value)
		{
			LogTrace("void LuaStack<signed char>::push(lua_State * L, signed char value)");
			lua_pushinteger(L, static_cast <lua_Integer> (value));
			LogTraceReturnVoid;
		}

		static inline signed char get(lua_State * L, int idx)
		{
			LogTrace("signed char LuaStack<signed char>::get(lua_State * L, int idx)");
			LogTraceReturn(static_cast<signed char>(luaL_checkinteger(L, idx)));
		}
	};



	//const unsigned short
	template <>
	struct LIGHTINK_TEMPLATE_DECL LuaStack <const unsigned short>
	{
		static inline void push(lua_State * L, const unsigned short value)
		{
			LogTrace("void LuaStack<const unsigned short>::push(lua_State * L, const unsigned short value)");
			lua_pushnumber(L, static_cast <lua_Number> (value));
			LogTraceReturnVoid;
		}

		static inline const unsigned short get(lua_State * L, int idx)
		{
			LogTrace("const unsigned short LuaStack<const unsigned short>::get(lua_State * L, int idx)");
			LogTraceReturn(static_cast<unsigned short>(luaL_checknumber(L, idx)));
		}
	};



	//long long
	template <>
	struct LIGHTINK_TEMPLATE_DECL LuaStack <long long>
	{
		static inline void push(lua_State * L, long long value)
		{
			LogTrace("void LuaStack<long long>::push(lua_State * L, long long value)");
			lua_pushnumber(L, static_cast <lua_Number> (value));
			LogTraceReturnVoid;
		}

		static inline long long get(lua_State * L, int idx)
		{
			LogTrace("long long LuaStack<long long>::get(lua_State * L, int idx)");
			LogTraceReturn(static_cast<long long>(luaL_checknumber(L, idx)));
		}
	};



	//const unsigned char
	template <>
	struct LIGHTINK_TEMPLATE_DECL LuaStack <const unsigned char>
	{
		static inline void push(lua_State * L, const unsigned char value)
		{
			LogTrace("void LuaStack<const unsigned char>::push(lua_State * L, const unsigned char value)");
			lua_pushinteger(L, static_cast <lua_Integer> (value));
			LogTraceReturnVoid;
		}

		static inline const unsigned char get(lua_State * L, int idx)
		{
			LogTrace("const unsigned char LuaStack<const unsigned char>::get(lua_State * L, int idx)");
			LogTraceReturn(static_cast<unsigned char>(luaL_checkinteger(L, idx)));
		}
	};



	//double
	template <>
	struct LIGHTINK_TEMPLATE_DECL LuaStack <double>
	{
		static inline void push(lua_State * L, double value)
		{
			LogTrace("void LuaStack<double>::push(lua_State * L, double value)");
			lua_pushnumber(L, static_cast <lua_Number> (value));
			LogTraceReturnVoid;
		}

		static inline double get(lua_State * L, int idx)
		{
			LogTrace("double LuaStack<double>::get(lua_State * L, int idx)");
			LogTraceReturn(static_cast<double>(luaL_checknumber(L, idx)));
		}
	};



	//const double
	template <>
	struct LIGHTINK_TEMPLATE_DECL LuaStack <const double>
	{
		static inline void push(lua_State * L, const double value)
		{
			LogTrace("void LuaStack<const double>::push(lua_State * L, const double value)");
			lua_pushnumber(L, static_cast <lua_Number> (value));
			LogTraceReturnVoid;
		}

		static inline const double get(lua_State * L, int idx)
		{
			LogTrace("const double LuaStack<const double>::get(lua_State * L, int idx)");
			LogTraceReturn(static_cast<double>(luaL_checknumber(L, idx)));
		}
	};


	//Push a lua_CFunction.
	template <>
	struct LIGHTINK_TEMPLATE_DECL LuaStack <lua_CFunction>
	{
		static inline void push(lua_State * L, lua_CFunction f)
		{
			LogTrace("void LuaStack<lua_CFunction>::push(lua_State * L, lua_CFunction f)");
			lua_pushcfunction (L, f);
			LogTraceReturnVoid;
		}

		static inline lua_CFunction get(lua_State * L, int idx)
		{
			LogTrace("lua_CFunction LuaStack<lua_CFunction>::get(lua_State * L, int idx)");
			LogTraceReturn(lua_tocfunction (L, idx));
		}
	};

	//RuntimeError
	template <>
	struct LIGHTINK_TEMPLATE_DECL LuaStack <RuntimeError>
	{
		static inline void push(lua_State * L, RuntimeError e)
		{
			LogTrace("void LuaStack<int>::push(lua_State * L, RuntimeError e)");
			lua_pushinteger(L, static_cast <lua_Integer> (e));
			LogTraceReturnVoid;
		}

		static inline RuntimeError get(lua_State * L, int idx)
		{
			LogTrace("int LuaStack<int>::get(lua_State * L, int idx)");
			LogTraceReturn(static_cast<RuntimeError>(luaL_checkinteger(L, idx)));
		}
	};

	//const RuntimeError
	template <>
	struct LIGHTINK_TEMPLATE_DECL LuaStack <const RuntimeError>
	{
		static inline void push(lua_State * L, const RuntimeError e)
		{
			LogTrace("void LuaStack<int>::push(lua_State * L, RuntimeError e)");
			lua_pushinteger(L, static_cast <lua_Integer> (e));
			LogTraceReturnVoid;
		}

		static inline RuntimeError get(lua_State * L, int idx)
		{
			LogTrace("int LuaStack<int>::get(lua_State * L, int idx)");
			LogTraceReturn(static_cast<RuntimeError>(luaL_checkinteger(L, idx)));
		}
	};

	//nil
	template <>
	struct LIGHTINK_TEMPLATE_DECL LuaStack <LuaTypeNil>
	{
		static inline void push(lua_State * L, LuaTypeNil)
		{
			LogTrace("void LuaStack<LuaTypeNil>::push(lua_State * L, LuaTypeNil)");
			lua_pushnil (L);
			LogTraceReturnVoid;
		}

		static inline LuaTypeNil get(lua_State * L, int idx)
		{
			LogTrace("LuaTypeNil LuaStack<LuaTypeNil>::get(lua_State * L, int idx)");
			LogTraceReturn(LuaTypeNil());
		}
	};

	//const char *
	template <>
	struct LIGHTINK_TEMPLATE_DECL LuaStack <const char * const>
	{
		static inline void push(lua_State * L, const char * str)
		{
			LogTrace("void LuaStack<const char *>::push(lua_State * L, const char * str)");
			if (str)
			{
				lua_pushstring(L, str);
			}
			else
			{
				lua_pushnil(L);
			}
			LogTraceReturnVoid;
		}

		static inline const char * get(lua_State * L, int idx)
		{
			LogTrace("const char * LuaStack<const char *>::get(lua_State * L, int idx)");
			LogTraceReturn((lua_isnil(L, idx) ? NULL : luaL_checkstring(L, idx)));
		}
	};

	//const char[size]
	template <int size>
	struct LIGHTINK_TEMPLATE_DECL LuaStack <const char [size]>
	{
		static inline void push(lua_State * L, const char str[size])
		{
			LogTrace("void LuaStack<const char *>::push(lua_State * L, const char str[size])");
			if (str)
			{
				lua_pushstring(L, str);
			}
			else
			{
				lua_pushnil(L);
			}
			LogTraceReturnVoid;
		}

		static inline const char * get(lua_State * L, int idx)
		{
			LogTrace("const char * LuaStack<const char *>::get(lua_State * L, int idx)");
			LogTraceReturn((lua_isnil(L, idx) ? NULL : luaL_checkstring(L, idx)));
		}
	};

	//char[size]
	template <int size>
	struct LIGHTINK_TEMPLATE_DECL LuaStack <char [size]>
	{
		static inline void push(lua_State * L, char str[size])
		{
			LogTrace("void LuaStack<const char *>::push(lua_State * L, char str[size])");
			if (str)
			{
				lua_pushstring(L, str);
			}
			else
			{
				lua_pushnil(L);
			}
			LogTraceReturnVoid;
		}

		static inline const char * get(lua_State * L, int idx)
		{
			LogTrace("const char * LuaStack<const char *>::get(lua_State * L, int idx)");
			LogTraceReturn((lua_isnil(L, idx) ? NULL : luaL_checkstring(L, idx)));
		}
	};

	//char *
	template <>
	struct LIGHTINK_TEMPLATE_DECL LuaStack <char *>
	{
		static inline void push(lua_State * L, char * str)
		{
			LogTrace("void LuaStack<char *>::push(lua_State * L, char * str)");
			if (str)
			{
				lua_pushstring(L, str);
			}
			else
			{
				lua_pushnil(L);
			}
			LogTraceReturnVoid;
		}

		static inline const char * get(lua_State * L, int idx)
		{
			LogTrace("const char * LuaStack<char *>::get(lua_State * L, int idx)");
			LogTraceReturn((lua_isnil(L, idx) ? NULL : luaL_checkstring(L, idx)));
		}
	};


	//CharPtrBridge
	template <>
	struct LIGHTINK_TEMPLATE_DECL LuaStack <CharPtrBridge>
	{
		static inline void push(lua_State * L, CharPtrBridge & str)
		{
			LogTrace("void LuaStack<CharPtrBridge>::push(lua_State * L, CharPtrBridge & str)");
			lua_pushlstring (L, str.m_charPtr, str.m_len);
			LogTraceReturnVoid;
		}

		static inline CharPtrBridge get(lua_State * L, int idx)
		{
			LogTrace("CharPtrBridge LuaStack<CharPtrBridge>::get(lua_State * L, int idx)");
			size_t len = 0;
			const char * str = luaL_checklstring(L, idx, &len);
			LogTraceReturn(CharPtrBridge(str, len));
		}
	};

	//const CharPtrBridge
	template <>
	struct LIGHTINK_TEMPLATE_DECL LuaStack <const CharPtrBridge>
	{
		static inline void push(lua_State * L, const CharPtrBridge & str)
		{
			LogTrace("void LuaStack<const CharPtrBridge>::push(lua_State * L, const CharPtrBridge & str)");
			lua_pushlstring (L, str.m_charPtr, str.m_len);
			LogTraceReturnVoid;
		}

		static inline CharPtrBridge get(lua_State * L, int idx)
		{
			LogTrace("CharPtrBridge LuaStack<const CharPtrBridge &>::get(lua_State * L, int idx)");
			size_t len = 0;
			const char * str = luaL_checklstring(L, idx, &len);
			LogTraceReturn(CharPtrBridge(str, len));
		}
	};

	//const CharPtrBridge &
	template <>
	struct LIGHTINK_TEMPLATE_DECL LuaStack <const CharPtrBridge &>
	{
		static inline void push(lua_State * L, const CharPtrBridge & str)
		{
			LogTrace("void LuaStack<const CharPtrBridge &>::push(lua_State * L, const CharPtrBridge & str)");
			lua_pushlstring (L, str.m_charPtr, str.m_len);
			LogTraceReturnVoid;
		}

		static inline CharPtrBridge get(lua_State * L, int idx)
		{
			LogTrace("CharPtrBridge LuaStack<const CharPtrBridge &>::get(lua_State * L, int idx)");
			size_t len = 0;
			const char * str = luaL_checklstring(L, idx, &len);
			LogTraceReturn(CharPtrBridge(str, len));
		}
	};

	//string
	template <>
	struct LIGHTINK_TEMPLATE_DECL LuaStack <std::string>
	{
		static inline void push(lua_State * L, std::string & str)
		{
			LogTrace("void LuaStack<string>::push(lua_State * L, const string & str)");
			lua_pushlstring (L, str.c_str (), str.size());
			LogTraceReturnVoid;
		}

		static inline std::string get(lua_State * L, int idx)
		{
			LogTrace("std::string LuaStack<string>::get(lua_State * L, int idx)");
			size_t len = 0;
			const char * str = luaL_checklstring(L, idx, &len);
			LogTraceReturn(std::string(str, len));
		}
	};

	//const string
	template <>
	struct LIGHTINK_TEMPLATE_DECL LuaStack <const std::string>
	{
		static inline void push(lua_State * L, const std::string & str)
		{
			LogTrace("void LuaStack<const string>::push(lua_State * L, const std::string & str)");
			lua_pushlstring (L, str.c_str (), str.size());
			LogTraceReturnVoid;
		}

		static inline std::string get(lua_State * L, int idx)
		{
			LogTrace("std::string LuaStack<const string &>::get(lua_State * L, int idx)");
			size_t len = 0;
			const char * str = luaL_checklstring(L, idx, &len);
			LogTraceReturn(std::string(str, len));
		}
	};

	//const string &
	template <>
	struct LIGHTINK_TEMPLATE_DECL LuaStack <const std::string &>
	{
		static inline void push(lua_State * L, const std::string & str)
		{
			LogTrace("void LuaStack<const string &>::push(lua_State * L, const std::string & str)");
			lua_pushlstring (L, str.c_str (), str.size());
			LogTraceReturnVoid;
		}

		static inline std::string get(lua_State * L, int idx)
		{
			LogTrace("string LuaStack<const string &>::get(lua_State * L, int idx)");
			size_t len = 0;
			const char * str = luaL_checklstring(L, idx, &len);
			LogTraceReturn(std::string(str, len));
		}
	};

	//vector
	template <typename T>
	struct LIGHTINK_TEMPLATE_DECL LuaStack <std::vector<T> >
	{
		static inline void push(lua_State * L, typename std::vector<T> & vec)
		{
			LogTrace("void LuaStack<std::vector<T>>::push(lua_State * L, const std::vector<T> & vec)");
			lua_createtable(L, vec.size(), 0);
			for (size_t i = 0; i < vec.size(); ++i)
			{
				LuaStack<const T>::push(L, vec[i]);
				lua_rawseti(L, -2, i+1);
			}
			LogTraceReturnVoid;
		}

		static inline typename std::vector<T> get(lua_State * L, int idx)
		{
			LogTrace("std::vector<T> LuaStack<std::vector<T>>::get(lua_State * L, int idx)");
			if (!lua_istable(L, idx))
			{
				LogScriptErrorJump(L, "Error!!!The %d data is not a table, convert vector failed!!!", idx);
			}
			typename std::vector<T> vec;
			idx = lua_absindex(L, idx);
			size_t len = lua_objlen(L, idx);
			for (size_t i = 1; i <= len; i++)
			{
				lua_rawgeti(L, idx, i);
				vec.push_back(LuaStack<const T>::get(L, -1));
				lua_pop(L, 1);
			}
			LogTraceReturn(vec);
		}
	};

	//const vector
	template <typename T>
	struct LIGHTINK_TEMPLATE_DECL LuaStack <const std::vector<T> >
	{
		static inline void push(lua_State * L, const typename std::vector<T> & vec)
		{
			LogTrace("void LuaStack<const std::vector<T>>::push(lua_State * L, const std::vector<T> & const vec)");
			lua_createtable(L, vec.size(), 0);
			for (size_t i = 0; i < vec.size(); ++i)
			{
				LuaStack<const T>::push(L, vec[i]);
				lua_rawseti(L, -2, i+1);
			}
			LogTraceReturnVoid;
		}

		static inline typename std::vector<T> get(lua_State * L, int idx)
		{
			LogTrace("std::vector<T> LuaStack<const std::vector<T> &>::get(lua_State * L, int idx)");
			if (!lua_istable(L, idx))
			{
				LogScriptErrorJump(L, "Error!!!The %d data is not a table, convert vector failed!!!", idx);
			}
			typename std::vector<T> vec;
			idx = lua_absindex(L, idx);
			size_t len = lua_objlen(L, idx);
			for (size_t i = 1; i <= len; i++)
			{
				lua_rawgeti(L, idx, i);
				vec.push_back(LuaStack<const T>::get(L, -1));
				lua_pop(L, 1);
			}
			LogTraceReturn(vec);
		}
	};

	//const vector &
	template <typename T>
	struct LIGHTINK_TEMPLATE_DECL LuaStack <const std::vector<T> &>
	{
		static inline void push(lua_State * L, const typename std::vector<T> & vec)
		{
			LogTrace("void LuaStack<const std::vector<T> &>::push(lua_State * L, const std::vector<T> & vec)");
			lua_createtable(L, vec.size(), 0);
			for (size_t i = 0; i < vec.size(); ++i)
			{
				LuaStack<const T>::push(L, vec[i]);
				lua_rawseti(L, -2, i+1);
			}
			LogTraceReturnVoid;
		}

		static inline typename std::vector<T> get(lua_State * L, int idx)
		{
			LogTrace("std::vector<T> LuaStack<const std::vector<T> &>::get(lua_State * L, int idx)");
			if (!lua_istable(L, idx))
			{
				LogScriptErrorJump(L, "Error!!!The %d data is not a table, convert vector failed!!!", idx);
			}
			typename std::vector<T> vec;
			idx = lua_absindex(L, idx);
			size_t len = lua_objlen(L, idx);
			for (size_t i = 1; i <= len; i++)
			{
				lua_rawgeti(L, idx, i);
				vec.push_back(LuaStack<const T>::get(L, -1));
				lua_pop(L, 1);
			}
			LogTraceReturn(vec);
		}
	};



	//map
	template <typename K, typename V>
	struct LIGHTINK_TEMPLATE_DECL LuaStack <std::map<K, V> >
	{
		static inline void push(lua_State * L, typename std::map<K, V> & m)
		{
			LogTrace("void LuaStack<std::map<K, V>>::push(lua_State * L, const std::map<K, V> & m)");
			lua_createtable(L, 0, m.size());
			for (typename std::map<K, V>::iterator iter = m.begin(); iter != m.end(); ++iter)
			{
				LuaStack<const K>::push(L, iter->first);
				LuaStack<const V>::push(L, iter->second);
				lua_rawset(L, -3);
			}
			LogTraceReturnVoid;
		}

		static inline typename std::map<K, V> get(lua_State * L, int idx)
		{
			LogTrace("std::map<K, V> LuaStack<map<K, V>>::get(lua_State * L, int idx)");
			if (!lua_istable(L, idx))
			{
				LogScriptErrorJump(L, "Error!!!The %d data is not a table, convert map failed!!!", idx);
			}
			typename std::map<K, V> m;
			idx = lua_absindex(L, idx);

			lua_pushnil(L);
			while (lua_next(L, idx))
			{
				K key = LuaStack<const K>::get(L, -2);
				V val = LuaStack<const V>::get(L, -1);
				m.insert(std::map<K, V>::value_type(key, val));
				lua_pop(L, 1);
			}
			LogTraceReturn(m);
		}
	};

	//const map &
	template <typename K, typename V>
	struct LIGHTINK_TEMPLATE_DECL LuaStack <const std::map<K, V> >
	{
		static inline void push(lua_State * L, const typename std::map<K, V> & m)
		{
			LogTrace("void LuaStack<const std::map<K, V> &>::push(lua_State * L, const std::map<K, V> & m)");
			lua_createtable(L, 0, m.size());
			for (typename std::map<K, V>::iterator iter = m.begin(); iter != m.end(); ++iter)
			{
				LuaStack<const K>::push(L, iter->first);
				LuaStack<const V>::push(L, iter->second);
				lua_rawset(L, -3);
			}
			LogTraceReturnVoid;
		}

		static inline typename std::map<K, V> get(lua_State * L, int idx)
		{
			LogTrace("std::map<K, V> LuaStack<const std::map<K, V> &>::get(lua_State * L, int idx)");
			if (!lua_istable(L, idx))
			{
				LogScriptErrorJump(L, "Error!!!The %d data is not a table, convert map failed!!!", idx);
			}
			typename std::map<K, V> m;
			idx = lua_absindex(L, idx);

			lua_pushnil(L);
			while (lua_next(L, idx))
			{
				K key = LuaStack<const K>::get(L, -2);
				V val = LuaStack<const V>::get(L, -1);
				m.insert(std::map<K, V>::value_type(key, val));
				lua_pop(L, 1);
			}
			LogTraceReturn(m);
		}
	};


	//set
	template <typename T>
	struct LIGHTINK_TEMPLATE_DECL LuaStack <std::set<T> >
	{
		static inline void push(lua_State * L, typename std::set<T> & s)
		{
			LogTrace("void LuaStack<std::set<T>>::push(lua_State * L, const std::set<T> & s)");
			lua_createtable(L, 0, s.size());
			for (typename std::set<T>::iterator iter = s.begin(); iter != s.end(); ++iter)
			{
				LuaStack<const T>::push(L, *iter);
				LuaStack<bool>::push(L, true);
				lua_rawset(L, -3);
			}
			LogTraceReturnVoid;
		}

		static inline typename std::set<T> get(lua_State * L, int idx)
		{
			LogTrace("std::set<T> LuaStack<std::set<T> >::get(lua_State * L, int idx)");
			if (!lua_istable(L, idx))
			{
				LogScriptErrorJump(L, "Error!!!The %d data is not a table, convert set failed!!!", idx);
			}
			typename std::set<T> s;
			idx = lua_absindex(L, idx);

			lua_pushnil(L);
			while (lua_next(L, idx))
			{
				T key = LuaStack<const T>::get(L, -2);
				s.insert(key);
				lua_pop(L, 1);
			}
			LogTraceReturn(s);
		}
	};

	//const set &
	template <typename T>
	struct LIGHTINK_TEMPLATE_DECL LuaStack <const std::set<T> >
	{
		static inline void push(lua_State * L, const typename std::set<T> & s)
		{
			LogTrace("void LuaStack<const std::set<T> &>::push(lua_State * L, const std::set<T> & s)");
			lua_createtable(L, 0, s.size());
			for (typename std::set<T>::iterator iter = s.begin(); iter != s.end(); ++iter)
			{
				LuaStack<const T>::push(L, *iter);
				LuaStack<bool>::push(L, true);
				lua_rawset(L, -3);
			}
			LogTraceReturnVoid;
		}

		static inline typename std::set<T> get(lua_State * L, int idx)
		{
			LogTrace("std::set<T> LuaStack<const std::set<T> &>::get(lua_State * L, int idx)");
			if (!lua_istable(L, idx))
			{
				LogScriptErrorJump(L, "Error!!!The %d data is not a table, convert set failed!!!", idx);
			}
			typename std::set<T> s;
			idx = lua_absindex(L, idx);

			lua_pushnil(L);
			while (lua_next(L, idx))
			{
				T key = LuaStack<const T>::get(L, -2);
				s.insert(key);
				lua_pop(L, 1);
			}
			LogTraceReturn(s);
		}
	};


	//SharedPtr template<T> can use this type!!!!
	/*
	template <typename T>
	struct LIGHTINK_TEMPLATE_DECL LuaStack <SharedPtr<T> >
	{
		static inline void push(lua_State* L, typename SharedPtr<T>::type & sp)
		{
			LogTrace("void LuaStack<SharedPtr<T>>::push(lua_State* L, const typename SharedPtr<T>::type & sp)");
			LuaUserdata::push<const SharedPtr<T>::type>(L, sp);
			LogTraceReturnVoid;
		}

		static inline typename SharedPtr<T>::type get (lua_State * L, int idx)
		{
			LogTrace("SharedPtr<T>::type LuaStack<SharedPtr<T>>::get(lua_State * L, int idx)");
			LogTraceReturn(LuaUserdata::get<const SharedPtr<T>::type>(L, idx));
		}
	};
	*/

	//SharedPtrTS template<T> can use this type!!!!
	/*
	template <typename T>
	struct LIGHTINK_TEMPLATE_DECL LuaStack <SharedPtrTS<T> >
	{
		static inline void push(lua_State* L, typename SharedPtrTS<T>::type & sp)
		{
			LogTrace("void LuaStack<SharedPtrTS<T>>::push(lua_State* L, const typename SharedPtrTS<T>::type & sp)");
			LuaUserdata::push<const SharedPtrTS<T>::type>(L, sp);
			LogTraceReturnVoid;
		}

		static inline typename SharedPtrTS<T>::type get (lua_State * L, int idx)
		{
			LogTrace("SharedPtrTS<T>::type LuaStack<SharedPtrTS<T>>::get(lua_State * L, int idx)");
			LogTraceReturn(LuaUserdata::get<const SharedPtrTS<T>::type>(L, idx));
		}
	};
	*/


	// pointer
	template <typename T>
	struct LIGHTINK_TEMPLATE_DECL LuaStack <T * const>
	{
		static inline void push(lua_State* L, T * const p)
		{
			LogTrace("void LuaStack<T *>::push(lua_State * L, T * const p)");
			LuaUserdataPtr::push<T>(L, p);
			LogTraceReturnVoid;
		}

		static inline T * get (lua_State * L, int idx)
		{
			LogTrace("T * LuaStack<T *>::get(lua_State * L, int idx)");
			LogTraceReturn(LuaUserdataPtr::get<T> (L, idx));
		}
	};

	//const pointer
	template <typename T>
	struct LIGHTINK_TEMPLATE_DECL LuaStack <const T * const>
	{
		static inline void push(lua_State* L, const T * const p)
		{
			LogTrace("void LuaStack<T *>::push(lua_State * L, T * const p)");
			LuaUserdataPtr::push<T>(L, p);
			LogTraceReturnVoid;
		}

		static inline T * get (lua_State * L, int idx)
		{
			LogTrace("T * LuaStack<T *>::get(lua_State * L, int idx)");
			LogTraceReturn(LuaUserdataPtr::get<T> (L, idx));
		}
	};

	// Lua stack conversions for const class objects passed by value.
	template <typename T>
	struct LIGHTINK_TEMPLATE_DECL LuaStack<const T>
	{
		static inline void push(lua_State * L, const T & t)
		{
			LogTrace("void LuaStack<T>::push(lua_State * L, const T & t)");
			LuaUserdata::push<T>(L, t);
			LogTraceReturnVoid;
		}

		static inline typename GetType<T>::type get(lua_State * L, int idx)
		{
			LogTrace("T LuaStack<T>::get(lua_State * L, int idx)");
			LogTraceReturn(LuaUserdata::get <typename GetType<T>::type> (L, idx));
		}
	};

	// Lua stack conversions for class objects passed by value.
	template <typename T>
	struct LIGHTINK_TEMPLATE_DECL LuaStack
	{
		static inline void push(lua_State * L, const T & t)
		{
			LogTrace("void LuaStack<T>::push(lua_State * L, const T & t)");
			LuaUserdata::push<T>(L, t);
			LogTraceReturnVoid;
		}

		static inline typename GetType<T>::type get(lua_State * L, int idx)
		{
			LogTrace("T LuaStack<T>::get(lua_State * L, int idx)");
			LogTraceReturn(LuaUserdata::get <typename GetType<T>::type> (L, idx));
		}
	};

}


#endif