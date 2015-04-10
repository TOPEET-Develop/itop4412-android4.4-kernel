/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2010-2011 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */

#ifndef _CINSTR_COMMON_H_
#define _CINSTR_COMMON_H_

#include <cinstr/mali_cinstr_version.h>
#include <cinstr/mali_cinstr_platform.h>
/**
 * \addtogroup cinstr_common Instrumentation Common
 * \{
 */


/**
 * Error codes
 */
typedef enum
{
	CINSTR_ERROR_SUCCESS,
	CINSTR_ERROR_UNKNOWN,
} cinstr_error_t;




/**
 * Profiling event data
 */
typedef struct
{
	u64 timestamp;
	u32 event_id;
	u32 data[5];
} cinstr_profiling_entry_t;



/**
 * Used to identify the features that are supported by the Midgard Instrumentation API that may be implemented and activated in the Driver and/or Instrumentation Plugin
 */
typedef enum
{
    /** Logging of debug messages
     */
    CINSTR_FEATURE_LOG_DEBUG    = 0x1,
    /** Logging of warning messages
     */
    CINSTR_FEATURE_LOG_WARNINGS = 0x2,
    /** Logging of error messages
     */
    CINSTR_FEATURE_LOG_ERRORS   = 0x4,
    /** Logging of API calls
     */
    CINSTR_FEATURE_LOG_API      = 0x8,

    /** The ability to interrupt execution of API functions
     */
    CINSTR_FEATURE_API_STUB     = 0x10,
    /** The ability to change the semantics of an API call at runtime
     */
    CINSTR_FEATURE_API_MANIP    = 0x20,

	/** Retrieve timeline profiling data
	 */
	CINSTR_FEATURE_TIMELINE_PROFILING = 0x40,

    /**
     * The listing of commands that comprise a closure of all information required
     * to re-perform the current job.
     */
    CINSTR_FEATURE_JOB_DUMP     = 0x100,

    /** Collection of harware performance counters on a per-tile basis
     */
    CINSTR_FEATURE_COUNTERS_HW_TILE = 0x1000,
    /** Collection of harware performance counters on a per-core basis
     */
    CINSTR_FEATURE_COUNTERS_HW_CORE = 0x2000,
    /** Collection of software performance counters
     */
    CINSTR_FEATURE_COUNTERS_SW_ALL  = 0x10000,

    /** Notifications each time a frame has completed */
    CINSTR_FEATURE_FRAME_COMPLETE = 0x100000,

    /** Notifications when apps are created and destroyed
     */
    CINSTR_FEATURE_APP_CREATE_DESTROY = 0x1000000
} cinstr_feature_t;


/**
 * The driver events for which the Instrumentation Plugin can receive data.
 */
typedef enum
{
    /** Triggered after a new app is created */
    CINSTR_EVENT_APP_CREATED,
    /** Triggered just before an app is destroyed */
    CINSTR_EVENT_APP_DESTROYED,

	/** Triggered when the processing of a single remder pass has completed on CPU */
    CINSTR_EVENT_RENDER_PASS_COMPLETE_CPU,

	/** Triggered when the processing of a single frame has completed on CPU */
    CINSTR_EVENT_FRAME_COMPLETE_CPU,

    /** Triggered when a render pass has completed on HW */
    CINSTR_EVENT_RENDER_PASS_COMPLETE,

	/** Triggered when the rendering of a single frame has completed on HW */
    CINSTR_EVENT_FRAME_COMPLETE,

    /** Triggered when a logging message classed as debug is ready */
    CINSTR_EVENT_LOG_DEBUG,
    /** Triggered when a logging message classed as a warning is ready */
    CINSTR_EVENT_LOG_WARNING,
    /** Triggered when a logging message classed as an error is ready */
    CINSTR_EVENT_LOG_ERROR,

    /** Triggered when an API function is entered */
    CINSTR_EVENT_API_CALL_ENTER,

    /** Triggered on return from an API function */
    CINSTR_EVENT_API_CALL_EXIT,

    /** Triggered when hardware counters have been received */
    CINSTR_EVENT_COUNTERS_HW,
    /** Triggered when software counters have been received */
    CINSTR_EVENT_COUNTERS_SW,
} cinstr_event_t;

