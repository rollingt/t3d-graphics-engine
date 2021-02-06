/*
 * Logger.cpp
 * Author: Evan Harvey
 * Output strings and streams to console and file.
 *
 * NOTE(Evan): A lot of of the functionality this offers could be replaced by SDL2, if T3D upgrades!
*/
#pragma once

#include <stdio.h>       // printf, vprintf, vfprintf, FILE
#include <errno.h>       // errno
#include <string.h>      // strerror

#include "Logger.h"

// Platform-specific code.

/* If we aren't on windows, don't pull in _fullpath or even try to
   get an absolute path. Just make fullpath return false always. 
   TODO. There's definitely ways to do this (and other file-related shenanigans) 
   with c++14 std::filesystem::paths that are portable and robust. */
#if defined(_WIN32) || defined(WINDOWS) || defined(WIN32)
#include <stdlib.h>				// _fullpath
#define PATH_SIZE_MAX _MAX_PATH // https://docs.microsoft.com/en-us/windows/win32/fileio/maximum-file-path-limitation

#else  // Non-Windows; unistd.h, or std::filesystem should cover this if T3D ever needs
#define _fullpath(Buffer, Path, Size)  (0)
#define PATH_SIZE_MAX 512u
#endif


// 'Helper' macros.

#define EnumToBitflag(Enum)      ((static_cast<uint32_t>(Enum)))
#define IndexOfBitset(Bitset)    ((EnumToBitflag(Bitset)) ? ((logger::Log2Lookup(EnumToBitflag(Bitset)))) : (0u))


// NOTE(Evan):
// Variadic arguments are very error prone. Here's a short summary of ways it could go wrong for future reference:
// - The ordering of the parameters matters for when va_start() is called;
// - every `va_start()` must have an associated `va_end()` call
// - reusing va_args requires va_copy() and an associated va_end()
// - The member preceding ellipsis `...` must not be a reference type or have 'default promotion' semantics, like how '64' could be promoted to float'.
//   This one is a bit confusing, but if the last argument is always `char *`, it doesn't matter.
//
// The alternative is template metaprogramming, which offers compile-time safety at the cost of compile-time understandability and code size.
// 'It should be fine', and 'it works on my machine', etc etc.
#include <stdarg.h>      // va_arg, va_end, va_copy

namespace T3D
{
	/*!
	 *  \param Priority All priorities equal or greater to this will be shown. As in, `Info` implies `Warning` and `Error`.
	 *  \param Output Which output stream/s should the logger initialize. 
	 *  \param EnableAllCategories Should all application categories be filtered initially? (e.g. `Platform`, `Audio`, `Animation`, etc)
	 *	\param LogFilePath Where the log file is found. Assumed to be relative to where the T3D executable is running from. No support for UTF8/UTF16 paths.
	 */
	void 
	logger::Initialise(priority	     Priority,
					   output_stream Output,
					   bool			 EnableAllCategories,
					   const char   *LogFilePath)
	{
		auto &TheLogger = logger::GetLogger();
		FILE *TheLogFile;
		auto CantOpenFile = fopen_s(&TheLogFile, LogFilePath, "w");

		if (CantOpenFile)
		{
			// Error buffer on failure
			const rsize_t BufferSize = 512;
			char Buffer[BufferSize] = {0};
			strerror_s(Buffer, BufferSize, errno);
			printf("[WARNING] :: [PLATFORM]  :: Could not open log file at %s! Defaulting to console output only. Reason :: %s", 
					LogFilePath, Buffer); 
		}
		else
		{
			// Path buffer on success
			const size_t BufferSize = PATH_SIZE_MAX; 
			char Buffer[BufferSize] = {0};

			// The log file path we want to print.
			// This is relative by default, typically `../<name_of_log` from either Debug/ or Release/.
			//     - We want to resolve it as absolute path to make it slightly easier to find the location,
			//     - but it's also possible for an unbounded amount of annoying things to happen involving e.g.
			//     - utf-16 nonsense, network-mountable locations on university computers, etc
			// So we provide a known good _relative_ path as a fallback!
			const char *PrintablePath = LogFilePath;

			auto CanFindAbsolutePath = _fullpath(Buffer, LogFilePath, _MAX_PATH);
			if (CanFindAbsolutePath) PrintablePath = Buffer;

			printf("[INFO]    :: [PLATFORM]  :: Log Initialised at %s\n", PrintablePath);
			TheLogger.LogFilePath = LogFilePath;
			TheLogger.LogFile = TheLogFile;
		}

		/* Lookup Tables.
		   These are manually `indented` using spaces, because the Windows console uses 8-space tabstops,
		   and ANSI terminals on Unix-like systems use both 8 and 4 space tabstops. So everything lines up right. */
		TheLogger.CategoryStringLookup = 
		{
			{
				 category::Debug,      "[DEBUG]     :: "
			},
			{
				 category::Platform,   "[PLATFORM]  :: "
			},
			{
				 category::Video,      "[VIDEO]     :: "
			},
			{
				 category::Audio,      "[AUDIO]     :: "
			},
			{
				 category::Game,       "[GAME]      :: "
			},
			{
				 category::Animation,  "[ANIMATION] :: "
			},
			{
				 category::Task,       "[TASK]      :: "
			},

		};

		TheLogger.PriorityStringLookup = 
		{
			{
				 priority::Tracing, "[TRACING] :: "
			},
			{
				 priority::Info,    "[INFO]    :: "
			},
			{
				 priority::Warning, "[WARNING] :: "
			},
			{
				 priority::Error,   "[ERROR]   :: "
			},
		};

		TheLogger.CurrentPriority = Priority;
		if (EnableAllCategories) TheLogger.CurrentCategories.set(); /* Set all categories as visible. */
	}


