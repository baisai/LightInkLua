


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
#ifndef LIGHTINK_COMMON_SHAREDPTR_CPP_
#define LIGHTINK_COMMON_SHAREDPTR_CPP_

#include "Common/Log.h"
#include "SharedPtr.h"

namespace LightInk
{

	///////////////////////////////////////////////////////////////////////
	//SharedPtr
	//////////////////////////////////////////////////////////////////////
	template <typename T, typename Counter, typename DelStrategy>
	SharedPtrWrapper<T, Counter, DelStrategy>::SharedPtrWrapper() : m_objPtr(NULL), m_refControl(NULL)
	{
		LogTrace("SharedPtrWrapper<T, Counter, DelStrategy>::SharedPtrWrapper()");
		set_ptr(NULL);
		LogTraceReturnVoid;
	}

	template <typename T, typename Counter, typename DelStrategy>
	template<typename __T>
	SharedPtrWrapper<T, Counter, DelStrategy>::SharedPtrWrapper(__T * ptr)
	{
		LogTrace("SharedPtrWrapper<T, Counter, DelStrategy>::SharedPtrWrapper(__T * ptr)");
		set_ptr(ptr);
		LogTraceReturnVoid;
	}

	template <typename T, typename Counter, typename DelStrategy>
	SharedPtrWrapper<T, Counter, DelStrategy>::SharedPtrWrapper(const SharedPtrWrapper<T, Counter, DelStrategy> & cp)
	{
		LogTrace("SharedPtrWrapper<T, Counter, DelStrategy>::SharedPtrWrapper(const SharedPtrWrapper<T, Counter, DelStrategy> & cp)");
		m_objPtr = cp.m_objPtr;
		m_refControl = cp.m_refControl;
		m_refControl->inc_shared();
		LogTraceReturnVoid;
	}


	template <typename T, typename Counter, typename DelStrategy>
	SharedPtrWrapper<T, Counter, DelStrategy> & SharedPtrWrapper<T, Counter, DelStrategy>::operator = (const SharedPtrWrapper<T, Counter, DelStrategy> & right)
	{
		LogTrace("SharedPtrWrapper<T, Counter, DelStrategy> & SharedPtrWrapper<T, Counter, DelStrategy>::operator = (const SharedPtrWrapper<T, Counter, DelStrategy> & right)");
		if (this == &right) { LogTraceReturn((*this)); }
		reset();
		m_objPtr = right.m_objPtr;
		m_refControl = right.m_refControl;
		m_refControl->inc_shared();
		LogTraceReturn((*this));
	}

	template <typename T, typename Counter, typename DelStrategy>
	SharedPtrWrapper<T, Counter, DelStrategy>::SharedPtrWrapper(const WeakPtrWrapper<T, Counter, DelStrategy> & wpw)
	{
		LogTrace("SharedPtrWrapper<T, Counter, DelStrategy>::SharedPtrWrapper(const WeakPtrWrapper<T, Counter, DelStrategy> & wpw)");
		m_objPtr = wpw.m_objPtr;
		m_refControl = wpw.m_refControl;
		m_refControl->inc_shared();
		LogTraceReturnVoid;
	}


	template <typename T, typename Counter, typename DelStrategy>
	template <typename __T, typename __Counter, typename __DelStrategy>
	SharedPtrWrapper<T, Counter, DelStrategy>::SharedPtrWrapper(const SharedPtrWrapper<__T, __Counter, __DelStrategy> & cp)
	{
		LogTrace("SharedPtrWrapper<T, Counter, DelStrategy>::SharedPtrWrapper(const SharedPtrWrapper<__T, __Counter, __DelStrategy> & cp)");
		m_objPtr = cp.m_objPtr;
		m_refControl = cp.m_refControl;
		m_refControl->inc_shared();
		LogTraceReturnVoid;
	}