/**
 * The level of log messages
 */
typedef enum
{
    /** Debug level logging */
    CINSTR_LOG_LEVEL_DEBUG,
    /** Warning level logging */
    CINSTR_LOG_LEVEL_WARNING,
    /** Error level logging */
    CINSTR_LOG_LEVEL_ERROR
} cinstr_log_level_t;


/** \private */
#define CINSTR_CLIENTAPI_COUNT 7

/**
 * The different client APIs which we can chose to enable/disable instrumentation
 * on.
 */
typedef enum
{
	/** Non-API specific */
	CINSTR_CLIENTAPI_COMMON = 0,

    /** EGL */
    CINSTR_CLIENTAPI_EGL  = 1,
    /** OpenGL ES */
    CINSTR_CLIENTAPI_GLES = 2,
    /** OpenVG */
    CINSTR_CLIENTAPI_VG   = 3,
    /** OpenCL */
    CINSTR_CLIENTAPI_CL   = 4,
    /** Open GL */
    CINSTR_CLIENTAPI_GL   = 5,
    /** DirectX */
    CINSTR_CLIENTAPI_DX   = 6,

	/** Enable for all supported APIs */
	CINSTR_CLIENTAPI_ALL  = 0xFFFF
} cinstr_clientapi_t;

/**
 * The different ways in which hardware performance counters may be collected.
 */
typedef enum
{
    /**
     * Hardware performance counters are not collected at all
     */
    CINSTR_HW_PERFORMANCE_COUNTER_MODE_DISABLED,
    /**
     * Hardware performance counters are enabled at job start and sampled at job end
     */
    CINSTR_HW_PERFORMANCE_COUNTER_MODE_JOB,
    /**
     * Harware performance counters are dumped per tile to the destination buffer. In
     * this mode, only shader performance counters are enabled.
     */
    CINSTR_HW_PERFORMANCE_COUNTER_MODE_TILE
} cinstr_hw_counters_collection_mode_t;


/**
 * Indicates what action should be taken after an event has been sent to and processed
 * bythe Instrumentation Plugin.
 */
typedef enum {
    /** No action need be taken */
    CINSTR_EVENT_ACTION_NONE,
    /** Force the function to return immediately */
    CINSTR_EVENT_ACTION_STUB
} cinstr_event_return_action_t;

typedef enum
{
	CINSTR_MODEL_MALI_200 = 1,
	CINSTR_MODEL_MALI_300 = 2,
	CINSTR_MODEL_MALI_400MP = 3,
	CINSTR_MODEL_MALI_T600 = 4,
} cinstr_hw_model_t;

/**
 * Used to identify the driver and GPU version
 */
struct cinstr_driver_info {
    /** The SW driver version */
    u32 sw_version;
	/** Indicate which GPU the driver controls */
	u32 hw_model;
    /** Indicates the version of the GPU driver controls */
    u32 hw_version;
};

/**
 * Event data for an api call
 *
 * \note Both the format string describing the types of the parameters to the function
 *       as well as the parameters themselves are passed as part of the variadic argument
 *       to the handle_event function in the \ref cinstr_plugin_instance struct.
 */
struct cinstr_event_data_api {
    /** The client API that experienced the event */
    u32 api_id;
    /** The ID of the API function that was called */
    u32 function;
};

/**
 * Event data for a log message
 *
 * \note Both the format string and parameters to be used with the tokens in it
 *       are passed as part of the variadic argument to the handle_event function in
 *       the \ref cinstr_plugin_instance struct.
 */
struct cinstr_event_data_log {
    /** The client API which experienced the event */
    cinstr_clientapi_t api;
    /** The level of the log message (e.g. debug, warning etc.) */
    cinstr_log_level_t level;
};

/**
 * Event data for frame completed events
 */
struct cinstr_event_data_frame_complete
{
	/* Which frame was completed */
	u32 frame_number;
};

/**
 * Event data for frame completed events
 */
struct cinstr_event_data_render_pass_complete
{
	/* Which frame the render pass belongs to */
	u32 frame_number;
	/* Which render pass was completed */
	u32 render_pass_number;
};

/**
 * Performance counter event data for Mali-200/400, both HW and SW counters.
 */
