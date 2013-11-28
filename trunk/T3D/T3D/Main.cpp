// =========================================================================================
// KXG363 - Advanced Games Programming, 2012
// =========================================================================================
//
// Author: Robert Ollington
//
// main.cpp
//
// Main entry point. Creates and runs a T3DApplication

#include "T3DTest.h"

using namespace T3D;

int main(int argc, char* argv[]){
	T3DTest *theApp = new T3DTest();
	theApp->run();
	delete theApp;

	return 0;
}