	template <typename T, typename Counter, typename DelStrategy>
	template <typename __T, typename __Counter, typename __DelStrategy>
	SharedPtrWrapper<T, Counter, DelStrategy> & SharedPtrWrapper<T, Counter, DelStrategy>::operator = (const SharedPtrWrapper<__T, __Counter, __DelStrategy> & right)
	{
		LogTrace("SharedPtrWrapper<T, Counter, DelStrategy> & SharedPtrWrapper<T, Counter, DelStrategy>::operator = (const SharedPtrWrapper<__T, __Counter, __DelStrategy> & right)");
		if (this == &right) { LogTraceReturn((*this)); }
		reset();
		m_objPtr = right.m_objPtr;
		m_refControl = right.m_refControl;
		m_refControl->inc_shared();
		LogTraceReturn((*this));
	}


	template <typename T, typename Counter, typename DelStrategy>
	template <typename __T, typename __Counter, typename __DelStrategy>
	SharedPtrWrapper<T, Counter, DelStrategy>::SharedPtrWrapper(const WeakPtrWrapper<__T, __Counter, __DelStrategy> & wpw)
	{
		LogTrace("SharedPtrWrapper<T, Counter, DelStrategy>::SharedPtrWrapper(const WeakPtrWrapper<__T, __Counter, __DelStrategy> & wpw)");
		m_objPtr = wpw.m_objPtr;
		m_refControl = wpw.m_refControl;
		m_refControl->inc_shared();
		LogTraceReturnVoid;
	}


	template <typename T, typename Counter, typename DelStrategy>
	SharedPtrWrapper<T, Counter, DelStrategy>::~SharedPtrWrapper()
	{
		LogTrace("SharedPtrWrapper<T, Counter, DelStrategy>::~SharedPtrWrapper()");
		check_delete_ptr();
		LogTraceReturnVoid;
	}

	template <typename T, typename Counter, typename DelStrategy>
	inline void SharedPtrWrapper<T, Counter, DelStrategy>::reset()
	{
		LogTrace("void SharedPtrWrapper<T, Counter, DelStrategy>::reset()");
		check_delete_ptr();
		LogTraceReturnVoid;
	}


	template <typename T, typename Counter, typename DelStrategy>
	template <typename __T>
	inline void SharedPtrWrapper<T, Counter, DelStrategy>::reset(__T * ptr)
	{
		LogTrace("void SharedPtrWrapper<T, Counter, DelStrategy>::reset(__T * ptr)");
		check_delete_ptr();
		set_ptr(ptr);
		LogTraceReturnVoid;
	}

	template <typename T, typename Counter, typename DelStrategy>
	inline void SharedPtrWrapper<T, Counter, DelStrategy>::swap(SharedPtrWrapper<T, Counter, DelStrategy> & right)
	{
		LogTrace("void SharedPtrWrapper<T, Counter, DelStrategy>::swap(SharedPtrWrapper<T, Counter, DelStrategy> & right)");
		if (this == &right) { LogTraceReturn((*this)); }
		T * tempPtr = m_objPtr;
		Counter * tempControl = m_refControl;
		m_objPtr = right.m_objPtr;
		m_refControl = right.m_refControl;
		right.m_objPtr = tempPtr;
		right.m_refControl = tempControl;
		LogTraceReturnVoid;
	}

	template <typename T, typename Counter, typename DelStrategy>
	inline T * SharedPtrWrapper<T, Counter, DelStrategy>::get() const
	{
		LogTrace("T * SharedPtrWrapper<T, Counter, DelStrategy>::get() const");
		LogTraceReturn(m_objPtr);
	}

	template <typename T, typename Counter, typename DelStrategy>
	inline T & SharedPtrWrapper<T, Counter, DelStrategy>::operator * () const
	{
		LogTrace("T & SharedPtrWrapper<T, Counter, DelStrategy>::operator * () const");
		LogTraceReturn((*m_objPtr));
	}


	template <typename T, typename Counter, typename DelStrategy>
	inline T * SharedPtrWrapper<T, Counter, DelStrategy>::operator -> () const
	{
		LogTrace("T * SharedPtrWrapper<T, Counter, DelStrategy>::operator -> () const");
		LogTraceReturn(m_objPtr);
	}


