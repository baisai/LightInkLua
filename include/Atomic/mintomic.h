#ifndef __MINTOMIC_MINTOMIC_H__
#define __MINTOMIC_MINTOMIC_H__

#include "Common/Type.h"

#include "platform_detect.h"

#if MINT_COMPILER_MSVC
	#if MINT_TARGET_XBOX_360    // Xbox 360
		#include <xtl.h>
	#else                       // Windows
		#ifndef WIN32_LEAN_AND_MEAN
			#define WIN32_LEAN_AND_MEAN
		#endif
		#include <windows.h>
		#undef WIN32_LEAN_AND_MEAN
		#include <intrin.h>
	#endif
#endif


#ifdef __cplusplus
extern "C" {
#endif

#if MINT_COMPILER_MSVC
    
	//-------------------------------------
	//  Alignment
	//-------------------------------------
	#define MINT_DECL_ALIGNED(declaration, amt) __declspec(align(amt)) declaration


	//-------------------------------------
	//  Inlining
	//-------------------------------------
	#ifdef __cplusplus
	#define MINT_C_INLINE inline
	#else
	#define MINT_C_INLINE __inline
	#endif

	#define MINT_NO_INLINE __declspec(noinline)

	//-------------------------------------
	//  Thread local
	//-------------------------------------
	#define MINT_THREAD_LOCAL __declspec(thread)

	//--------------------------------------------------------------
	//  Platform-specific fences and atomic RMW operations
	//--------------------------------------------------------------
	#include "mintomic_msvc.h"

#elif MINT_COMPILER_GCC
	#include<pthread.h>
	#include <unistd.h>
	//-------------------------------------
	//  Alignment
	//-------------------------------------
	// Note: May not work on local variables.
	// http://gcc.gnu.org/bugzilla/show_bug.cgi?id=24691
	#define MINT_DECL_ALIGNED(declaration, amt) declaration __attribute__((aligned(amt)))


	//-------------------------------------
	//  Inlining
	//-------------------------------------
	#define MINT_C_INLINE static inline
	#define MINT_NO_INLINE __attribute__((noinline))


	//-------------------------------------
	//  Thread local
	//-------------------------------------
	#define MINT_THREAD_LOCAL __thread

	//-------------------------------------
	//  Thread IDs
	//-------------------------------------
	typedef size_t mint_tid_t;

	MINT_C_INLINE mint_tid_t mint_get_current_thread_id()
	{
		return (mint_tid_t) pthread_self();
	}


	//-------------------------------------
	//  Process IDs
	//-------------------------------------
	typedef pid_t mint_pid_t;

	MINT_C_INLINE mint_pid_t mint_get_current_process_id()
	{
		return getpid();
	}

	//-------------------------------------
	//  Sleep
	//-------------------------------------
	MINT_C_INLINE void mint_yield_hw_thread()
	{
		// Only implemented on x86/64
#if MINT_CPU_X86 || MINT_CPU_X64
		asm volatile("pause");
#endif
	}

	MINT_C_INLINE void mint_sleep_millis(int millis)
	{
		struct timespec ts;
		ts.tv_sec = millis / 1000;
		ts.tv_nsec = (millis % 1000) * 1000 * 1000;
		nanosleep(&ts, NULL);
	}

	
	//--------------------------------------------------------------
	//  Platform-specific fences and atomic RMW operations
	//--------------------------------------------------------------
	#if MINT_CPU_X86 || MINT_CPU_X64
		#include "mintomic_gcc_x86-64.h"
	#elif MINT_CPU_ARM
		#include "mintomic_gcc_arm.h"
	#endif
	
#else
    #error Unsupported platform!
#endif


//--------------------------------------------------------------
//  Pointer-sized atomic RMW operation wrappers
//--------------------------------------------------------------
#if MINT_PTR_SIZE == 4
    MINT_C_INLINE void *mint_load_ptr_relaxed(const mint_atomicPtr_t *object)
    {
        return (void *) mint_load_32_relaxed((const mint_atomic32_t *) object);
    }
    MINT_C_INLINE void mint_store_ptr_relaxed(mint_atomicPtr_t *object, void *desired)
    {
        mint_store_32_relaxed((mint_atomic32_t *) object, (size_t) desired);
    }
    MINT_C_INLINE void *mint_compare_exchange_strong_ptr_relaxed(mint_atomicPtr_t *object, void *expected, void *desired)
    {
        return (void *) mint_compare_exchange_strong_32_relaxed((mint_atomic32_t *) object, (size_t) expected, (size_t) desired);
    }
    MINT_C_INLINE void *mint_fetch_add_ptr_relaxed(mint_atomicPtr_t *object, ptrdiff_t operand)
    {
        return (void *) mint_fetch_add_32_relaxed((mint_atomic32_t *) object, operand);
    }
    MINT_C_INLINE void *mint_fetch_and_ptr_relaxed(mint_atomicPtr_t *object, size_t operand)
    {
        return (void *) mint_fetch_and_32_relaxed((mint_atomic32_t *) object, operand);
    }
    MINT_C_INLINE void *mint_fetch_or_ptr_relaxed(mint_atomicPtr_t *object, size_t operand)
    {
        return (void *) mint_fetch_or_32_relaxed((mint_atomic32_t *) object, operand);
    }
#elif MINT_PTR_SIZE == 8
    MINT_C_INLINE void *mint_load_ptr_relaxed(const mint_atomicPtr_t *object)
    {
        return (void *) mint_load_64_relaxed((const mint_atomic64_t *) object);
    }
    MINT_C_INLINE void mint_store_ptr_relaxed(mint_atomicPtr_t *object, void *desired)
    {
        mint_store_64_relaxed((mint_atomic64_t *) object, (size_t) desired);
    }
    MINT_C_INLINE void *mint_compare_exchange_strong_ptr_relaxed(mint_atomicPtr_t *object, void *expected, void *desired)
    {
        return (void *) mint_compare_exchange_strong_64_relaxed((mint_atomic64_t *) object, (size_t) expected, (size_t) desired);
    }
    MINT_C_INLINE void *mint_fetch_add_ptr_relaxed(mint_atomicPtr_t *object, ptrdiff_t operand)
    {
        return (void *) mint_fetch_add_64_relaxed((mint_atomic64_t *) object, operand);
    }
    MINT_C_INLINE void *mint_fetch_and_ptr_relaxed(mint_atomicPtr_t *object, size_t operand)
    {
        return (void *) mint_fetch_and_64_relaxed((mint_atomic64_t *) object, operand);
    }
    MINT_C_INLINE void *mint_fetch_or_ptr_relaxed(mint_atomicPtr_t *object, size_t operand)
    {
        return (void *) mint_fetch_or_64_relaxed((mint_atomic64_t *) object, operand);
    }
#else
    #error MINT_PTR_SIZE not set!
#endif


#ifdef __cplusplus
} // extern "C"
#endif

#endif // __MINTOMIC_MINTOMIC_H__
