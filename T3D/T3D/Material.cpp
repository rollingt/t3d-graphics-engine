// =========================================================================================
// KXG363 - Advanced Games Programming
// =========================================================================================
//
// Author: Robert Ollington
//
// Material.cpp
//
// Class for encapsulating material properties

#include "Material.h"
#include <array>

namespace T3D {

	/* NOTE(Evan): 
	   `std::array<T, N>` is used to delegate the public overloaded constructors 
	   as a quick-and-dirty fix to C++ not supporting C-style array literal compound initialisers.
	   In English, both public constructors will be ambigious without using `std::array` 
	   as they could be an initialiser list {r, b, g, a} for the `r, b, g, a` constructor OR a compound array literal intended for the private constructor. Yikes.

	   On the plus side, migrating to a shared delegating constructor caught some nasty 
	   uninitialized member bugs that MSVC couldn't detect with the prior (copy-pasted) constructors.
    */
	Material::Material(std::array<float, 4> d) : diffuse{d[0], d[1], d[2], d[3]},
									             specular{1, 1, 1, 1},
									             emissive{0, 0, 0, 1},
									             shininess(100),
									             textured(false),
									             texture(nullptr),
									             textureScale(1.0f),
									             shader(nullptr),
									             smooth(true),	
									             sortedDraw(false),
									             disableDepth(false),
												 blending(BlendMode::DEFAULT) { }
                        
	Material::Material(void)							   : Material(std::array<float, 4>{ 1, 1, 1, 1 }) { }
	Material::Material(float r, float g, float b, float a) : Material(std::array<float, 4>{ 0, 0, 0, 1 }) { }

}
