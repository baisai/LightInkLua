


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

#include <math.h>
#include "Common/Log.h"
#include "LuaEngine/LuaInt64.h"

namespace LightInk
{
	//////////////////////////////////////////////////////////
	//LuaInt64
	/////////////////////////////////////////////////////////
	LuaInt64::LuaInt64(lua_Number number) : m_number(static_cast<int64>(number))
	{
		LogTrace("LuaInt64::LuaInt64(lua_Number number)");
		LogTraceReturnVoid;
	}

	LuaInt64::LuaInt64(int64 number) : m_number(number)
	{
		LogTrace("LuaInt64::LuaInt64(int64 number)");
		LogTraceReturnVoid;
	}

	LuaInt64 LuaInt64::new_from_string(CharPtrBridge number)
	{
		LogTrace("LuaInt64 LuaInt64::new_from_string(CharPtrBridge number)");
		int64 num = strtoll(number.m_charPtr, NULL, 10);
		LogTraceReturn(LuaInt64(num));
	}
	LuaInt64 LuaInt64::new_from_st(const LuaInt64 & number)
	{
		LogTrace("LuaInt64 LuaInt64::new_from_st(const LuaInt64 & number)");
		LogTraceReturn(LuaInt64(number.m_number));
	}

	const std::string LuaInt64::to_string()
	{
		LogTrace("const std::string LuaInt64::to_string()");
		char num[32] = { 0 };
		snprintf(num, 32, "%lld", m_number);
		LogTraceReturn(std::string(num));
	}
	lua_Number LuaInt64::to_number()
	{
		LogTrace("lua_Number LuaInt64::to_number()");
		LogTraceReturn(static_cast<lua_Number>(m_number));
	}
	LuaUint64 LuaInt64::to_uint64()
	{
		LogTrace("LuaUint64 LuaInt64::to_uint64()");
		LogTraceReturn(LuaUint64(static_cast<uint64>(m_number)));
	}

	void LuaInt64::set_number(lua_Number number)
	{
		LogTrace("void LuaInt64::set_number(lua_Number number)");
		m_number = static_cast<int64>(number);
		LogTraceReturnVoid;
	}
	void LuaInt64::set_string(const CharPtrBridge number)
	{
		LogTrace("void LuaInt64::set_string(const CharPtrBridge number)");
		m_number = strtoll(number.m_charPtr, NULL, 10);
		LogTraceReturnVoid;
	}
	void LuaInt64::set_st(const LuaInt64 & number)
	{
		LogTrace("void LuaInt64::set_st(const LuaInt64 & number)");
		m_number = number.m_number;
		LogTraceReturnVoid;
	}

	LuaInt64 LuaInt64::add_number(lua_Number number)
	{
		LogTrace("LuaInt64 LuaInt64::add_number(lua_Number number)");
		LogTraceReturn(LuaInt64(m_number + static_cast<int64>(number)));
	}
	LuaInt64 LuaInt64::sub_number(lua_Number number)
	{
		LogTrace("LuaInt64 LuaInt64::sub_number(lua_Number number)");
		LogTraceReturn(LuaInt64(m_number - static_cast<int64>(number)));
	}
	LuaInt64 LuaInt64::mul_number(lua_Number number)
	{
		LogTrace("LuaInt64 LuaInt64::mul_number(lua_Number number)");
		LogTraceReturn(LuaInt64(static_cast<int64>(m_number * number)));
	}
	LuaInt64 LuaInt64::div_number(lua_Number number)
	{
		LogTrace("LuaInt64 LuaInt64::div_number(lua_Number number)");
		LogTraceReturn(LuaInt64(static_cast<int64>(m_number / number)));
	}
	LuaInt64 LuaInt64::mod_number(lua_Number number)
	{
		LogTrace("LuaInt64 LuaInt64::mod_number(lua_Number number)");
		LogTraceReturn(LuaInt64(m_number % static_cast<int64>(number)));
	}
	LuaInt64 LuaInt64::pow_number(lua_Number number)
	{
		LogTrace("LuaInt64 LuaInt64::pow_number(lua_Number number)");
		LogTraceReturn(LuaInt64(static_cast<int64>(pow(m_number, number))));
	}
	LuaInt64 LuaInt64::unm_number()
	{
		LogTrace("LuaInt64 LuaInt64::unm_number()");
		LogTraceReturn(LuaInt64(-m_number));
	}
	bool LuaInt64::eq_number(lua_Number number)
	{
		LogTrace("bool LuaInt64::eq_number(lua_Number number)");
		LogTraceReturn(m_number == static_cast<int64>(number));
	}
	bool LuaInt64::lt_number(lua_Number number)
	{
		LogTrace("bool LuaInt64::lt_number(lua_Number number)");
		LogTraceReturn(m_number < static_cast<int64>(number));
	}
	bool LuaInt64::le_number(lua_Number number)
	{
		LogTrace("bool LuaInt64::le_number(lua_Number number)");
		LogTraceReturn(m_number <= static_cast<int64>(number));
	}