	template <typename T, typename Counter, typename DelStrategy>
	inline int64 SharedPtrWrapper<T, Counter, DelStrategy>::use_count() const
	{
		LogTrace("int64 SharedPtrWrapper<T, Counter, DelStrategy>::use_count() const");
		if (m_objPtr == NULL)
		{
			LogTraceReturn(0);
		}
		LogTraceReturn(m_refControl->get_shared_refs());
	}

	template <typename T, typename Counter, typename DelStrategy>
	inline bool SharedPtrWrapper<T, Counter, DelStrategy>::unique() const
	{
		LogTrace("bool SharedPtrWrapper<T, Counter, DelStrategy>::unique() const");
		LogTraceReturn(use_count() == 1);
	}

	template <typename T, typename Counter, typename DelStrategy>
	inline SharedPtrWrapper<T, Counter, DelStrategy>::operator bool() const
	{
		LogTrace("SharedPtrWrapper<T, Counter, DelStrategy>::operator bool() const");
		LogTraceReturn(m_objPtr != NULL);
	}

	template <typename T, typename Counter, typename DelStrategy>
	template <typename __T, typename __Counter, typename __DelStrategy>
	inline bool SharedPtrWrapper<T, Counter, DelStrategy>::operator == (const SharedPtrWrapper<__T, __Counter, __DelStrategy> & right) const
	{
		LogTrace("bool SharedPtrWrapper<T, Counter, DelStrategy>::operator == (const SharedPtrWrapper<__T, __Counter, __DelStrategy> & right) const");
		LogTraceReturn(m_objPtr == right.m_objPtr);
	}


	template <typename T, typename Counter, typename DelStrategy>
	template <typename __T, typename __Counter, typename __DelStrategy>
	inline bool SharedPtrWrapper<T, Counter, DelStrategy>::operator != (const SharedPtrWrapper<__T, __Counter, __DelStrategy> & right) const
	{
		LogTrace("bool SharedPtrWrapper<T, Counter, DelStrategy>::operator != (const SharedPtrWrapper<__T, __Counter, __DelStrategy> & right) const");
		LogTraceReturn(m_objPtr != right.m_objPtr);
	}


	template <typename T, typename Counter, typename DelStrategy>
	template <typename __T, typename __Counter, typename __DelStrategy>
	inline bool SharedPtrWrapper<T, Counter, DelStrategy>::operator < (const SharedPtrWrapper<__T, __Counter, __DelStrategy> & right) const
	{
		LogTrace("bool SharedPtrWrapper<T, Counter, DelStrategy>::operator < (const SharedPtrWrapper<__T, __Counter, __DelStrategy> & right) const");
		LogTraceReturn(m_objPtr < right.m_objPtr);
	}

	template <typename T, typename Counter, typename DelStrategy>
	template <typename __T, typename __Counter, typename __DelStrategy>
	inline bool SharedPtrWrapper<T, Counter, DelStrategy>::operator > (const SharedPtrWrapper<__T, __Counter, __DelStrategy> & right) const
	{
		LogTrace("bool SharedPtrWrapper<T, Counter, DelStrategy>::operator > (const SharedPtrWrapper<__T, __Counter, __DelStrategy> & right) const");
		LogTraceReturn(m_objPtr > right.m_objPtr);
	}

	template <typename T, typename Counter, typename DelStrategy>
	template <typename __T, typename __Counter, typename __DelStrategy>
	inline bool SharedPtrWrapper<T, Counter, DelStrategy>::operator <= (const SharedPtrWrapper<__T, __Counter, __DelStrategy> & right) const
	{
		LogTrace("bool SharedPtrWrapper<T, Counter, DelStrategy>::operator <= (const SharedPtrWrapper<__T, __Counter, __DelStrategy> & right) const");
		LogTraceReturn(m_objPtr <= right.m_objPtr);
	}


