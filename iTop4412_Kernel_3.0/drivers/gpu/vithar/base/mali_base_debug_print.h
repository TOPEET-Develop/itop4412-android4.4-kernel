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
 * @file mali_base_debug_print.h
 * Base's equivalent of Debug Messaging, which is copied and
 * renamed from the CDBG module
 */

#ifndef _BASE_DEBUG_PRINT_H_
#define _BASE_DEBUG_PRINT_H_

/**
 * @addtogroup base_api
 * @{
 */

/**
 * @addtogroup base_user_api
 * @{
 */

/**
 * @addtogroup base_user_api_debug
 * @{
 */


/*
 * List of BDBG macros/functions:
 * 
 */

/**
 * @brief prints a message to one of the important channel (error /assert / warning)
 *
 * @param channel_idx output channel index: @ref CDBG_OUTPUT_ERROR, @ref CDBG_OUTPUT_WARN or @ref CDBG_OUTPUT_INFO.
 * @param type message type: "INFO", "WARN", etc.
 * @param module module printing the message. See @ref cdbgp_module_to_str (u32 id) to convert a module id into string.
 * @param trace location in the code from where this message is printed.
 * @param func function from where the message is printed
 * @param msg message to print
 * @param ...  Arguments to display.
 */
void bdbgp_print_to_important_channel(u32 channel_idx, const char* type, const char* module, const char* trace, const char* func,
		const char* msg, ...);

/**
 * @brief prints a message to the info channel.
 *
 * The message displayed is much shorter than the one displayed by @ref bdbgp_print_to_important_channel.
 *
 * @param func Function from where the message is printed
 * @param msg  Message to print.
 * @param ...  Arguments to display.
 */
void bdbgp_print_to_info_channel(const char* func,const char* msg, ...);


/**
 * @def   BDBG_PRINT_INFO(module, ...)
 * @brief Prints "INFO" followed by a module name and the given message.
 *
 * The behavior of this function is defined by the macros @ref CDBG_ON_INFO, @ref CDBG_OUTPUT_INFO
 *
 * Example: @code BDBG_PRINT_INFO(CDBG_BASE, " %d blocks could not be allocated", mem_allocated); @endcode will print: 
 * \n
 * "==>[INFO] BASE: In file: <filename>  function: <function>   line: <line>\n
 * 10 blocks could not be allocated"\n
 *
 * @note Depending on the values of @ref CDBG_SKIP_FUNCTION_NAME and @ref CDBG_SKIP_TRACE the trace will be displayed
 * before the message.
 *
 * @param module   Name of the module which prints the message.
 * @param ...      Format string followed by a varying number of parameters
 */
#define BDBG_PRINT_INFO(module, ...)\
	do\
	{\
		if(MALI_FALSE != BDBGP_PRINT_IS_ALLOWED( (module), CDBG_CHANNEL_INFO))\
		{\
			BDBGP_INFO(cdbgp_module_to_str( (module) ), CDBGP_PRINT_TRACE, CDBGP_PRINT_FUNCTION, __VA_ARGS__ );\
		}\
		CDBGP_INFO_ACTION();\
	}while(MALI_FALSE)

/**
 * @def   BDBG_PRINT_WARN(module, ...)
 * @brief Prints "WARN" followed by a module name and the given message.
 *
 * The behavior of this function is defined by the macros @ref CDBG_ON_WARN, @ref CDBG_OUTPUT_WARN
 *
 * Example: @code BDBG_PRINT_WARN(CDBG_BASE, " %d blocks could not be allocated", mem_allocated);@endcode will print: \n
 * "==>[WARN] BASE: In file: <filename>  function: <function>   line: <line>\n
 * 10 blocks could not be allocated"\n
 *
 * @note Depending on the values of @ref CDBG_SKIP_FUNCTION_NAME and @ref CDBG_SKIP_TRACE the trace will be displayed
 * before the message.
 *
 * @param module   Name of the module which prints the message.
 * @param ...      Format string followed by a varying number of parameters
 */
#define BDBG_PRINT_WARN(module, ...)\
	do\
	{\
		if(MALI_FALSE != BDBGP_PRINT_IS_ALLOWED( (module), CDBG_CHANNEL_WARN))\
		{\
			BDBGP_WARN(cdbgp_module_to_str( (module) ), CDBGP_PRINT_TRACE, CDBGP_PRINT_FUNCTION,  __VA_ARGS__);\
		}\
		CDBGP_WARN_ACTION();\
	}while(MALI_FALSE)

/**
 * @def BDBG_PRINT_ERROR(module, ...)
 * @brief Prints "ERROR" followed by a module name and the given message.
 *
 * The behavior of this function is defined by the macros @ref CDBG_ON_ERROR, @ref CDBG_OUTPUT_ERROR
 *
 * Example: @code BDBG_PRINT_ERROR(CDBG_BASE, " %d blocks could not be allocated", mem_allocated); @endcode will print: 
 * \n
 * "==>[ERROR] BASE: In file: <filename>  function: <function>   line: <line>\n
 * 10 blocks could not be allocated"\n
 *
 * @note Depending on the values of @ref CDBG_SKIP_FUNCTION_NAME and @ref CDBG_SKIP_TRACE the trace will be displayed
 * before the message.
 *
 * @param module   Name of the module which prints the message.
 * @param ...      Format string followed by a varying number of parameters
  */