	LuaInt64 LuaInt64::add_st(const LuaInt64 & number)
	{
		LogTrace("LuaInt64 LuaInt64::add_st(const LuaInt64 & number)");
		LogTraceReturn(LuaInt64(m_number + number.m_number));
	}
	LuaInt64 LuaInt64::sub_st(const LuaInt64 & number)
	{
		LogTrace("LuaInt64 LuaInt64::sub_st(const LuaInt64 & number)");
		LogTraceReturn(LuaInt64(m_number - number.m_number));
	}
	LuaInt64 LuaInt64::mul_st(const LuaInt64 & number)
	{
		LogTrace("LuaInt64 LuaInt64::mul_st(const LuaInt64 & number)");
		LogTraceReturn(LuaInt64(m_number * number.m_number));
	}
	LuaInt64 LuaInt64::div_st(const LuaInt64 & number)
	{
		LogTrace("LuaInt64 LuaInt64::div_st(const LuaInt64 & number)");
		LogTraceReturn(LuaInt64(m_number / number.m_number));
	}
	LuaInt64 LuaInt64::mod_st(const LuaInt64 & number)
	{
		LogTrace("LuaInt64 LuaInt64::mod_st(const LuaInt64 & number)");
		LogTraceReturn(LuaInt64(m_number % number.m_number));
	}
	LuaInt64 LuaInt64::pow_st(const LuaInt64 & number)
	{
		LogTrace("LuaInt64 LuaInt64::pow_st(const LuaInt64 & number)");
		LogTraceReturn(LuaInt64(static_cast<int64>(pow(m_number, number.m_number))));
	}
	bool LuaInt64::eq_st(const LuaInt64 & number)
	{
		LogTrace("bool LuaInt64::eq_st(const LuaInt64 & number)");
		LogTraceReturn(m_number == number.m_number);
	}
	bool LuaInt64::lt_st(const LuaInt64 & number)
	{
		LogTrace("bool LuaInt64::lt_st(const LuaInt64 & number)");
		LogTraceReturn(m_number < number.m_number);
	}
	bool LuaInt64::le_st(const LuaInt64 & number)
	{
		LogTrace("bool LuaInt64::le_st(const LuaInt64 & number)");
		LogTraceReturn(m_number <= number.m_number);
	}

