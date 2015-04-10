/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2010-2011 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */

/**
 * @file mali_base_debug.h
 * Base's equivalent of Debug Asserts and Messaging, which is copied and
 * renamed from the CDBG module.
 */

#ifndef _BASE_DEBUG_H_
#define _BASE_DEBUG_H_

#include <cdbg/mali_cdbg.h>
#include <base/mali_base_debug_print.h>

/**
 * @addtogroup base_api
 * @{
 */

/**
 * @addtogroup base_user_api
 * @{
 */

/**
 * @defgroup base_user_api_debug Base Debug Asserts and Messaging
 *
 * Base's equivalent of Debug Asserts and Messaging, which is copied and
 * renamed from the CDBG module.
 *
 * These provide a way of making asserts and debug messages without causing
 * re-entrancy issues into Base Portable Debug Channels, or any modules used by
 * Base Portable Debug Channels. However, the messaging provided is restricted,
 * and is not guarenteed to give the correct output when multiple threads are
 * writing, and so most modules should not use BDBG macros.
 *
 * The modules that must only use BDBG macros, and not CDBG macros are:
 * - Base Portable Debug Channels
 * - Stdlib
 * - OSU
 * - CUTILS::Ringbuffer
 *
 * BDBG macros prevent re-entrancy by not calling into any of the above modules,
 * <b>strictly except for these two case</b>:
 * - Base Portable Debug Channels for base_channel_emergency_message()
 * - CUTILS for cutils_cstr_snprintf()
 *
 * Therefore, those two functions above are prohibited from using most BDBG or
 * CDBG macros, but can use:
 * - BDBG_INTERNAL_ASSERT
 * - CDBG_COMPILE_ASSERT
 *
 * @{
 * @}
 */

/**
 * @addtogroup base_user_api_debug
 * @{
 */

/*
 * Wrappers for BDBG_<...> module identifiers
 */
/** @brief BDBG modules ID of Unknown module */
#define BDBG_UNKNOWN CDBG_UNKNOWN
/** @brief BDBG modules ID of Base  */
#define BDBG_BASE    CDBG_BASE
/** @brief BDBG modules ID of Common Utilities */
#define BDBG_CUTILS  CDBG_CUTILS
/** @brief BDBG modules ID of Base Operating System User */
#define BDBG_OSU     CDBG_OSU
/** @brief BDBG modules ID of Base Standard Library */
#define BDBG_STDLIB  CDBG_STDLIB

/**
 * @def BDBG_ASSERT_MSG(expr, ...)
 * @brief Calls @ref BDBGP_PRINT_ASSERT and prints the given message if @a expr is false
 *
 * @note This macro does nothing if the flag @ref CDBG_DISABLE_ASSERTS is set to 1
 *
 * @param expr Boolean expression
 * @param ...  Message to display when @a expr is false, as a format string followed by format arguments.
 */
#if CDBG_DISABLE_ASSERTS
	#define BDBG_ASSERT_MSG(expr, ...) CSTD_NOP()
#else
	#define BDBG_ASSERT_MSG(expr, ...)\
		do\
		{\
			if(MALI_FALSE ==  (expr))\
			{\
				BDBGP_PRINT_ASSERT(__VA_ARGS__);\
			}\
		}while(MALI_FALSE)
#endif
/**
 * @def BDBG_ASSERT(expr)
 * @brief Calls @ref BDBGP_PRINT_ASSERT and prints the expression @a expr if @a expr is false
 *
 * @note This macro does nothing if the flag @ref CDBG_DISABLE_ASSERTS is set to 1
 *
 * @param expr Boolean expression
 */
#if CDBG_DISABLE_ASSERTS
	#define BDBG_ASSERT(expr) CSTD_NOP()
