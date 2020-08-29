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
		static const bool showWireframe = false;
		static const bool showAxes		= false;
		static const bool showGrid		= false;
		static const bool showVertices	= false;
	};
}