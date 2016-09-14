


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

#ifndef LIGHTINK_COMMON_AUTOPTR_CPP_
#define LIGHTINK_COMMON_AUTOPTR_CPP_

#include "AutoPtr.h"
#include "Common/Log.h"

namespace LightInk
{
	template <typename T, typename DelStrategy>
	AutoPtrWrapper<T, DelStrategy>::AutoPtrWrapper() : m_objPtr(NULL)
	{
		LogTrace("AutoPtrWrapper<T, DelStrategy>::AutoPtrWrapper()");
		LogTraceReturnVoid;
	}

	template <typename T, typename DelStrategy>
	template<typename __T>
	AutoPtrWrapper<T, DelStrategy>::AutoPtrWrapper(__T * ptr) : m_objPtr(ptr)
	{
		LogTrace("AutoPtrWrapper<T, DelStrategy>::AutoPtrWrapper(__T * ptr)");
		LogTraceReturnVoid;
	}

	template <typename T, typename DelStrategy>
	AutoPtrWrapper<T, DelStrategy>::AutoPtrWrapper(const AutoPtrWrapper<T, DelStrategy> & cp) : m_objPtr(cp.release())
	{
		LogTrace("AutoPtrWrapper<T, DelStrategy>::AutoPtrWrapper(const AutoPtrWrapper<T, DelStrategy> & cp)");
		LogTraceReturnVoid;
	}

	template <typename T, typename DelStrategy>
	inline AutoPtrWrapper<T, DelStrategy> & AutoPtrWrapper<T, DelStrategy>::operator = (const AutoPtrWrapper<T, DelStrategy> & right)
	{
		LogTrace("AutoPtrWrapper<T, DelStrategy> & AutoPtrWrapper<T, DelStrategy>::operator = (const AutoPtrWrapper<T, DelStrategy> & right)");
		reset(right.release());
		LogTraceReturn(*this);
	}


	template <typename T, typename DelStrategy>
	template <typename __T, typename __DelStrategy>
	AutoPtrWrapper<T, DelStrategy>::AutoPtrWrapper(const AutoPtrWrapper<__T, __DelStrategy> & cp) : m_objPtr(cp.release())
	{
		LogTrace("AutoPtrWrapper<T, DelStrategy>::AutoPtrWrapper(const AutoPtrWrapper<__T, __DelStrategy> & cp)");
		LogTraceReturnVoid;
	}


	template <typename T, typename DelStrategy>
	template <typename __T, typename __DelStrategy>
	inline AutoPtrWrapper<T, DelStrategy> & AutoPtrWrapper<T, DelStrategy>::operator = (const AutoPtrWrapper<__T, __DelStrategy> & right)
	{
		LogTrace("AutoPtrWrapper<T, DelStrategy> & AutoPtrWrapper<T, DelStrategy>::operator = (const AutoPtrWrapper<__T, __DelStrategy> & right)");
		reset(right.release());
		LogTraceReturn(*this);
	}


	template <typename T, typename DelStrategy>
	AutoPtrWrapper<T, DelStrategy>::~AutoPtrWrapper()
	{
		LogTrace("AutoPtrWrapper<T, DelStrategy>::~AutoPtrWrapper()");
		if (m_objPtr)
		{
			DelStrategy::release(m_objPtr);
			m_objPtr = NULL;
		}
		LogTraceReturnVoid;
	}

	template <typename T, typename DelStrategy>
	inline void AutoPtrWrapper<T, DelStrategy>::reset(T * ptr)
	{
		LogTrace("void AutoPtrWrapper<T, DelStrategy>::reset(T * ptr)");
		if (ptr && ptr != m_objPtr)
		{
			DelStrategy::release(m_objPtr);
		}
		m_objPtr = ptr;
		LogTraceReturnVoid;
	}

	template <typename T, typename DelStrategy>
	inline T * AutoPtrWrapper<T, DelStrategy>::get() const
	{
		LogTrace("T * AutoPtrWrapper<T, DelStrategy>::get() const");
		LogTraceReturn(m_objPtr);
	}

	template <typename T, typename DelStrategy>
	inline T * AutoPtrWrapper<T, DelStrategy>::release()
	{
		LogTrace("T * AutoPtrWrapper<T, DelStrategy>::release()");
		T * t = m_objPtr;
		m_objPtr = NULL;
		LogTraceReturn(t);
	}

	template <typename T, typename DelStrategy>
	inline T & AutoPtrWrapper<T, DelStrategy>::operator * () const
	{
		LogTrace("T & AutoPtrWrapper<T, DelStrategy>::operator * () const");
		LogTraceReturn((*m_objPtr));
	}

	template <typename T, typename DelStrategy>
	inline T * AutoPtrWrapper<T, DelStrategy>::operator -> () const
	{
		LogTrace("T * AutoPtrWrapper<T, DelStrategy>::operator -> () const");
		LogTraceReturn(m_objPtr);
	}

	template <typename T, typename DelStrategy>
	inline AutoPtrWrapper<T, DelStrategy>::operator bool() const
	{
		LogTrace("AutoPtrWrapper<T, DelStrategy>::operator bool() const");
		LogTraceReturn(m_objPtr != NULL);
	}



	template <typename T, typename DelStrategy>
	bool operator == (const AutoPtrWrapper<T, DelStrategy> & left, T * right)
	{
		LogTrace("bool operator == (const AutoPtrWrapper<T, DelStrategy> & left, T * right)");
		LogTraceReturn(left->get() == right);
	}

	template <typename T, typename DelStrategy>
	bool operator == (T * left, const AutoPtrWrapper<T, DelStrategy> & right)
	{
		LogTrace("bool operator == (T * left, const AutoPtrWrapper<T, DelStrategy> & right)");
		LogTraceReturn(left == right->get());
	}

	template <typename T, typename DelStrategy>
	bool operator != (const AutoPtrWrapper<T, DelStrategy> & left, T * right)
	{
		LogTrace("bool operator != (const AutoPtrWrapper<T, DelStrategy> & left, T * right)");
		LogTraceReturn(left->get() != right);
	}

	template <typename T, typename DelStrategy>
	bool operator != (T * left,const AutoPtrWrapper<T, DelStrategy> & right)
	{
		LogTrace("bool operator != (T * left,const AutoPtrWrapper<T, DelStrategy> & right)");
		LogTraceReturn(left != right->get());
	}

	//////////////////////////////////////////////////////////////////////////////
	//DelStrategy
	/////////////////////////////////////////////////////////////////////////////
	template <typename T>
	inline void PtrDelStrategy::release(T * ptr)
	{
		LogTrace("void PtrDelStrategy::release(T * ptr)");
		if (ptr) { delete ptr; }
		LogTraceReturnVoid;
	}

	template <typename T>
	inline void ArrayDelStrategy::release(T * ptr)
	{
		LogTrace("void ArrayDelStrategy::release(T * ptr)");
		if (ptr) { delete [] ptr; }
		LogTraceReturnVoid;
	}

}

#endif