	template <typename T, typename Counter, typename DelStrategy>
	template <typename __T, typename __Counter, typename __DelStrategy>
	inline bool SharedPtrWrapper<T, Counter, DelStrategy>::operator >= (const SharedPtrWrapper<__T, __Counter, __DelStrategy> & right) const
	{
		LogTrace("bool SharedPtrWrapper<T, Counter, DelStrategy>::operator >= (const SharedPtrWrapper<__T, __Counter, __DelStrategy> & right) const");
		LogTraceReturn(m_objPtr >= right.m_objPtr);
	}



	template <typename T, typename Counter, typename DelStrategy>
	inline void SharedPtrWrapper<T, Counter, DelStrategy>::check_delete_ptr()
	{
		LogTrace("void SharedPtrWrapper<T, Counter, DelStrategy>::check_delete_ptr()");
		if (m_refControl == NULL)
		{
			LogTraceReturnVoid;
		}
		m_refControl->dec_shared();
		if (m_refControl->get_shared_refs() == 0)
		{
			DelStrategy::release(m_objPtr);
		}
		if (!m_refControl->has_refs())
		{
			delete m_refControl;
		}
		reset_no_delete();
		LogTraceReturnVoid;
	}


	template <typename T, typename Counter, typename DelStrategy>
	inline void SharedPtrWrapper<T, Counter, DelStrategy>::reset_no_delete()
	{
		LogTrace("void SharedPtrWrapper<T, Counter, DelStrategy>::reset_no_delete()");
		m_objPtr = NULL;
		m_refControl = NULL;
		LogTraceReturnVoid;
	}

	template <typename T, typename Counter, typename DelStrategy>
	inline void SharedPtrWrapper<T, Counter, DelStrategy>::reset_ref_counter(T * ptr, Counter * cntr)
	{
		LogTrace("void SharedPtrWrapper<T, Counter, DelStrategy>::reset_ref_counter(T * ptr, Counter * cntr)");
		m_objPtr = ptr;
		m_refControl = cntr;
		LogTraceReturnVoid;
	}

	template <typename T, typename Counter, typename DelStrategy>
	inline void SharedPtrWrapper<T, Counter, DelStrategy>::set_ptr(T * ptr)
	{
		LogTrace("void SharedPtrWrapper<T, Counter, DelStrategy>::set_ptr(T * ptr)");
		m_refControl = new Counter();
		m_objPtr = ptr;
		LogTraceReturnVoid;
	}


	/////////////////////////////////////////////////////////////////////////
	//Ptr operator
	////////////////////////////////////////////////////////////////////////
	template <typename T, typename Counter, typename DelStrategy>
	inline bool operator == (const SharedPtrWrapper<T, Counter, DelStrategy> & left, T * right)
	{
		LogTrace("bool operator == (const SharedPtrWrapper<T, Counter, DelStrategy> & left, T * right)");
		LogTraceReturn(left->get() == right);
	}

	template <typename T, typename Counter, typename DelStrategy>
	inline bool operator == (T * left, const SharedPtrWrapper<T, Counter, DelStrategy> & right)
	{
		LogTrace("bool operator == (T * left, const SharedPtrWrapper<T, Counter, DelStrategy> & right)");
		LogTraceReturn(left == right->get());
	}

	template <typename T, typename Counter, typename DelStrategy>
	inline bool operator != (const SharedPtrWrapper<T, Counter, DelStrategy> & left, T * right)
	{
		LogTrace("bool operator != (const SharedPtrWrapper<T, Counter, DelStrategy> & left, T * right)");
		LogTraceReturn(left->get() != right);
	}

	template <typename T, typename Counter, typename DelStrategy>
	inline bool operator != (T * left,const SharedPtrWrapper<T, Counter, DelStrategy> & right)
	{
		LogTrace("bool operator != (T * left,const SharedPtrWrapper<T, Counter, DelStrategy> & right)");
		LogTraceReturn(left == right->get());
	}