#else
	#define BDBG_ASSERT(expr)\
		BDBG_ASSERT_MSG(expr, #expr)
#endif
/**
 * @def BDBG_ASSERT_POINTER(ptr)
 * @brief Calls @ref BDBGP_PRINT_ASSERT if the pointer @a ptr is NULL.
 *
 * @note This macro does nothing if the flag @ref CDBG_DISABLE_ASSERTS is set to 1
 *
 * @param ptr Pointer to test
 */
#if CDBG_DISABLE_ASSERTS
	#define BDBG_ASSERT_POINTER(ptr) CSTD_NOP()
#else
	#define BDBG_ASSERT_POINTER(ptr)\
		BDBG_ASSERT_MSG( NULL != (ptr), "\"%s\" is NULL", #ptr)
#endif
/**
 * @def BDBG_ASSERT_ALIGNMENT(ptr, align)
 * @brief Tests if a pointer is correctly aligned, if not @ref BDBGP_PRINT_ASSERT is called
 *
 * @note This macro does nothing if the flag @ref CDBG_DISABLE_ASSERTS is set to 1
 *
 * @param ptr     Pointer to test
 * @param align   Alignment to which the pointer should be aligned.
 * @note The alignment should be a power of two, otherwise @ref BDBGP_PRINT_ASSERT is called
 */
#if CDBG_DISABLE_ASSERTS
	#define BDBG_ASSERT_ALIGNMENT(ptr, align) CSTD_NOP()
#else
	#define BDBG_ASSERT_ALIGNMENT(ptr, align)\
		do\
		{\
			BDBG_ASSERT(0 < align);\
			BDBG_ASSERT_MSG(0 == ( (align) & ((align) - 1)), ("align %d is not a power-of-two", (s32) (align)));\
			BDBG_ASSERT_MSG(0 == (((uintptr_t)(ptr)) & ((align) - 1)), \
				       ("ptr %p not aligned to %d bytes", (void*)(ptr), (int) (align)));\
		} while(MALI_FALSE)
#endif
/**
 * @def BDBG_ASSERT_RANGE(x, min, max)
 * @brief Calls @ref BDBGP_PRINT_ASSERT if the value of @a x is out of the interval [@a min, @a max].
 *
 * @note This macro does nothing if the flag @ref CDBG_DISABLE_ASSERTS is set to 1
 *
 */
#if CDBG_DISABLE_ASSERTS
	#define BDBG_ASSERT_RANGE(x, min, max) CSTD_NOP()
#else
	#define BDBG_ASSERT_RANGE(x, min, max)\
		BDBG_ASSERT_MSG((x) >= (min) && (x) <= (max), \
			#x " (%2.2f) out of the range [%2.2f, %2.2f]", (float)(x), (float)(min), (float)(max))
#endif
/**
 * @def BDBG_ASSERT_LEQ(x, max)
 * @brief Calls @ref BDBGP_PRINT_ASSERT if the value of @a x is strictly greater than @a max.
 *
 * @note This macro does nothing if the flag @ref CDBG_DISABLE_ASSERTS is set to 1
 *
 */
#if CDBG_DISABLE_ASSERTS
	#define BDBG_ASSERT_LEQ(x, max) CSTD_NOP()
#else
	#define BDBG_ASSERT_LEQ(x, max)\
		BDBG_ASSERT_MSG((x) <= (max), \
			#x " (%2.2f) out of range (greater than %2.2f)", (float)(x), (float)(max))
#endif


/**
 * @def BDBG_CHECKABLE_ASSERT_RETURN( expr )
 * @brief if expr is false then the counter of failed tests
 * will be incremented and  the function will return.
 *
 * @note if @ref CDBG_DISABLE_ASSERTS is enabled this macro does nothing.
 * @note if CDBG_API_CHECK is disabled then an error is triggered if expr is false.
 *
 * @param expr The expression to evaluate
 */
/**
 * @def BDBG_CHECKABLE_ASSERT_RETURN_VAL( expr, return_value)
 * @brief if expr is false then the counter of failed checks
 * will be incremented and the function will return the given value.
 *
 * @note if @ref CDBG_DISABLE_ASSERTS is enabled this macro does nothing.
 * @note if CDBG_API_CHECK is disabled then an error is triggered if expr is false.
 *
 * @param expr The expression to evaluate
 * @param return_value value to return if expr is false.
 */
/** @def BDBG_CHECKABLE_ASSERT_CLEANUP( expr, goto_label)
 * @brief if expr is false then the counter of failed tests
 * will be incremented and the execution will jump to goto_label.
 *
 * @note if @ref CDBG_DISABLE_ASSERTS is enabled this macro does nothing.
 * @note if CDBG_API_CHECK is disabled then an error is triggered if expr is false.
 *
 * @param expr The expression to evaluate
 * @param goto_label label to jump to if expr is false.
 */
/* <!-- This function not declared - removed from doxygen -->
 * @fn mali_bool cdbg_get_check_failed_and_reset()
 * @brief return MALI_TRUE if at least one of the tests performed by @ref BDBG_CHECKABLE_ASSERT_RETURN, @ref BDBG_CHECKABLE_RETURN_VAL or
 * @ref BDBG_CHECKABLE_ASSERT_CLEANUP failed and reinitialize the variable to MALI_FALSE
 *
 * @note This function only exists if @ref CDBG_DISABLE_ASSERTS is disabled and CDBG_API_CHECK enabled.
 */
#if !CDBG_DISABLE_ASSERTS
#if CDBG_API_CHECK
	#define BDBG_CHECKABLE_ASSERT_RETURN( expr ) \
		do\
		{\
			if (! (expr) ) \
			{ \
				cdbgp_check_failed();\
				return;\
		       	} \
		}while(MALI_FALSE)

	#define BDBG_CHECKABLE_ASSERT_RETURN_VAL( expr, return_value ) \
		do\
		{ \
			if (! (expr) ) \
			{ \
				cdbgp_check_failed();\
				return (return_value); \
			} \
		}while(MALI_FALSE)

	#define BDBG_CHECKABLE_ASSERT_CLEANUP( expr, goto_label ) \
		do \
		{ \
			if (! (expr) ) \
			{ \
				cdbgp_check_failed();\
				goto goto_label ;\
			} \
		}while(MALI_FALSE)
#else
	#define BDBG_CHECKABLE_ASSERT_RETURN( expr ) \
		BDBG_ASSERT_MSG((expr), "Checkable ASSERT: "#expr" was false")

	#define BDBG_CHECKABLE_ASSERT_RETURN_VAL( expr, return_value ) \
		BDBG_ASSERT_MSG((expr), "Checkable ASSERT: "#expr" was false")

	#define BDBG_CHECKABLE_ASSERT_CLEANUP( expr, goto_label ) \
		BDBG_ASSERT_MSG((expr), "Checkable ASSERT: "#expr" was false")
#endif /* CDBG_API_CHECK */
#else

	#define BDBG_CHECKABLE_ASSERT_RETURN( expr )  CSTD_NOP()
	#define BDBG_CHECKABLE_ASSERT_RETURN_VAL( expr, return_value )  CSTD_NOP()
	#define BDBG_CHECKABLE_ASSERT_CLEANUP( expr, goto_label ) CSTD_NOP()
#endif /* CDBG_DISABLE_ASSERTS */


/**
 * @def   BDBGP_PRINT_ASSERT(...)
 * @brief Prints "ASSERT" followed by the given message.
 *
 * The behavior of this function is defined by the macros @ref CDBG_ON_ASSERT
 *
 * @note This macro does nothing if the flag @ref CDBG_DISABLE_ASSERTS is set to 1
 *
 * Example:  BDBGP_PRINT_ASSERT(" %d blocks could not be allocated", mem_alocated) will print:\n
 * "ASSERT: 10 blocks could not be allocated"
 *
 * @note Depending on the values of @ref CDBG_SKIP_FUNCTION_NAME and @ref CDBG_SKIP_TRACE the trace will be displayed
 * before the message.
 *
 * @param ...      Message to print, passed as a format string followed by format arguments.  */
#if CDBG_DISABLE_ASSERTS
	#define BDBGP_PRINT_ASSERT(...) CSTD_NOP()
#else
	#define BDBGP_PRINT_ASSERT(...)\
		do\
		{\
			BDBGP_ASSERT("", CDBGP_PRINT_TRACE, CDBGP_PRINT_FUNCTION, __VA_ARGS__);\
			CDBGP_ASSERT_ACTION();\
		}while(MALI_FALSE)
#endif

/**
 * @def BDBG_INTERNAL_ASSERT(expr)
 * @brief Allows functions used by BDBG to make simplified asserts. No message
 * can be printed out.
 *
 * Functions used by BDBG macros must not make a call to a BDBG macro, because
 * a re-entrancy problem would occur. For example, CUTILS CStr functions are
 * used by BDBG, and so must not call BDBG macros, otherwise the CStr function
 * will be called recursively.
 *
 * Instead, the BDBG_INTERNAL_ASSERT() macro can be used in these cases,
 * which does not call into any other modules other than to stdlib_abort().
 *
 * @note This macro does nothing if the flag @ref CDBG_DISABLE_ASSERTS is set to 1
 *
 * @param expr Boolean expression
 */
#if CDBG_DISABLE_ASSERTS
	#define BDBG_INTERNAL_ASSERT(expr) CSTD_NOP()
#else
#define BDBG_INTERNAL_ASSERT(expr)                          \
	do                                                      \
	{                                                       \
		if(MALI_FALSE ==  (expr))                           \
		{                                                   \
			CDBGP_ASSERT_ACTION();                          \
		}                                                   \
	}while(MALI_FALSE)
#endif

/**
 * @def BDBG_SET_FAIL_OFF()
 * @brief Disables simulation of failures for the code between \c BDBG_SET_FAIL_OFF and @ref BDBG_SET_FAIL_ON
 * All the @ref BDBG_SIMULATE_FAILURE calls evaluate to @ref MALI_FALSE between @ref BDBG_SET_FAIL_OFF @ref BDBG_SET_FAIL_OFF
 * 
 * This feature is useful where one wants to manually disable simulated failures in certain parts of code that are not
 * part of the driver itself (e.g. glue code to a platform simulator that uses the platform independent APIs such
 * as OSU).
 * 
 * Another use is to prevent failure simulation for the portion of code where an issue is found, until the issue is fixed 
 * so that one can proceed with further testing.
 *
 * Should be used with caution as it might hide possible issues, ideally these should not be used.
 *
 * @note This macro does nothing if the flag @ref CDBG_SIMULATE_FAILURES is set to 0
 */
#if (CDBG_SIMULATE_FAILURES && (1 == MALI_BASE_TRACK_MEMLEAK) )
#define BDBG_SET_FAIL_OFF()                                              \
	do                                                                   \
	{                                                                    \
		uintptr_t temp =  (uintptr_t)osu_debug_failure_flag_get();       \
		osu_debug_failure_flag_set((void*)(temp+1));                     \
	}while(MALI_FALSE)
#else
#define BDBG_SET_FAIL_OFF() CSTD_NOP( )
#endif

/**
 * @def BDBG_SET_FAIL_ON()
 * @brief Re-enables the simulation of failures which are previously disabled using @ref BDBG_SET_FAIL_OFF
 * Should always be paired with @ref BDBG_SET_FAIL_OFF, and should not be used before disabling.
 *
 * @note This macro does nothing if the flag @ref CDBG_SIMULATE_FAILURES is set to 0
 */
#if (CDBG_SIMULATE_FAILURES && (1 == MALI_BASE_TRACK_MEMLEAK) )
#define BDBG_SET_FAIL_ON()                                               \
	do                                                                   \
	{                                                                    \
		uintptr_t temp =  (uintptr_t)osu_debug_failure_flag_get();       \
		temp = temp -1;                                                  \
		osu_debug_failure_flag_set((void*)(temp));                       \
	}while(MALI_FALSE)
#else
#define BDBG_SET_FAIL_ON() CSTD_NOP( )
#endif

/**
 * @def BDBG_IS_FAIL_ON()
 * @return MALI_TRUE if failure simulation is enabled and MALI_FALSE if not.
 *
 * @note This macro does nothing if the flag @ref CDBG_SIMULATE_FAILURES is set to 0
 */
#define BDBG_IS_FAIL_ON()  ( 0  == (u32)osu_debug_failure_flag_get() )

/**
 * @def BDBG_SIMULATE_FAILURE( module)
 * @brief Decide whether or not to simulate a failure in a given module
 * please refer to @ref CDBG_SIMULATE_FAILURE for usage.
 * In addition to CDBG failure feature ability to switch off and on of failure simulation is provided.
 * @note This macro does nothing if the flag @ref CDBG_SIMULATE_FAILURES is set to 0
 */
#if (CDBG_SIMULATE_FAILURES && (1 == MALI_BASE_TRACK_MEMLEAK) )
#define BDBG_SIMULATE_FAILURE( module)   ( BDBG_IS_FAIL_ON() && CDBG_SIMULATE_FAILURE( module ) )
#else
#define BDBG_SIMULATE_FAILURE( module ) \
            ( CSTD_NOP( module ), MALI_FALSE )
#endif

/** @} end group base_user_api_debug */
/** @} end group base_user_api */
/** @} end group base_api */

#endif /* _BASE_DEBUG_H_ */