struct cinstr_event_data_perfcount
{
	/** The source of the event, see enum cinstr_counter_source in mali_cinstr_counters_m200.h for more values. */
	u32 source;
	/** The number of counters reported (size of counters and values array). */
	u32 count;
	/** An array of the counter IDs for the reported counters, index matching the values array. */
	u32* counters;
	/** An array of the counter values for the reported counters, index matching the counters array. */
	s64* values;
};

/**
 * Software counter event data
 */
struct cinstr_event_data_perfcount_sw {
    /** The client API which experienced the event
     */
    cinstr_clientapi_t api;
    /** The ID of the counter that is to be changed */
    u32 counter_id;
    /** The increment to be applied to the counter */
    s32 increment;
};

/**
 * Hardware counter event data
 */
struct cinstr_event_data_perfcount_hw {
    /**
     * The size of the block of performance counter data received from
     * the hardware
     */
    u32 size;
    /** Pointer to the performance counter data */
    char *data;
};

/**
 * Data related to a driver event.
 *
 * This structure contains data collected for an event.
 *
 * \note There is no related data to a frame completion event. For such events, the value
 *       stored in the payload union is undefined.
 */
struct cinstr_event_data {
    /** The event that was encountered.
     */
    cinstr_event_t type;
    /** The data related to the event
     */
    union {
      struct cinstr_event_data_log                  log;
      struct cinstr_event_data_api                  api;
      struct cinstr_event_data_frame_complete       frame_complete;
      struct cinstr_event_data_render_pass_complete render_pass_complete;
      struct cinstr_event_data_perfcount            perfcount;
      struct cinstr_event_data_perfcount_sw         perfcount_sw;
      struct cinstr_event_data_perfcount_hw         perfcount_hw;
    } payload;
};


/**
 * Defines a location for jub dump data to be copied
 *
 * This structure provides the necessary information to pass the multiple files that are
 * required as part of a job dump to an Instrumentation Plugin in an extensible
 * way.
 *
 * \todo Need to design this structure!
 */
struct cinstr_job_dump {
    void *dest;
};

/** \} end group cinstr_common */

/**
 * \addtogroup cinstr_ipi_core Instrumentation Plugin Interface Core APIs
 * \{
 */

/**
 * \def CINSTR_FEATURE_AVAILABLE(_feature)
 *
 * \brief Checks whether an instrumentation feature is supported by the driver
 *
 * This macro checks whether the specified instrumentation feature has been compiled in to
 * the driver for any client API.
 *
 * \param _instance  A pointer to an Instrumentation Core instance
 * \param _feature   The feature(s) whose state is the be checked (as a \ref cinstr_feature_t)
 * \return          MALI_TRUE if available, otherwise MALI_FALSE
 */
#define CINSTR_FEATURE_AVAILABLE(_instance, _feature) \
    ( ((_feature) == (_instance)->cinstr_core_available & (_feature)) ? MALI_TRUE : MALI_FALSE )

/**
 * \def CINSTR_FEATURE_AVAILABLE_FOR_CLIENT_API(_api, _feature)
 *
 * \brief Checks whether an instrumentation feature is supported by the driver for the
 *        specified client API.
 *
 * This macro checks whether the specified instrumentation feature has been compiled in to
 * the indicated client API.
 *
 * \param _instance  A pointer to an Instrumentation Core instance
 * \param _api       The client API that much support the feature (as a \ref cinstr_clientapi_t)
 * \param _feature   The feature(s) whose state is the be checked (as a \ref cinstr_feature_t)
 * \return          MALI_TRUE if available, otherwise MALI_FALSE
 */
#define CINSTR_FEATURE_AVAILABLE_FOR_CLIENT_API(_instance, _api, _feature) \
    ( ((_feature) == (_instance)->cinstr_core_features_available[(_api)] & (_feature)) ? MALI_TRUE : MALI_FALSE )

/**
 * A structure containing all fields and methods that an Instrumentation Plugin
 * needs access to from the Instrumentatin Core.
 */
