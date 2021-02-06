// =========================================================================================
// KXG363 - Advanced Games Programming
// =========================================================================================
//
// Author: Robert Ollington
//
// Terrain.cpp
//
// Component used for creating terrains - from an image file, or procedurally.

#include <sdl\SDL.h>
#include "Terrain.h"
#include "PlaneMesh.h"
#include "Math.h"
#include "GameObject.h"
#include "Transform.h"

namespace T3D{

	///-------------------------------------------------------------------------------------------------
	/// @fn	float Terrain::getHeight(Vector3 pos)
	///
	/// @brief	Calculates the interpolated terrain height.
	///
	/// @param	pos	The position (y coordinate is ignored).
	///
	/// @return	The interpolated height.

	float Terrain::getHeight(Vector3 pos){
		Vector3 terrainPos = gameObject->getTransform()->getWorldPosition();
		Vector3 relativePos = pos-terrainPos;
		float xPos = Math::clamp((relativePos.x+size/2.0f) / gridSize, 0, size/gridSize);
		float yPos = Math::clamp((relativePos.z+size/2.0f) / gridSize, 0, size/gridSize);

		int xlow = int(floor(xPos));
		int ylow = int(floor(yPos));
		int xhigh = int(ceil(xPos));
		int yhigh = int(ceil(yPos));

		PlaneMesh *mesh = (PlaneMesh*)gameObject->getMesh();
		Vector3 xlyl = mesh->getVertex(xlow,ylow);
		Vector3 xlyh = mesh->getVertex(xlow,yhigh);
		Vector3 xhyl = mesh->getVertex(xhigh,ylow);
		Vector3 xhyh = mesh->getVertex(xhigh,yhigh);

		Vector3 xli = Vector3::lerp(xlyl,xlyh,yPos-ylow);
		Vector3 xhi = Vector3::lerp(xhyl,xhyh,yPos-ylow);

		Vector3 posOnTerrain = Vector3::lerp(xli,xhi,xPos-xlow);

		return (gameObject->getTransform()->getWorldMatrix()*posOnTerrain).y;
	}

	///-------------------------------------------------------------------------------------------------
	/// @fn	void Terrain::createTerrain(std::string tex, float horizScale, float vertScale)
	///
	/// @brief	Creates a terrain from an image file.
	///
	/// @param	tex			Filename of the image to use.
	/// @param	horizScale	The horiz scale.
	/// @param	vertScale 	The vertical scale.

	void Terrain::createTerrain(std::string tex, float horizScale, float vertScale){
		SDL_Surface *surface;	// This surface will tell us the details of the image
 
		if ( (surface = SDL_LoadBMP(tex.c_str())) ) {
			if(SDL_MUSTLOCK(surface))
				SDL_LockSurface(surface);

			size = horizScale;

			int density = (surface->h>surface->w)?surface->w:surface->h - 2; // use smaller dimension
			PlaneMesh *mesh = new PlaneMesh(density); 

			gridSize = size/density;
			
			for (int i=0; i<=density; i++){
				for (int j=0; j<=density; j++){
					Vector3 current = mesh->getVertex(i,j);
					current.x *= size;
					current.z *= size;

					Uint32 color = ((Uint32 *)surface->pixels)[i*(surface->pitch/sizeof(unsigned int)) + j]; 

					Uint8 r,g,b,a;
					SDL_GetRGBA(color, surface->format,&r,&g,&b,&a);

					current.y = float(r)/256.0f * vertScale;

					mesh->setVertex(i,j,current.x,current.y,current.z);
				}
			}

			mesh->calcNormals();

			gameObject->setMesh(mesh);
		}
	}

	///-------------------------------------------------------------------------------------------------
	/// @fn	void Terrain::createFractalTerrain(int resolution, float horizScale, float vertScale,
	/// 	float roughness)
	///
	/// @brief	Creates fractal terrain using the midpoint method.
	///
	/// @param	resolution	The resolution (number of points).
	/// @param	horizScale	The horiz scale.
	/// @param	vertScale 	The vertical scale.
	/// @param	roughness 	The roughness.

	void Terrain::createFractalTerrain(int resolution, float horizScale, float vertScale, float roughness){
		PlaneMesh *mesh = new PlaneMesh(resolution); 
		float** data = Math::generateFractal(resolution,0,vertScale,roughness);

		size = horizScale;		
		gridSize = size/resolution;

		for (int i=0; i<=resolution; i++){
			for (int j=0; j<=resolution; j++){
				Vector3 current = mesh->getVertex(i,j);
				current *= size;
				current.y = data[i][j];
				mesh->setVertex(i,j,current.x,current.y,current.z);
			}
		}

		mesh->calcNormals();

		gameObject->setMesh(mesh);

		for (int i=0; i<resolution; i++){
			delete []data[i];
		}
		delete []data;

	}
}