#define BDBG_PRINT_ERROR(module, ...)\
	do\
	{\
		if(MALI_FALSE != BDBGP_PRINT_IS_ALLOWED( (module), CDBG_CHANNEL_ERROR))\
		{\
			BDBGP_ERROR(cdbgp_module_to_str( (module) ), CDBGP_PRINT_TRACE, CDBGP_PRINT_FUNCTION, __VA_ARGS__ );\
		}\
		CDBGP_ERROR_ACTION();\
	}while(MALI_FALSE)


/**
 * @brief Calls @ref BDBG_PRINT_INFO if @a expr is true
 *
 * @param expr   expression to evaluate, if it is true then the INFO message is printed
 * @param module name of the module calling the macro
 * @param ...	 message to display if @a expr is true, passed as a format string followed by format arguments.
 */
#define BDBG_PRINT_INFO_ON(expr, module, ...)\
	CDBGP_ON(BDBG_PRINT_INFO, (expr), (module), __VA_ARGS__)
/**
 * @brief Calls @ref BDBG_PRINT_WARN if @a expr is true
 *
 * @param expr   expression to evaluate, if it is true then the WARN message is printed
 * @param module name of the module calling the macro
 * @param ...	 message to display if @a expr is true, passed as ai format string followed by format arguments.
 */
#define BDBG_PRINT_WARN_ON(expr, module, ...)\
	CDBGP_ON(BDBG_PRINT_WARN, (expr), (module), __VA_ARGS__)
/**
 * @brief Calls @ref BDBG_PRINT_ERROR if @a expr is true
 *
 * @param expr   expression to evaluate, if it is true then the ERROR message is printed
 * @param module name of the module calling the macro
 * @param ...	 message to display if @a expr is true, passed as ai format string followed by format arguments.
 */
#define BDBG_PRINT_ERROR_ON(expr, module, ...)\
	CDBGP_ON(BDBG_PRINT_ERROR, (expr), (module), __VA_ARGS__)

/**
 * @def BDBGP_PRINT_IS_ALLOWED(module, channel)
 * @brief function or constant indicating if the given module is allowed to print on the given channel
 * @param module is a @ref cdbg_module
 * @param channel is one of @ref CDBG_CHANNEL_INFO, @ref CDBG_CHANNEL_WARN, @ref CDBG_CHANNEL_ERROR,
 * @ref CDBG_CHANNEL_ALL
 * @return MALI_TRUE if the module is allowed to print on the channel.
 */
#define BDBGP_PRINT_IS_ALLOWED(module, channel) MALI_TRUE

/**
 * @def BDBGP_INFO(module, trace, ...)
 * @brief (Private) system printing function associated to the @ref BDBG_PRINT_INFO event.
 * @param module module ID
 * @param trace location in the code from where the message is printed
 * @param function function from where the message is printed
 * @param ... Format string followed by format arguments.
 */
/* Select the correct system output function*/
#if CDBG_ON_INFO != CDBG_ACTION_IGNORE
	#define BDBGP_INFO(module, trace, function, ...) bdbgp_print_to_info_channel(function, __VA_ARGS__)
#else
	#define BDBGP_INFO(module, trace, function, ...) CSTD_NOP()
#endif

/**
 * @def BDBGP_WARN(module, trace, ...)
 * @brief (Private) system printing function associated to the @ref BDBG_PRINT_WARN event.
 * @param module module ID
 * @param trace location in the code from where the message is printed
 * @param function function from where the message is printed
 * @param ... Format string followed by format arguments.
 */
/* Select the correct system output function*/
#if CDBG_ON_WARN != CDBG_ACTION_IGNORE
	#define BDBGP_WARN(module, trace, function, ...) bdbgp_print_to_important_channel(CDBG_OUTPUT_WARN, "WARN",	\
		       	(module), (trace), (function), __VA_ARGS__)
#else
	#define BDBGP_WARN(module, trace, function, ...) CSTD_NOP()
#endif

/**
 * @def BDBGP_ASSERT(module, trace, ...)
 * @brief (Private) system printing function associated to the @ref BDBGP_PRINT_ASSERT event.
 * @param module module ID
 * @param trace location in the code from where the message is printed
 * @param function function from where the message is printed
 * @param ... Format string followed by format arguments.
 */
/* Select the correct system output function*/
#if CDBG_ON_ASSERT != CDBG_ACTION_IGNORE
	#define BDBGP_ASSERT(module, trace, function, ...) bdbgp_print_to_important_channel(0, "ASSERT", (module), (trace), (function), __VA_ARGS__)
#else
	#define BDBGP_ASSERT(module, trace, function, ...) CSTD_NOP()
#endif

/**
 * @def BDBGP_ERROR(module, trace, ...)
 * @brief (Private) system printing function associated to the @ref BDBG_PRINT_ERROR event.
 * @param module module ID
 * @param trace location in the code from where the message is printed
 * @param function function from where the message is printed
 * @param ... Format string followed by format arguments.
 */
/* Select the correct system output function*/
#if CDBG_ON_ERROR != CDBG_ACTION_IGNORE
	#define BDBGP_ERROR(module, trace, function, ...) bdbgp_print_to_important_channel(CDBG_OUTPUT_ERROR, "ERROR",\
		       (module), (trace), (function), __VA_ARGS__)
#else
	#define BDBGP_ERROR(module, trace, function, ...)  CSTD_NOP()
#endif





/** @} end group base_user_api_debug */
/** @} end group base_user_api */
/** @} end group base_api */

#endif /* _BASE_DEBUG_PRINT_H_ */
