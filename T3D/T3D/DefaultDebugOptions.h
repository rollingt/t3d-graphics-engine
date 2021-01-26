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

namespace T3D
{
	class DefaultDebugOptions
	{
	public:
		// Renderer constants.
		
		// Visualization toggles
		static const bool showWireframe = false;  // F1
		static const bool showAxes		= false;  // F2
		static const bool showGrid		= false;  // F3
		static const bool showVertices	= false;  // F4


		// KeyboardController constants
		// Key and Mouse min/max
		static constexpr float keySensitivityMin   = 50.0;
		static constexpr float keySensitivityMax   = 100.0;
		static constexpr float mouseSensitivityMin = 0.0005f;
		static constexpr float mouseSensitivityMax = 0.0010f;
	};
}
