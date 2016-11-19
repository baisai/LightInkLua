


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
#ifndef LIGHTINK_COMMON_TYPE_H_
#define LIGHTINK_COMMON_TYPE_H_

#include "Common/Config.h"
#include "Common/WinSnprintf.h"

#define LIGHTINK_DISABLE_COPY(name) \
	private: \
	name(const name &); \
	name & operator = (const name &);

#define LIGHTINK_ONLE_HEAP_NEW(name) \
	private: \
	~name();


#if defined(_MSC_VER) && _MSC_VER < 1600
# include "stdint_msvc2008.h"
#else
# include <stdint.h>
#endif



/////////////////////////////////////////////////////////////
//类型
////////////////////////////////////////////////////////////

typedef uint64_t uint64;
typedef int64_t int64;
typedef uint32_t uint32;
typedef int32_t int32;
typedef uint16_t uint16;
typedef int16_t int16;
typedef uint8_t uint8;
typedef int8_t int8;



typedef uint32 ENTITY_ID;
typedef uint32 OPCODE_ID;
typedef uint32 SERVER_ID;
typedef uint16 PROC_ID;
typedef uint16 SERVER_TYPE;
typedef uint32 MSG_OPCODE;
typedef uint8 BROADCAST_TYPE;
typedef uint8 LINK_TYPE;
typedef uint32 LINK_ID;
typedef int PID_TYPE;



//////////////////////////////////////////////////////////
//常数
/////////////////////////////////////////////////////////
namespace LightInk
{
	const int32 maxInt = 0x7FFF;
	const uint32 maxUint32 = (uint32)-1;

}



#endif