typedef struct cinstr_core_instance
{
    /**
     * A word indicating which instrumentation features have been compiled into
     * the driver.
     */
    u32 features_available;

    /**
     * Returns information on the driver to the calling Instrumentation Plugin
     *
     * \return     Information on the driver as well as the underlying hardware
     */
    struct cinstr_driver_info (*cinstr_core_get_driver_info)(void);


    /**
     * \brief Enables the collection of data for an instrumentation feature
     *
     * This calls instructs the driver to beging collection of data related to the
     * specified feature.
     *
     * \param feature            The feature to enable in the driver
     * \param api                The client API(s) the toggle applies to
     *
     * \return                   Non-zero indicates failure
     *
     * \note This function will be called by the Instrumentation Plugin
     * \note Some features may not support filtering by client API
     */
    cinstr_error_t (*feature_enable)(cinstr_clientapi_t api, cinstr_feature_t feature);

    /**
     * \brief Disables the collection of data for an instrumentation feature
     *
     * This calls advises the driver that the data related to the specified feature
     * no longer need be collected.
     *
     * \param feature            The feature whose data is no longer required
     * \param api                The client API(s) the toggle applies to
     *
     * \return                   Non-zero indicates failure
     *
     * \note This function will be called by the Instrumentation Plugin
     */
    cinstr_error_t (*feature_disable)(cinstr_clientapi_t api, cinstr_feature_t feature);

	/**
	 * \brief Starts system-wide recording of profiling events.
	 *
	 * Trying to start recording while another gathering in place will make this function fail.
	 * You must also call profiling_clear before starting another recording.
	 *
	 * The CINSTR_FEATURE_TIMELINE_PROFILING feature must be enabled for user space generated events to be generated.
	 *
	 * \param limit The desired limit for number of events to record.
	 * \return The actual limit (might be lower than requested) of number of events to record. 0 on failure.
	 */
	u32 (*profiling_start)(u32 limit);

	/**
	 * \brief Stop recording of profiling events.
	 *
	 * After this is called, the events will be ready to be retrieved by calling profiling_get_events.
	 *
	 * \return Number of events recorded.
	 */
	u32 (*profiling_stop)(void);

	/**
	 * \brief Retrieve recorded profiling events.
	 *
	 * You must have called profiling_stop before you can collect events.
	 *
	 * \param entries Pointer to an array where the retrieived events will be stored.
	 * \param count The number of entries to be returned (should match return value of profiling_stop).
	 * \return The number of events reteurned in the entries array.
	 */
	u32 (*profiling_get_events)(cinstr_profiling_entry_t* entries, u32 count);

	/**
	 * \brief Clear the recorded events.
	 *
	 * Clear the recorded events, so that a new profiling event recording can be started.
	 *
	 * \return CINSTR_ERROR_SUCCESS on success, otherwise failure.
	 */
	cinstr_error_t (*profiling_clear)(void);

	/**
	 * \brief Retrieve number of avaialble counters.
	 *
	 * \return Number of available counters
	 */
	u32 (*get_number_of_counters)(void);

	/**
	 * \brief Retrieve avaialble counters.
	 *
	 * \return Number of available counters
	 */
	cinstr_error_t (*get_counters)(u32* ids, u32 size);

	/**
	 * \brief Enable specified counter.
	 *
	 * Available values are returned by get_counters or can be found in the cinstr_counters_m200_t enum.
	 *
	 * \param id Which counter to enable.
	 * \return Number of available counters
	 *
	 * \return CINSTR_ERROR_SUCCESS on success, otherwise failure.
	 */
	cinstr_error_t (*counter_enable)(u32 id);

	/**
	 * \brief Enable specified counter.
	 *
	 * Available values are returned by get_counters or can be found in the cinstr_counters_m200_t enum.
	 *
	 * \param id Which counter to enable.
	 * \return Number of available counters
	 *
	 * \return CINSTR_ERROR_SUCCESS on success, otherwise failure.
	 */
	cinstr_error_t (*counter_disable)(u32 id);

    /**
     * \brief Configures the collection of hardware performance counters
     *
     * This function is used to configure the hardware performance counters that are to
     * be collected on the GPU. For information on what the bits in the enable words mean,
     * refer to the GPU specific implementation specificication.
     *
     * \param type                The type of hardware counter collection to be used
     *
     * \param cinstr_hw_counters_enable_job_manager  Enable bits for performance counters in the
     *                                               Job Manager
     * \param cinstr_hw_counters_enable_shader_cores Enable bits for performance counters in the
     *                                               each shader core
     * \param cinstr_hw_counters_enable_tiler_cores  Enable bits for performance counters in the
     *                                               each tiler core
     * \param cinstr_hw_counters_enable_level3_cache Enable bits for performance counters in the
     *                                               level 3 cache
     * \param cinstr_hw_counters_enable_level2_cache Enable bits for performance counters in the
     *                                               level 2 cache
     *
     * \return                    Returns MALI_TRUE if the call was successful and MALI_FALSE
     *                            otherwise
     *
     * \note The destination buffer size must correspond to the requirments stipulated in the
     * architecture specification document.
     *
     */
    mali_bool (*cinstr_core_feature_configure_hw_counters)(cinstr_hw_counters_collection_mode_t type,
                        u32 cinstr_hw_counters_enable_job_manager,
                        u32 cinstr_hw_counters_enable_shader_cores,
                        u32 cinstr_hw_counters_enable_tiler_cores,
                        u32 cinstr_hw_counters_enable_level3_cache,
                        u32 cinstr_hw_counters_enable_level2_cache);

    /**
     * \brief Configures where job dump data should be stored
     *
     * This function is used to configure job dumping in the driver. It specifies the location
     * where job dump data should be copied to when ready.
     *
     * In order to start the collection of job dump data, a call to \ref feature_enable (or a
     * suitable helper macro) on the Instrumentation Core instance should be made with the
     * relevant parameters.
     *
     * \param dest                 A pointer to a \ref cinstr_job_dump structure into which job dump
     *                             data is to be copied.
     *
     * \return                     Non-zero indicates failure
     *
     * \todo                       Need to determine the best way to return data to the plugin.
     *                             Perhaps a series of ring buffers is a better way?
     */
    cinstr_error_t (*configure_job_dump)(struct cinstr_job_dump *dest);
} cinstr_core_instance;