	/*!
	 *  \param Format A null-terminated c-string holding printf-style formatting information.
	 *  \param ... Optional variadic arguments
	 */
	void 
	logger::Trace(const char *Format, ... /* variadic args */)
	{
		if (logger::GetLogger().CurrentPriority > priority::Tracing) return;

		va_list Args;  /* VA_START */
		va_start(Args, Format);
		{
			logger::Log(priority::Tracing, output_stream::All, category::Debug, Format, Args);
		} 
		va_end(Args);  /* VA_END */

		
	}

	/*!
	 *  \param Format A null-terminated c-string holding printf-style formatting information.
	 *  \param ... Optional variadic arguments
	 */
	void 
	logger::Info(const char *Format, ... /* variadic args */)
	{
		if (logger::GetLogger().CurrentPriority > priority::Info) return;

		va_list Args;  /* VA_START */
		va_start(Args, Format);
		{
			logger::Log(priority::Info, output_stream::All, category::Debug, Format, Args);
		} 
		va_end(Args);  /* VA_END */
		
	}

	/*!
	 *  \param Format A null-terminated c-string holding printf-style formatting information.
	 *  \param ... Optional variadic arguments
	 */
	void 
	logger::Warn(const char *Format, ... /* variadic args */)
	{
		if (logger::GetLogger().CurrentPriority > priority::Warning) return;

		va_list Args; /* VA_START */
		va_start(Args, Format);
		{
			logger::Log(priority::Warning, output_stream::All, category::Debug, Format, Args);
		}
		va_end(Args); /* VA_END */
	}

	/*!
	 *  \param Priority The new priority.
	 */
	void
	logger::SetPriority(priority Priority)
	{
		GetLogger().CurrentPriority = Priority;
	}

	/*!
	 *  \param Category to enable
	 */
	void
	logger::EnableCategory(category Category)
	{
		GetLogger().CurrentCategories.set(IndexOfBitset(Category), true);
	}

	/*!
	 *  \param Category to disable
	 */
	void
	logger::DisableCategory(category Category)
	{
		GetLogger().CurrentCategories.set(IndexOfBitset(Category), false);
	}

	void
	logger::EnableAllCategories()
	{
		GetLogger().CurrentCategories.set();
	}

	void
	logger::DisableAllCategories()
	{
		GetLogger().CurrentCategories.reset();
	}

	/*!
	 *  \param Priority The priority of the message
	 *  \param OutputStream Where the message should go
	 *  \param Category The subsystem the message should be classified under. If unsure, 'Debug' is a safe bet.
	 *  \param Format A null-terminated c-string holding printf-style formatting information.
	 *  \param ... Optional variadic arguments
	 *
	 *  \note If the supplied output stream is not enabled, this does not emit a warning.
	 */
	void
	logger::Log(priority      Priority, 
				output_stream OutputStream, 
				category      Category,
				const char   *Format, 
				...        /* variadic args */)
	{
		auto &TheLogger = logger::GetLogger();

		if (TheLogger.CurrentPriority > Priority)	                     return; /* priority filter */
		if (! TheLogger.CurrentCategories.test(IndexOfBitset(Category))) return; /* category filter */

		va_list Args; /* VA_START */
		va_start(Args, Format);
		{
			switch (OutputStream)
			{
				case output_stream::All:
				{
					va_list ArgsCopy;
					va_copy(ArgsCopy, Args); /* VA_COPY */
					{
						logger::LogToFile(Format, Priority, Category, Args);
						logger::LogToConsole(Format, Priority, Category, ArgsCopy);
					}
					va_end(ArgsCopy);       /* VA_COPY */

				} break;

				case output_stream::Console:
				{
					logger::LogToConsole(Format, Priority, Category, Args);
				} break;

				case output_stream::File:
				{
					logger::LogToFile(Format, Priority, Category, Args);
				} break;
			};

		} 
		va_end(Args); /* VA_END */
	}