	void LuaInt64::add_set_number(lua_Number number)
	{
		LogTrace("void LuaInt64::add_set_number(lua_Number number)");
		m_number += static_cast<int64>(number);
		LogTraceReturnVoid;
	}
	void LuaInt64::sub_set_number(lua_Number number)
	{
		LogTrace("void LuaInt64::sub_set_number(lua_Number number)");
		m_number -= static_cast<int64>(number);
		LogTraceReturnVoid;
	}
	void LuaInt64::mul_set_number(lua_Number number)
	{
		LogTrace("void LuaInt64::mul_set_number(lua_Number number)");
		m_number = static_cast<int64>(m_number * number);
		LogTraceReturnVoid;
	}
	void LuaInt64::div_set_number(lua_Number number)
	{
		LogTrace("void LuaInt64::div_set_number(lua_Number number)");
		m_number = static_cast<int64>(m_number / number);
		LogTraceReturnVoid;
	}
	void LuaInt64::mod_set_number(lua_Number number)
	{
		LogTrace("void LuaInt64::mod_set_number(lua_Number number)");
		m_number %= static_cast<int64>(number);
		LogTraceReturnVoid;
	}
	void LuaInt64::pow_set_number(lua_Number number)
	{
		LogTrace("void LuaInt64::pow_set_number(lua_Number number)");
		m_number = static_cast<int64>(pow(m_number, number));
		LogTraceReturnVoid;
	}
	void LuaInt64::unm_set_number()
	{
		LogTrace("void LuaInt64::unm_set_number()");
		m_number = -m_number;
		LogTraceReturnVoid;
	}
	void LuaInt64::add_set_st(const LuaInt64 & number)
	{
		LogTrace("void LuaInt64::add_set_st(const LuaInt64 & number)");
		m_number += number.m_number;
		LogTraceReturnVoid;
	}
	void LuaInt64::sub_set_st(const LuaInt64 & number)
	{
		LogTrace("void LuaInt64::sub_set_st(const LuaInt64 & number)");
		m_number -= number.m_number;
		LogTraceReturnVoid;
	}
	void LuaInt64::mul_set_st(const LuaInt64 & number)
	{
		LogTrace("void LuaInt64::mul_set_st(const LuaInt64 & number)");
		m_number *= number.m_number;
		LogTraceReturnVoid;
	}
	void LuaInt64::div_set_st(const LuaInt64 & number)
	{
		LogTrace("void LuaInt64::div_set_st(const LuaInt64 & number)");
		m_number /= number.m_number;
		LogTraceReturnVoid;
	}
	void LuaInt64::mod_set_st(const LuaInt64 & number)
	{
		LogTrace("void LuaInt64::mod_set_st(const LuaInt64 & number)");
		m_number %= number.m_number;
		LogTraceReturnVoid;
	}
	void LuaInt64::pow_set_st(const LuaInt64 & number)
	{
		LogTrace("void LuaInt64::pow_set_st(const LuaInt64 & number)");
		m_number = static_cast<int64>(pow(m_number, number.m_number));
		LogTraceReturnVoid;
	}

	//////////////////////////////////////////////////////////
	//LuaUint64
	/////////////////////////////////////////////////////////
	LuaUint64::LuaUint64(lua_Number number) : m_number(static_cast<uint64>(number))
	{
		LogTrace("LuaUint64::LuaUint64(lua_Number number)");
		LogTraceReturnVoid;
	}

	LuaUint64::LuaUint64(uint64 number) : m_number(number)
	{
		LogTrace("LuaUint64::LuaUint64(int64 number)");
		LogTraceReturnVoid;
	}

	LuaUint64 LuaUint64::new_from_string(CharPtrBridge number)
	{
		LogTrace("LuaUint64 LuaUint64::new_from_string(CharPtrBridge number)");
		uint64 num = strtoull(number.m_charPtr, NULL, 10);
		LogTraceReturn(LuaUint64(num));
	}
	LuaUint64 LuaUint64::new_from_st(const LuaUint64 & number)
	{
		LogTrace("LuaUint64 LuaUint64::new_from_st(const LuaUint64 & number)");
		LogTraceReturn(LuaUint64(number.m_number));
	}

	const std::string LuaUint64::to_string()
	{
		LogTrace("const std::string LuaUint64::to_string()");
		char num[32] = { 0 };
		snprintf(num, 32, "%llu", m_number);
		LogTraceReturn(std::string(num));
	}
	lua_Number LuaUint64::to_number()
	{
		LogTrace("lua_Number LuaUint64::to_number()");
		LogTraceReturn(static_cast<lua_Number>(m_number));
	}
	LuaInt64 LuaUint64::to_int64()
	{
		LogTrace("LuaInt64 LuaUint64::to_int64()");
		LogTraceReturn(LuaInt64(static_cast<int64>(m_number)));
	}

