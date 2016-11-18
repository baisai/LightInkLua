


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

#include "Common/SmallObject.h"
#include "Atomic/mintomic.h"

namespace LightInk
{

	template <typename Allocator>
	class LIGHTINK_TEMPLATE_DECL RefCounter : public Allocator
	{
	public:
		RefCounter() : m_sharedRefs(1), m_weakRefs(0) {  }
		int64 inc_shared() { ++m_sharedRefs; return m_sharedRefs; }
		int64 dec_shared() { if (m_sharedRefs > 0) { --m_sharedRefs; } return m_sharedRefs; }
		int64 inc_weak() { ++m_weakRefs; return m_weakRefs; }
		int64 dec_weak() { if (m_weakRefs > 0) { --m_weakRefs; } return m_weakRefs; }
		int64 get_shared_refs() const { return m_sharedRefs; }
		int64 get_weak_refs() const { return m_weakRefs; }
		bool has_refs() const { return (m_sharedRefs + m_weakRefs > 0); }

	private:
		int64 m_sharedRefs;
		int64 m_weakRefs;
	};

	template <typename Allocator>
	class LIGHTINK_TEMPLATE_DECL RefCounterTS : public Allocator
	{
	public:
		RefCounterTS() { mint_store_64_relaxed(&m_sharedRefs, 1); mint_store_64_relaxed(&m_weakRefs, 0); }
		int64 inc_shared() { return mint_fetch_add_64_relaxed(&m_sharedRefs, 1) + 1; }
		int64 dec_shared() 
		{ 
			int64 r = mint_fetch_add_64_relaxed(&m_sharedRefs, -1);
			if (r == 0) { mint_store_64_relaxed(&m_sharedRefs, 0); return r; }
			return (r - 1); 
		}
		int64 inc_weak() { return mint_fetch_add_64_relaxed(&m_weakRefs, 1) + 1; }
		int64 dec_weak()
		{
			int64 r = mint_fetch_add_64_relaxed(&m_weakRefs, -1);
			if (r == 0) { mint_store_64_relaxed(&m_weakRefs, 0); return r; }
			return (r - 1);
		}
		int64 get_shared_refs() const { return mint_load_64_relaxed(&m_sharedRefs); }
		int64 get_weak_refs() const { return mint_load_64_relaxed(&m_weakRefs); }
		bool has_refs() const { return mint_load_64_relaxed(&m_sharedRefs) + mint_load_64_relaxed(&m_weakRefs) > 0; }

	private:
		mint_atomic64_t m_sharedRefs;
		mint_atomic64_t m_weakRefs;
	};

}


#endif