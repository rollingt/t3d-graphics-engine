/*
 * Logger.h
 * Author: Evan Harvey
 * Output strings and streams to console and file.
 *
 * NOTE(Evan): A lot of of the functionality this offers could be replaced by SDL2, if T3D upgrades!
*/
#pragma once

#include <stdarg.h>      
#include <bitset>        
#include <unordered_map> 

namespace T3D
{
	//! \brief Priority filter levels, ordered ascendingly.
	enum class priority      { Quiet, Tracing, Info, Warning, Error, }; 

	//! \brief Category filter levels, ordered ascendingly. 
	enum class category      { Debug = 1, Platform = 2, Video = 4, Audio = 8, Game = 16, Animation = 32, Task = 64, }; /* Bitflags */

	//! \brief Output streams for messages.
	enum class output_stream { Console, File, All };


	//! \brief Application logging class.
	//		   Outputs user-supplied strings to to file and console output streams with respect to
	//         priority filters ('warning', 'tracing', etc) and category filters ('Video, 'Debug', Animation', etc).
	/*
	 *	This class is designed to be easy to use for both debugging application code such as animation keyframes,
	 *  procedural mesh generation, and audio subsystems. An easy-to-use API is provided for these purposes, comprising 
	 *  `Trace`, `Info`, and `Warn` for message output, and priority-setting functions for toggling between states.
	 *
	 *  It also supports fine-grained filtering mechanisms intended for debugging and tracing lower-level T3D code.
	 *  Much of T3D has been instrumented with such logging messages -- if something isn't working, check the log file!
	 */
	class logger
	{
		public:

		//! \brief Initialise the logging subsystem. Must be called before using any other functions.
		//		   The default parameters are intended for student code, rather then T3D-debugging code.
		static void 
		Initialise(priority      Priority            = priority::Info,
				   output_stream Output              = output_stream::All,
				   bool			 EnableAllCategories = false,
				   const char   *LogFilePath         = "../T3D_Log.txt");

		//! \brief Log message to all output streams as `Debug` category, using `Tracing` priority. Very verbose.
		static void 
		Trace(const char *Format, ... /* variadic args */);

		//! \brief Log message to all output streams as `Debug` category, using `Info` priority. Verbose.
		static void 
		Info(const char *Format, ... /* variadic args */);

		//! \brief Log message to all output streams as `Debug` category, using `Warning` priority.
		static void 
		Warn(const char *Format, ... /* variadic args */);

		//! \brief Set filtering priority.
		static void
		SetPriority(priority Priority);

		//! \brief Enable filtering category.
		static void
		EnableCategory(category Category);

		//! \brief Disable filtering category.
		static void
		DisableCategory(category Category);

		//! \brief Disable all filtering categories.
		static void
		EnableAllCategories();

		//! \brief Enable all filtering categories.
		static void
		DisableAllCategories();

		//! \brief Log a message respecting priority, output stream and category filters.
		static void
		Log(priority      Priority, 
			output_stream OutputStream, 
			category      Category,
			const char   *Format, 
			...        /* variadic args */);

		//! \brief Delete the logger, flushing any in-memory data to output streams.
		~logger();

		private:
		logger() { /* private constructor */ }

		//! \brief Get a handle to the singleton Logger instance. The first time this is called, the Logger's data members are initialized.
		static logger & 
		GetLogger();

		//! \brief Log a message to the console.
		static void
		LogToConsole(const char *Format, 
				     priority    Priority, 
					 category    Category,
					 va_list     Args);

		//! \brief Log a message to file.
		static void
		LogToFile(const char *Format, 
				  priority    Priority,
				  category    Category,
				  va_list     Args);
		
		//! \brief Computes discretized log_2(n).
		static uint32_t
		Log2Lookup(uint32_t BitFlags);

		//! \brief Log file handle.
		/*
		 * Not much effort is made to ensure this is flushed if the application terminates unexpectedly.
		 */
		FILE       *LogFile          = nullptr;
		//! \brief Log file path. Assumed null-terminated ASCII characters.
		/*
		 * This _may_ be converted to an absolute path for diagnostic purposes, but that behaviour isn't portable.
		 */
		const char *LogFilePath      = nullptr;

		//! \brief The current priority of the logger.
		//! \note This starts off as `Quiet`, so that if the Logger isn't initialized but e.g. `Trace(...)` is called, nothing happens.
		priority CurrentPriority  = priority::Quiet;

		//! \brief The set of non-filtered categories.
		std::bitset<32>   CurrentCategories;

		//! \brief Internal priority label lookup table.
		std::unordered_map<priority, char *> PriorityStringLookup;

		//! \brief Internal category label lookup table.
		std::unordered_map<category, char *> CategoryStringLookup;
	};
};