	void LuaUint64::set_number(lua_Number number)
	{
		LogTrace("void LuaUint64::set_number(lua_Number number)");
		m_number = static_cast<uint64>(number);
		LogTraceReturnVoid;
	}
	void LuaUint64::set_string(const CharPtrBridge number)
	{
		LogTrace("void LuaUint64::set_string(const CharPtrBridge number)");
		m_number = strtoull(number.m_charPtr, NULL, 10);
		LogTraceReturnVoid;
	}
	void LuaUint64::set_st(const LuaUint64 & number)
	{
		LogTrace("void LuaUint64::set_st(const LuaUint64 & number)");
		m_number = number.m_number;
		LogTraceReturnVoid;
	}

	LuaUint64 LuaUint64::add_number(lua_Number number)
	{
		LogTrace("LuaUint64 LuaUint64::add_number(lua_Number number)");
		LogTraceReturn(LuaUint64(m_number + static_cast<uint64>(number)));
	}
	LuaUint64 LuaUint64::sub_number(lua_Number number)
	{
		LogTrace("LuaUint64 LuaUint64::sub_number(lua_Number number)");
		LogTraceReturn(LuaUint64(m_number - static_cast<uint64>(number)));
	}
	LuaUint64 LuaUint64::mul_number(lua_Number number)
	{
		LogTrace("LuaUint64 LuaUint64::mul_number(lua_Number number)");
		LogTraceReturn(LuaUint64(static_cast<uint64>(m_number * number)));
	}
	LuaUint64 LuaUint64::div_number(lua_Number number)
	{
		LogTrace("LuaUint64 LuaUint64::div_number(lua_Number number)");
		LogTraceReturn(LuaUint64(static_cast<uint64>(m_number / number)));
	}
	LuaUint64 LuaUint64::mod_number(lua_Number number)
	{
		LogTrace("LuaUint64 LuaUint64::mod_number(lua_Number number)");
		LogTraceReturn(LuaUint64(m_number % static_cast<uint64>(number)));
	}
	LuaUint64 LuaUint64::pow_number(lua_Number number)
	{
		LogTrace("LuaUint64 LuaUint64::pow_number(lua_Number number)");
		LogTraceReturn(LuaUint64(static_cast<uint64>(pow(m_number, number))));
	}
	LuaInt64 LuaUint64::unm_number()
	{
		LogTrace("LuaInt64 LuaUint64::unm_number()");
		LogTraceReturn(LuaInt64(-static_cast<int64>(m_number)));
	}
	bool LuaUint64::eq_number(lua_Number number)
	{
		LogTrace("bool LuaUint64::eq_number(lua_Number number)");
		LogTraceReturn(m_number == static_cast<uint64>(number));
	}
	bool LuaUint64::lt_number(lua_Number number)
	{
		LogTrace("bool LuaUint64::lt_number(lua_Number number)");
		LogTraceReturn(m_number < static_cast<uint64>(number));
	}
	bool LuaUint64::le_number(lua_Number number)
	{
		LogTrace("bool LuaUint64::le_number(lua_Number number)");
		LogTraceReturn(m_number <= static_cast<uint64>(number));
	}


	LuaUint64 LuaUint64::add_st(const LuaUint64 & number)
	{
		LogTrace("LuaUint64 LuaUint64::add_st(const LuaUint64 & number)");
		LogTraceReturn(LuaUint64(m_number + number.m_number));
	}
	LuaUint64 LuaUint64::sub_st(const LuaUint64 & number)
	{
		LogTrace("LuaUint64 LuaUint64::sub_st(const LuaUint64 & number)");
		LogTraceReturn(LuaUint64(m_number - number.m_number));
	}
	LuaUint64 LuaUint64::mul_st(const LuaUint64 & number)
	{
		LogTrace("LuaUint64 LuaUint64::mul_st(const LuaUint64 & number)");
		LogTraceReturn(LuaUint64(m_number * number.m_number));
	}
	LuaUint64 LuaUint64::div_st(const LuaUint64 & number)
	{
		LogTrace("LuaUint64 LuaUint64::div_st(const LuaUint64 & number)");
		LogTraceReturn(LuaUint64(m_number / number.m_number));
	}
	LuaUint64 LuaUint64::mod_st(const LuaUint64 & number)
	{
		LogTrace("LuaUint64 LuaUint64::mod_st(const LuaUint64 & number)");
		LogTraceReturn(LuaUint64(m_number % number.m_number));
	}
	LuaUint64 LuaUint64::pow_st(const LuaUint64 & number)
	{
		LogTrace("LuaUint64 LuaUint64::pow_st(const LuaUint64 & number)");
		LogTraceReturn(LuaUint64(static_cast<uint64>(pow(m_number, number.m_number))));
	}
	bool LuaUint64::eq_st(const LuaUint64 & number)
	{
		LogTrace("bool LuaUint64::eq_st(const LuaUint64 & number)");
		LogTraceReturn(m_number == number.m_number);
	}
	bool LuaUint64::lt_st(const LuaUint64 & number)
	{
		LogTrace("bool LuaUint64::lt_st(const LuaUint64 & number)");
		LogTraceReturn(m_number < number.m_number);
	}
	bool LuaUint64::le_st(const LuaUint64 & number)
	{
		LogTrace("bool LuaUint64::le_st(const LuaUint64 & number)");
		LogTraceReturn(m_number <= number.m_number);
	}