	///////////////////////////////////////////////////////////////////////
	//WeakPtr
	//////////////////////////////////////////////////////////////////////
	template <typename T, typename Counter, typename DelStrategy>
	WeakPtrWrapper<T, Counter, DelStrategy>::WeakPtrWrapper() : m_objPtr(NULL), m_refControl(NULL)
	{
		LogTrace("WeakPtrWrapper<T, Counter, DelStrategy>::WeakPtrWrapper()");
		LogTraceReturnVoid;
	}

	template <typename T, typename Counter, typename DelStrategy>
	WeakPtrWrapper<T, Counter, DelStrategy>::WeakPtrWrapper(const SharedPtrWrapper<T, Counter, DelStrategy> & spw) : 
		m_objPtr(spw.m_objPtr), m_refControl(spw.m_refControl)
	{
		LogTrace("WeakPtrWrapper<T, Counter, DelStrategy>::WeakPtrWrapper(const SharedPtrWrapper<T, Counter, DelStrategy> & spw)");
		m_refControl->inc_weak();
		LogTraceReturnVoid;
	}

	template <typename T, typename Counter, typename DelStrategy>
	WeakPtrWrapper<T, Counter, DelStrategy>::WeakPtrWrapper(const WeakPtrWrapper<T, Counter, DelStrategy> & cp) : 
		m_objPtr(cp.m_objPtr), m_refControl(cp.m_refControl)
	{
		LogTrace("WeakPtrWrapper<T, Counter, DelStrategy>::WeakPtrWrapper(const WeakPtrWrapper<T, Counter, DelStrategy> & cp)");
		m_refControl->inc_weak();
		LogTraceReturnVoid;
	}

	template <typename T, typename Counter, typename DelStrategy>
	WeakPtrWrapper<T, Counter, DelStrategy> & WeakPtrWrapper<T, Counter, DelStrategy>::operator = (const WeakPtrWrapper<T, Counter, DelStrategy> & right)
	{
		LogTrace("WeakPtrWrapper<T, Counter, DelStrategy> & WeakPtrWrapper<T, Counter, DelStrategy>::operator = (const WeakPtrWrapper<T, Counter, DelStrategy> & right)");
		if (this == &right) { LogTraceReturn((*this)); }
		m_objPtr = right.m_objPtr;
		m_refControl = right.m_refControl;
		m_refControl->inc_weak();
		LogTraceReturn((*this));
	}


	template <typename T, typename Counter, typename DelStrategy>
	template <typename __T, typename __Counter, typename __DelStrategy>
	WeakPtrWrapper<T, Counter, DelStrategy>::WeakPtrWrapper(const SharedPtrWrapper<__T, __Counter, __DelStrategy> & spw) : 
		m_objPtr(spw.m_objPtr), m_refControl(spw.m_refControl)
	{
		LogTrace("WeakPtrWrapper<T, Counter, DelStrategy>::WeakPtrWrapper(const SharedPtrWrapper<__T, __Counter, __DelStrategy> & spw)");
		m_refControl->inc_weak();
		LogTraceReturnVoid;
	}


	template <typename T, typename Counter, typename DelStrategy>
	template <typename __T, typename __Counter, typename __DelStrategy>
	WeakPtrWrapper<T, Counter, DelStrategy> & WeakPtrWrapper<T, Counter, DelStrategy>::operator = (const WeakPtrWrapper<__T, __Counter, __DelStrategy> & right)
	{
		LogTrace("WeakPtrWrapper<T, Counter, DelStrategy> & WeakPtrWrapper<T, Counter, DelStrategy>::operator = (const WeakPtrWrapper<__T, __Counter, __DelStrategy> & right)");
		if (this == &right) { LogTraceReturn((*this)); }
		m_objPtr = right.m_objPtr;
		m_refControl = right.m_refControl;
		m_refControl->inc_weak();
		LogTraceReturn((*this));
	}


	template <typename T, typename Counter, typename DelStrategy>
	template <typename __T, typename __Counter, typename __DelStrategy>
	WeakPtrWrapper<T, Counter, DelStrategy>::WeakPtrWrapper(const WeakPtrWrapper<__T, __Counter, __DelStrategy> & cp) : 
		m_objPtr(cp.m_objPtr), m_refControl(cp.m_refControl)
	{
		LogTrace("WeakPtrWrapper<T, Counter, DelStrategy>::WeakPtrWrapper(const WeakPtrWrapper<__T, __Counter, __DelStrategy> & cp)");
		m_refControl->inc_weak();
		LogTraceReturnVoid;
	}


