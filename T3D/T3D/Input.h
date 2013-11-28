// =========================================================================================
// KXG363 - Advanced Games Programming, 2012
// =========================================================================================
//
// Author: Robert Ollington
//
// input.h
//
// Simple static class to track keyboard and mouse
// Adapted from Ogre3D

#ifndef INPUT_H
#define INPUT_H

namespace T3D
{
	// ASCII Keys
	#define KEY_UNKNOWN		0 
	#define KEY_FIRST		0 
	#define KEY_BACKSPACE	8 
	#define KEY_TAB			9 
	#define KEY_CLEAR		12 
	#define KEY_RETURN		13 
	#define KEY_PAUSE		19 
	#define KEY_ESCAPE		27 
	#define KEY_SPACE		32 
	#define KEY_EXCLAIM		33 
	#define KEY_QUOTEDBL	34 
	#define KEY_HASH		35 
	#define KEY_DOLLAR		36 
	#define KEY_AMPERSAND	38 
	#define KEY_QUOTE		39 
	#define KEY_LEFTPAREN	40 
	#define KEY_RIGHTPAREN	41 
	#define KEY_ASTERISK	42 
	#define KEY_PLUS		43 
	#define KEY_COMMA		44 
	#define KEY_MINUS		45 
	#define KEY_PERIOD		46 
	#define KEY_SLASH		47 
	#define KEY_0			48 
	#define KEY_1			49 
	#define KEY_2			50 
	#define KEY_3			51 
	#define KEY_4			52 
	#define KEY_5			53 
	#define KEY_6			54 
	#define KEY_7			55 
	#define KEY_8			56 
	#define KEY_9			57 
	#define KEY_COLON		58 
	#define KEY_SEMICOLON	59 
	#define KEY_LESS		60 
	#define KEY_EQUALS		61 
	#define KEY_GREATER		62 
	#define KEY_QUESTION	63 
	#define KEY_AT			64 
	/* 
	   Skip uppercase letters
	 */
	#define KEY_LEFTBRACKET		91 
	#define KEY_BACKSLASH		92 
	#define KEY_RIGHTBRACKET	93 
	#define KEY_CARET			94 
	#define KEY_UNDERSCORE		95 
	#define KEY_BACKQUOTE		96 
	#define KEY_A			97 
	#define KEY_B			98 
	#define KEY_C			99 
	#define KEY_D			100 
	#define KEY_E			101 
	#define KEY_F			102 
	#define KEY_G			103 
	#define KEY_H			104 
	#define KEY_I			105 
	#define KEY_J			106 
	#define KEY_K			107 
	#define KEY_L			108 
	#define KEY_M			109 
	#define KEY_N			110 
	#define KEY_O			111 
	#define KEY_P			112 
	#define KEY_Q			113 
	#define KEY_R			114 
	#define KEY_S			115 
	#define KEY_T			116 
	#define KEY_U			117 
	#define KEY_V			118 
	#define KEY_W			119 
	#define KEY_X			120 
	#define KEY_Y			121 
	#define KEY_Z			122 
	#define KEY_DELETE		127 

	// Keypad
	#define KEY_KP0			256 
	#define KEY_KP1			257 
	#define KEY_KP2			258 
	#define KEY_KP3			259 
	#define KEY_KP4			260 
	#define KEY_KP5			261 
	#define KEY_KP6			262 
	#define KEY_KP7			263 
	#define KEY_KP8			264 
	#define KEY_KP9			265 
	#define KEY_KP_PERIOD	266 
	#define KEY_KP_DIVIDE	267 
	#define KEY_KP_MULTIPLY	268 
	#define KEY_KP_MINUS	269 
	#define KEY_KP_PLUS		270 
	#define KEY_KP_ENTER	271 
	#define KEY_KP_EQUALS	272 

	// Arrows
	#define KEY_UP			273 
	#define KEY_DOWN		274 
	#define KEY_RIGHT		275 
	#define KEY_LEFT		276 
	#define KEY_INSERT		277 
	#define KEY_HOME		278 
	#define KEY_END			279 
	#define KEY_PAGEUP		280 
	#define KEY_PAGEDOWN	281 

	// Function keys 
	#define KEY_F1			282 
	#define KEY_F2			283 
	#define KEY_F3			284 
	#define KEY_F4			285 
	#define KEY_F5			286 
	#define KEY_F6			287 
	#define KEY_F7			288 
	#define KEY_F8			289 
	#define KEY_F9			290 
	#define KEY_F10			291 
	#define KEY_F11			292 
	#define KEY_F12			293 
	#define KEY_F13			294 
	#define KEY_F14			295 
	#define KEY_F15			296 

	class Input
	{
	public:
		static void init();
		static void onKeyDown(int keycode);
		static void onKeyUp(int keycode);
		static void onMouseMotion(int dx, int dy);

	public:
		static bool keyDown[512];
		static int mouseX, mouseY;
	};

}

#endif