	void LuaUint64::add_set_number(lua_Number number)
	{
		LogTrace("void LuaUint64::add_set_number(lua_Number number)");
		m_number += static_cast<uint64>(number);
		LogTraceReturnVoid;
	}
	void LuaUint64::sub_set_number(lua_Number number)
	{
		LogTrace("void LuaUint64::sub_set_number(lua_Number number)");
		m_number -= static_cast<uint64>(number);
		LogTraceReturnVoid;
	}
	void LuaUint64::mul_set_number(lua_Number number)
	{
		LogTrace("void LuaUint64::mul_set_number(lua_Number number)");
		m_number = static_cast<uint64>(m_number * number);
		LogTraceReturnVoid;
	}
	void LuaUint64::div_set_number(lua_Number number)
	{
		LogTrace("void LuaUint64::div_set_number(lua_Number number)");
		m_number = static_cast<uint64>(m_number / number);
		LogTraceReturnVoid;
	}
	void LuaUint64::mod_set_number(lua_Number number)
	{
		LogTrace("void LuaUint64::mod_set_number(lua_Number number)");
		m_number %= static_cast<uint64>(number);
		LogTraceReturnVoid;
	}
	void LuaUint64::pow_set_number(lua_Number number)
	{
		LogTrace("void LuaUint64::pow_set_number(lua_Number number)");
		m_number = static_cast<uint64>(pow(m_number, number));
		LogTraceReturnVoid;
	}
	void LuaUint64::unm_set_number()
	{
		LogTrace("void LuaUint64::unm_set_number()");
		m_number = -m_number;
		LogTraceReturnVoid;
	}
	void LuaUint64::add_set_st(const LuaUint64 & number)
	{
		LogTrace("void LuaUint64::add_set_st(const LuaUint64 & number)");
		m_number += number.m_number;
		LogTraceReturnVoid;
	}
	void LuaUint64::sub_set_st(const LuaUint64 & number)
	{
		LogTrace("void LuaUint64::sub_set_st(const LuaUint64 & number)");
		m_number -= number.m_number;
		LogTraceReturnVoid;
	}
	void LuaUint64::mul_set_st(const LuaUint64 & number)
	{
		LogTrace("void LuaUint64::mul_set_st(const LuaUint64 & number)");
		m_number *= number.m_number;
		LogTraceReturnVoid;
	}
	void LuaUint64::div_set_st(const LuaUint64 & number)
	{
		LogTrace("void LuaUint64::div_set_st(const LuaUint64 & number)");
		m_number /= number.m_number;
		LogTraceReturnVoid;
	}
	void LuaUint64::mod_set_st(const LuaUint64 & number)
	{
		LogTrace("void LuaUint64::mod_set_st(const LuaUint64 & number)");
		m_number %= number.m_number;
		LogTraceReturnVoid;
	}
	void LuaUint64::pow_set_st(const LuaUint64 & number)
	{
		LogTrace("void LuaUint64::pow_set_st(const LuaUint64 & number)");
		m_number = static_cast<uint64>(pow(m_number, number.m_number));
		LogTraceReturnVoid;
	}
}