	template <typename T, typename Counter, typename DelStrategy>
	WeakPtrWrapper<T, Counter, DelStrategy>::~WeakPtrWrapper()
	{
		LogTrace("WeakPtrWrapper<T, Counter, DelStrategy>::~WeakPtrWrapper()");
		check_delete_ptr();
		LogTraceReturnVoid;
	}


	template <typename T, typename Counter, typename DelStrategy>
	inline void WeakPtrWrapper<T, Counter, DelStrategy>::reset()
	{
		LogTrace("void WeakPtrWrapper<T, Counter, DelStrategy>::reset()");
		check_delete_ptr();
		LogTraceReturnVoid;
	}

	template <typename T, typename Counter, typename DelStrategy>
	inline void WeakPtrWrapper<T, Counter, DelStrategy>::swap(WeakPtrWrapper<T, Counter, DelStrategy> & right)
	{
		LogTrace("void WeakPtrWrapper<T, Counter, DelStrategy>::swap(WeakPtrWrapper<T, Counter, DelStrategy> & right)");
		if (this == &right) { LogTraceReturnVoid; }
		T * tempPtr = m_objPtr;
		Counter * tempControl = m_refControl;
		m_objPtr = right.m_objPtr;
		m_refControl = right.m_refControl;
		right.m_objPtr = tempPtr;
		right.m_refControl = tempControl;
		LogTraceReturnVoid;
	}

	template <typename T, typename Counter, typename DelStrategy>
	inline int64 WeakPtrWrapper<T, Counter, DelStrategy>::use_count() const
	{
		LogTrace("int64 WeakPtrWrapper<T, Counter, DelStrategy>::use_count() const");
		if (m_refControl == NULL)
		{
			LogTraceReturn(0);
		}
		LogTraceReturn(m_refControl->get_shared_refs());
	}

	template <typename T, typename Counter, typename DelStrategy>
	inline bool WeakPtrWrapper<T, Counter, DelStrategy>::expired() const
	{
		LogTrace("bool WeakPtrWrapper<T, Counter, DelStrategy>::expired() const");
		if (m_refControl == NULL)
		{
			LogTraceReturn(true);
		}
		LogTraceReturn(m_refControl->get_shared_refs() == 0);
	}


	template <typename T, typename Counter, typename DelStrategy>
	inline SharedPtrWrapper<T, Counter, DelStrategy> WeakPtrWrapper<T, Counter, DelStrategy>::lock() const
	{
		LogTrace("SharedPtrWrapper<T, Counter, DelStrategy> WeakPtrWrapper<T, Counter, DelStrategy>::lock() const");
		if (expired())
		{
			LogTraceReturn((SharedPtrWrapper<T, Counter, DelStrategy>()));
		}
		LogTraceReturn((SharedPtrWrapper<T, Counter, DelStrategy>(*this)));
	}

	
	template <typename T, typename Counter, typename DelStrategy>
	inline void WeakPtrWrapper<T, Counter, DelStrategy>::check_delete_ptr()
	{
		LogTrace("void WeakPtrWrapper<T, Counter, DelStrategy>::check_delete_ptr()");
		m_refControl->dec_weak();
		if (!m_refControl->has_refs())
		{
			delete m_refControl;
		}
		reset_no_delete();
		LogTraceReturnVoid;
	}
		
	template <typename T, typename Counter, typename DelStrategy>
	inline void WeakPtrWrapper<T, Counter, DelStrategy>::reset_no_delete()
	{
		LogTrace("void WeakPtrWrapper<T, Counter, DelStrategy>::reset_no_delete()");
		m_objPtr = NULL;
		m_refControl = NULL;
		LogTraceReturnVoid;
	}


}

#endif