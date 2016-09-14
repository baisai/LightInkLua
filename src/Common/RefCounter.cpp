


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

#include "Common/Log.h"
#include "Common/RefCounter.h"


namespace LightInk
{
	/////////////////////////////////////////////////////
	//Counter
	////////////////////////////////////////////////////
	RefCounter::RefCounter() : m_sharedRefs(1), m_weakRefs(0)
	{
		LogTrace("RefCounter::RefCounter()");
		LogTraceReturnVoid;
	}

	int64 RefCounter::inc_shared()
	{
		LogTrace("size_t RefCounter::inc_shared()");
		++m_sharedRefs;
		LogTraceReturn(m_sharedRefs);
	}
	int64 RefCounter::dec_shared()
	{
		LogTrace("size_t RefCounter::dec_shared()");
		if (m_sharedRefs == 0)
		{
			LogError("call RefCount::dec_shared() error!!!! m_sharedRefs == 0");
			LogTraceReturn(m_sharedRefs);
		}
		--m_sharedRefs;
		LogTraceReturn(m_sharedRefs);
	}
	int64 RefCounter::inc_weak()
	{
		LogTrace("size_t RefCounter::inc_weak()");
		++m_weakRefs;
		LogTraceReturn(m_weakRefs);
	}
	int64 RefCounter::dec_weak()
	{
		LogTrace("size_t RefCounter::dec_weak()");
		if (m_weakRefs == 0)
		{
			LogError("call RefCount::dec_weak() error!!!! m_weakRefs == 0");
			LogTraceReturn(m_weakRefs);
		}
		--m_weakRefs;
		LogTraceReturn(m_weakRefs);
	}
	int64 RefCounter::get_shared_refs() const
	{
		LogTrace("size_t RefCounter::get_shared_refs()");
		LogTraceReturn(m_sharedRefs);
	}
	int64 RefCounter::get_weak_refs() const
	{
		LogTrace("size_t RefCounter::get_weak_refs()");
		LogTraceReturn(m_weakRefs);
	}
	bool RefCounter::has_refs() const
	{
		LogTrace("bool RefCounter::has_refs()");
		LogTraceReturn((m_sharedRefs + m_weakRefs > 0));
	}






	/////////////////////////////////////////////////////
	//CounterTS
	////////////////////////////////////////////////////
	RefCounterTS::RefCounterTS()
	{
		LogTrace("RefCounterTS::RefCounterTS()");
		mint_store_64_relaxed(&m_sharedRefs, 1);
		mint_store_64_relaxed(&m_weakRefs, 0);
		LogTraceReturnVoid;
	}

	int64 RefCounterTS::inc_shared()
	{
		LogTrace("size_t RefCounterTS::inc_shared()");
		int64 r = mint_fetch_add_64_relaxed(&m_sharedRefs, 1);
		LogTraceReturn(r + 1);
	}
	int64 RefCounterTS::dec_shared()
	{
		LogTrace("size_t RefCounterTS::dec_shared()");
		int64 r = mint_fetch_add_64_relaxed(&m_sharedRefs, -1);
		if (r == 0)
		{
			LogError("call RefCount::dec_shared() error!!!! m_sharedRefs == 0");
			mint_store_64_relaxed(&m_sharedRefs, 0);
			LogTraceReturn(r);
		}
		LogTraceReturn(r - 1);
	}
	int64 RefCounterTS::inc_weak()
	{
		LogTrace("size_t RefCounterTS::inc_weak()");
		int64 r = mint_fetch_add_64_relaxed(&m_weakRefs, 1);
		LogTraceReturn(r + 1);
	}
	int64 RefCounterTS::dec_weak()
	{
		LogTrace("size_t RefCounterTS::dec_weak()");
		int64 r = mint_fetch_add_64_relaxed(&m_weakRefs, -1);
		if (r == 0)
		{
			LogError("call RefCount::dec_weak() error!!!! m_weakRefs == 0");
			mint_store_64_relaxed(&m_weakRefs, 0);
			LogTraceReturn(r);
		}
		LogTraceReturn(r - 1);
	}
	int64 RefCounterTS::get_shared_refs() const
	{
		LogTrace("size_t RefCounterTS::get_shared_refs()");
		LogTraceReturn(mint_load_64_relaxed(&m_sharedRefs));
	}
	int64 RefCounterTS::get_weak_refs() const
	{
		LogTrace("size_t RefCounterTS::get_weak_refs()");
		LogTraceReturn(mint_load_64_relaxed(&m_weakRefs));
	}
	bool RefCounterTS::has_refs() const
	{
		LogTrace("bool RefCounterTS::has_refs()");
		int64 r = mint_load_64_relaxed(&m_sharedRefs) + mint_load_64_relaxed(&m_weakRefs);
		LogTraceReturn((r > 0));
	}

}