/**
 * Container for all methods related to an instance of an Instrumentation Plugin.
 */
typedef struct cinstr_plugin_instance
{

    /**
     * \brief Access plugin metadata
     *
     * Checks the metadata of a plugin to ensure that it is both compatible and safe.
     *
     * \param version          Pointer to a u32 which will contain the version of the
     *                         Instrumentation Plugin API the plugin uses
     *
     * \param security_token   Pointer to a u64 which will contain the key signature of
     *                         the plugin that can be used to verify that it is from a
     *                         trusted source.
     *
     * \return                 None
     *
     */
    void (*get_info)(u32 version, u64 *security_token);

    /**
     * \brief Passes a driver event to the Instrumentation Plugin
     *
     * When an event occurs in the driver, it is passed on to the Instrumentation Plugin
     * using this function. The Instrumentation Plugin is then tasked with the freeing of
     * the event structure when it has finished with it.
     *
     * \param event              Data corresponding to the event
     * \param ...                Variadic data for the event. The format of the variadic
     *                           arguments depends on the type of the event.
     *
     * \return                   Indicates the action the caller needs to take.
     *
     * \note In order to support features such as API stubbing and API manipulation, this
     *       function returns information on whether the execution of the function should
     *       continue or whether it should return immediately.
     *
     * \todo Are var args handled properly if there are potentially different compilers
     *       compiling the Core and the Plugin?
     */
    cinstr_event_return_action_t (*handle_event)(struct cinstr_event_data *event, va_list args);

    /**
     * \brief Initialize an Instrumentation Plugin
     *
     * Releases any resources held by the Instrumentation Core and Instrumentation Plugin.
     *
     * \return                   Non-zero indicates failure
     */
    cinstr_error_t (*term)(void);
} cinstr_plugin_instance;

/**
 * A version independent structure that communicates relevant data to the
 * Instrumentation Plugin at load time. It is intended that the Plugin
 * interpret the core pointer appropriately given the version information.
 */
typedef struct cinstr_core_data
{
    /** Indicates the version of the structure that is passed */
    u32 core_version;

    /** A pointer to the core instance structure */
    const cinstr_core_instance *core;
	cinstr_plugin_instance *plugin;
} cinstr_core_data;

/** \} end group cinstr_ipi_core */

#endif /*_CINSTR_COMMON_H_*/
