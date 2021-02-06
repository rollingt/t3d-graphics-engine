// =========================================================================================
// KXG363 - Advanced Games Programming, 2012
// =========================================================================================
//
// Author: Robert Ollington
//
// DefaultDebugOptions.h
//
// Set default debug options. Applied when starting a WinGLApplication
#pragma once
#include <stdint.h>

namespace T3D
{
	//! \brief A class wrapping a handful of static data members.
	class DefaultDebugOptions
	{
	public:
		static const uint32_t DefaultWindowWidth = 1024u;

		static const uint32_t DefaultWindowHeight = 640u;
		// Visualization toggles

		//! \brief Show wireframe on startup
		static const bool showWireframe = false;  // F1

		//! \brief Show world axes on startup
		static const bool showAxes		= false;  // F2

		//! \brief Show mesh grid lines on startup
		static const bool showGrid		= false;  // F3

		//! \brief Show mesh points on startup
		static const bool showVertices	= false;  // F4


		// KeyboardController constants

		//! \brief Movement speed when acceleration key (`Shift` by default) isn't held
		static constexpr float keySensitivityMin   = 50.0f;

		//! \brief Movement speed when acceleration key (`Shift` by default) is held
		static constexpr float keySensitivityMax   = 100.0f;

		//! \brief Rotational speed when acceleration key (`Shift` by default) isn't held
		static constexpr float mouseSensitivityMin = 0.0005f;

		//! \brief Rotational speed when acceleration key (`Shift` by default) is held
		static constexpr float mouseSensitivityMax = 0.0010f;
	};
}
