


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

#ifndef LIGHTINK_COMMON_REFCOUNTER_H_
#define LIGHTINK_COMMON_REFCOUNTER_H_

#include "Atomic/mintomic.h"
#include "Common/SmallObject.h"

namespace LightInk
{

	class LIGHTINK_DECL RefCounter : public SmallObject
	{
	public:
		RefCounter();
		int64 inc_shared();
		int64 dec_shared();
		int64 inc_weak();
		int64 dec_weak();
		int64 get_shared_refs() const;
		int64 get_weak_refs() const;
		bool has_refs() const;

	private:
		int64 m_sharedRefs;
		int64 m_weakRefs;
	};

	class LIGHTINK_DECL RefCounterTS : public SmallObject
	{
	public:
		RefCounterTS();
		int64 inc_shared();
		int64 dec_shared();
		int64 inc_weak();
		int64 dec_weak();
		int64 get_shared_refs() const;
		int64 get_weak_refs() const;
		bool has_refs() const;

	private:
		mint_atomic64_t m_sharedRefs;
		mint_atomic64_t m_weakRefs;
	};

}


#endif