	/* Private Interface  */


	/*! 
	 *  This closes the file and prints a 'log closed' message to standard output. Can't be filtered.
	 */
	logger::~logger()
	{
		// NOTE(Evan):
		// Despite being static the Logger has a deterministic _creation time_. 
		// It does not have a well-defined destruction time. This means that the file handle it holds will
		// be destroyed at some point by the c++ runtime after main returns.
		// This doesn't have any implications for T3D's current design except for the exact time when the file handle
		// is flushed matters.
		if (LogFile)
		{
			fclose(LogFile);
			printf("[INFO] :: [PLATFORM]    :: Closed log file at %s successfully\n", LogFilePath);
		}
	}

	//! \brief Get a handle to the singleton Logger instance. 
	/*!
	  * The first time this is called, the Logger's data members are initialized using a locally-scoped static.
	  */
	logger & 
	logger::GetLogger() 
	{ 
		static logger gLogger = {}; 
		return(gLogger); 
	}

	/*!
	 *  \param Priority The priority of the message
	 *  \param Format A null-terminated c-string holding printf-style formatting information.
	 *  \param Category The subsystem the message should be classified under. 
	 *  \param ... Optional variadic arguments
	 *  \note `va_start` should be called on `Args` before calling this function, and `va_end` should be called on `Args` sometime after this function returns.
	 */
	void
	logger::LogToConsole(const char *Format, 
						 priority    Priority, 
						 category    Category,
						 va_list     Args)
	{
		const char *PriorityLabel = logger::GetLogger().PriorityStringLookup[Priority];
		printf(PriorityLabel);

		const char *CategoryLabel = logger::GetLogger().CategoryStringLookup[Category];
		printf(CategoryLabel);

		vprintf(Format, Args);
		printf("\n");
	}


	/*!
	 *  \param Priority The priority of the message
	 *  \param Format A null-terminated c-string holding printf-style formatting information.
	 *  \param Category The subsystem the message should be classified under. 
	 *  \param ... Optional variadic arguments
	 *  \note `va_start` should be called on `Args` before calling this function, and `va_end` should be called on `Args` sometime after this function returns.
	 */
	void
	logger::LogToFile(const char *Format, 
			  priority    Priority,
			  category    Category,
			  va_list     Args)
	{
		auto &TheLogger = GetLogger();
		if (!TheLogger.LogFile) return; /* TODO(Evan): Test how verbose it is to warn that a file can't be found. */

		const char *PriorityLabel = logger::GetLogger().PriorityStringLookup[Priority];
		fprintf(TheLogger.LogFile, PriorityLabel);

		const char *CategoryLabel = logger::GetLogger().CategoryStringLookup[Category];
		fprintf(TheLogger.LogFile, CategoryLabel);

		vfprintf(TheLogger.LogFile, Format, Args);
		fprintf(TheLogger.LogFile, "\n");
	}

	/*
	 *  \param BitFlags Number to compute log_2(n) for. Assumed > 0.
	 */
	uint32_t
	logger::Log2Lookup(uint32_t Bitflags)
	{
		// Honestly, the code is slightly arcane but it's just a lookup table for log2(n).
		// Credit: https://graphics.stanford.edu/~seander/bithacks.html#IntegerLogLookup
		static const char LogTable256[256] = 
		{
			#define LT(n) n, n, n, n, n, n, n, n, n, n, n, n, n, n, n, n
			-1, 0, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3,
			LT(4), LT(5), LT(5), LT(6), LT(6), LT(6), LT(6),
			LT(7), LT(7), LT(7), LT(7), LT(7), LT(7), LT(7), LT(7)
		};

		uint32_t t, tt; // temporaries

		if (tt = Bitflags >> 16)
		{
			return((t = tt >> 8) ? 24 + LogTable256[t] : 16 + LogTable256[tt]);
		}
		else 
		{
			return((t = Bitflags >> 8) ? 8 + LogTable256[t] : LogTable256[Bitflags]);
		}
	}

}; // Namespace T3D
