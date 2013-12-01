// =========================================================================================
// KXG363 - Advanced Games Programming, 2012
// =========================================================================================
//
// Author: Robert Ollington
//
// glrenderer.cpp
//
// Handles rendering tasks using OpenGL
// Some code adapted from KXG262

#include <sdl\SDL.h>
#include <gl\glew.h>
#include <gl\GL.h>
#include <gl\GLU.h>
#include <iostream>

#include "GLRenderer.h"
#include "GameObject.h"
#include "Camera.h"

namespace T3D
{
	GLRenderer::GLRenderer(void)
	{			
	}


	GLRenderer::~GLRenderer(void)
	{
	}
	
	void GLRenderer::prerender()
	{
		// set up lighting
		glEnable(GL_NORMALIZE);

		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);
		
		for(int i = 0; i < lights.size(); ++i)
		{
			int lightid = GL_LIGHT0+i;
			if (lights[i]->enabled){
				glEnable(lightid);
				
				float positiondata[4];
				if (lights[i]->type == Light::DIRECTIONAL)
				{
					Matrix3x3 rot;
					lights[i]->gameObject->getTransform()->getWorldMatrix().extract3x3Matrix(rot);
					Vector3 position = rot.GetColumn(2);
					positiondata[0] = position.x;
					positiondata[1] = position.y;
					positiondata[2] = position.z;
					positiondata[3] = 0;
				} else {
					Vector3 position = lights[i]->gameObject->getTransform()->getWorldPosition();
					positiondata[0] = position.x;
					positiondata[1] = position.y;
					positiondata[2] = position.z;
					positiondata[3] = 1.0;
				}

				glLightfv(lightid, GL_POSITION, positiondata);					
				glLightfv(lightid, GL_DIFFUSE, lights[i]->diffuse);
				glLightfv(lightid, GL_SPECULAR, lights[i]->specular);
				glLightf(lightid, GL_CONSTANT_ATTENUATION, lights[i]->constantAttenuation); 
				glLightf(lightid, GL_LINEAR_ATTENUATION, lights[i]->linearAttenuation);
				glLightf(lightid, GL_QUADRATIC_ATTENUATION, lights[i]->quadraticAttenuation); 
			} else {
				glDisable(lightid);
			}	
		}
		
		// Set up camera
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		if (camera!=NULL){						
			if (renderSkybox){		
				glDisable(GL_CULL_FACE);
				glDisable(GL_DEPTH_TEST);
				glDisable(GL_LIGHTING);
				glDisable(GL_FOG);
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);	
				glEnable(GL_TEXTURE_2D);				
				
				float camAngle;
				Vector3 camAxis;

				//camera->gameObject->getTransform()->getQuaternion().toAngleAxis(camAngle,camAxis);
				//glRotatef(-(camAngle*Math::RAD2DEG),camAxis.x,camAxis.y,camAxis.z);
				
				glMatrixMode(GL_MODELVIEW);
				glLoadIdentity();

				Matrix3x3 rot3 = Matrix3x3::IDENTITY;
				camera->gameObject->getTransform()->getWorldMatrix().extract3x3Matrix(rot3);
				Matrix4x4 rot4 = Matrix4x4::IDENTITY;
				rot4 = rot3.transpose();
				glLoadTransposeMatrixf(rot4.getData());

				drawSkybox();
			}
						
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			Matrix4x4 invCamMatrix = (camera->gameObject->getTransform()->getWorldMatrix()).inverse();
			glLoadTransposeMatrixf(invCamMatrix.getData());
		}

		
		// draw the global grid and axes if necessary		
		glEnable(GL_DEPTH_TEST);	
		if (showAxes)
		{
			// +ve axes
			glLineWidth(2);	
			glBegin(GL_LINES);
			glColor4f(1.0, 0.0, 0, 1.0);
			glVertex3f(0, 0, 0); glVertex3f(200, 0, 0);
			glColor4f(0.0, 1.0, 0, 1.0);
			glVertex3f(0.0, 0, 0); glVertex3f(0, 200, 0);
			glColor4f(0.0, 0.0, 1, 1.0);
			glVertex3f(0.0, 0, 0); glVertex3f(0, 0, 200);
			glColor4f(1.0, 1.0, 1.0, 1.0);
			glEnd();		
			
			// -ve axes	
			glEnable (GL_LINE_STIPPLE);
			glLineStipple (1, 0x00FF); /* dashed */
			glLineWidth(1);
			glBegin(GL_LINES);
			glColor4f(1.0, 0.0, 0, 1.0);
			glVertex3f(0, 0, 0); glVertex3f(-200, 0, 0);
			glColor4f(0.0, 1.0, 0, 1.0);
			glVertex3f(0.0, 0, 0); glVertex3f(0, -200, 0);
			glColor4f(0.0, 0.0, 1, 1.0);
			glVertex3f(0.0, 0, 0); glVertex3f(0, 0, -200);
			glColor4f(1.0, 1.0, 1.0, 1.0);
			glEnd();	
			glDisable (GL_LINE_STIPPLE);	
		}

		if (showGrid)
		{
			glEnable (GL_LINE_STIPPLE);
			glLineStipple (1, 0x5555); /* dotted */
			glBegin(GL_LINES);
			glColor4f(0.5, 0.5, 0.5, 1.0);
			for (float x=-200.0; x<=200.0; x+=10.0)
			{
				glVertex3f(x, 0, -200);
				glVertex3f(x, 0, +200);
			}
			for (float z=-200.0; z<=200.0; z+=10.0)
			{
				glVertex3f(-200, 0, z);
				glVertex3f(+200, 0, z);
			}
			glColor4f(1.0, 1.0, 1.0, 1.0);
			glEnd();
			glDisable (GL_LINE_STIPPLE);	
		}
		
		//fog?
		if (showFog){
			glEnable(GL_FOG);
			glFogi(GL_FOG_MODE, GL_EXP2);
			glFogfv(GL_FOG_COLOR, fogColour);
			glFogf (GL_FOG_DENSITY, fogDensity);
			glHint (GL_FOG_HINT, GL_NICEST);
		} else {
			glDisable(GL_FOG);
		}
		if (showWireframe){
			glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
			glDisable(GL_CULL_FACE);
		} else {
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);	
			glEnable(GL_CULL_FACE);
		}
		glEnable(GL_LIGHTING);
		glShadeModel(GL_SMOOTH);
		glEnable(GL_DEPTH_TEST);		
	}

	void GLRenderer::postrender()
	{
		SDL_GL_SwapBuffers();
	}

	void GLRenderer::draw(GameObject* object){
		Mesh *mesh = object->getMesh();
		Material *mat = object->getMaterial();
		if (mesh != NULL){			
			if (mat != NULL){
				glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat->getDiffuse());
				glMaterialfv(GL_FRONT, GL_SPECULAR, mat->getSpecular());
				glMaterialfv(GL_FRONT, GL_EMISSION, mat->getEmissive());
				glMaterialf(GL_FRONT,GL_SHININESS, mat->getShininess());
				
				if (mat->isTextured()){
					glEnable(GL_TEXTURE_2D);
					glBindTexture(GL_TEXTURE_2D,mat->getTexID());
					glEnableClientState(GL_TEXTURE_COORD_ARRAY);
					glTexCoordPointer(2, GL_FLOAT, 0, mesh->getUVs());

					glMatrixMode(GL_TEXTURE);
					glLoadIdentity();
					float s = mat->getTextureScale();
					glScalef(s,s,s);
				}
			}			
			
			glMatrixMode(GL_MODELVIEW);
			glPushMatrix();
			glMultTransposeMatrixf((object->getTransform()->getWorldMatrix()).getData());

			drawMesh(mesh);

			glPopMatrix();
			
			glDisable(GL_TEXTURE_2D);
		}
	}
	
	void GLRenderer::drawMesh(Mesh* mesh){
		glEnableClientState(GL_VERTEX_ARRAY);
		//glEnableClientState(GL_COLOR_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);

		glVertexPointer(3,GL_FLOAT,0,mesh->getVertices());
		glNormalPointer(GL_FLOAT,0,mesh->getNormals());
		//glColorPointer(4,GL_FLOAT,0,mesh->getColors());
		glDrawElements(GL_TRIANGLES,3*mesh->getNumTris(),GL_UNSIGNED_INT,mesh->getTriIndices());
		glDrawElements(GL_QUADS,4*mesh->getNumQuads(),GL_UNSIGNED_INT,mesh->getQuadIndices());
	}


	void GLRenderer::drawSkybox(){		
		glMatrixMode(GL_TEXTURE);
		glLoadIdentity();

		// Render the front quad
		glBindTexture(GL_TEXTURE_2D, skyboxfront->getID());
		glBegin(GL_QUADS);
			glTexCoord2f(1, 1); glVertex3f(  0.5f, -0.5f, -0.5f );
			glTexCoord2f(0, 1); glVertex3f( -0.5f, -0.5f, -0.5f );
			glTexCoord2f(0, 0); glVertex3f( -0.5f,  0.5f, -0.5f );
			glTexCoord2f(1, 0); glVertex3f(  0.5f,  0.5f, -0.5f );
		glEnd();
 
		// Render the left quad
		glBindTexture(GL_TEXTURE_2D, skyboxleft->getID());
		glBegin(GL_QUADS);
			glTexCoord2f(1, 1); glVertex3f(  0.5f, -0.5f,  0.5f );
			glTexCoord2f(0, 1); glVertex3f(  0.5f, -0.5f, -0.5f );
			glTexCoord2f(0, 0); glVertex3f(  0.5f,  0.5f, -0.5f );
			glTexCoord2f(1, 0); glVertex3f(  0.5f,  0.5f,  0.5f );
		glEnd();
 
		// Render the back quad
		glBindTexture(GL_TEXTURE_2D, skyboxback->getID());
		glBegin(GL_QUADS);
			glTexCoord2f(1, 1); glVertex3f( -0.5f, -0.5f,  0.5f );
			glTexCoord2f(0, 1); glVertex3f(  0.5f, -0.5f,  0.5f );
			glTexCoord2f(0, 0); glVertex3f(  0.5f,  0.5f,  0.5f );
			glTexCoord2f(1, 0); glVertex3f( -0.5f,  0.5f,  0.5f );
 
		glEnd();
 
		// Render the right quad
		glBindTexture(GL_TEXTURE_2D, skyboxright->getID());
		glBegin(GL_QUADS);
			glTexCoord2f(1, 1); glVertex3f( -0.5f, -0.5f, -0.5f );
			glTexCoord2f(0, 1); glVertex3f( -0.5f, -0.5f,  0.5f );
			glTexCoord2f(0, 0); glVertex3f( -0.5f,  0.5f,  0.5f );
			glTexCoord2f(1, 0); glVertex3f( -0.5f,  0.5f, -0.5f );
		glEnd();
 
		// Render the top quad
		glBindTexture(GL_TEXTURE_2D, skyboxup->getID());
		glBegin(GL_QUADS);
			glTexCoord2f(0, 1); glVertex3f( -0.5f,  0.5f, -0.5f );
			glTexCoord2f(0, 0); glVertex3f( -0.5f,  0.5f,  0.5f );
			glTexCoord2f(1, 0); glVertex3f(  0.5f,  0.5f,  0.5f );
			glTexCoord2f(1, 1); glVertex3f(  0.5f,  0.5f, -0.5f );
		glEnd();
 
		// Render the bottom quad
		glBindTexture(GL_TEXTURE_2D, skyboxdown->getID());
		glBegin(GL_QUADS);
			glTexCoord2f(0, 0); glVertex3f( -0.5f, -0.5f, -0.5f );
			glTexCoord2f(0, 1); glVertex3f( -0.5f, -0.5f,  0.5f );
			glTexCoord2f(1, 1); glVertex3f(  0.5f, -0.5f,  0.5f );
			glTexCoord2f(1, 0); glVertex3f(  0.5f, -0.5f, -0.5f );
		glEnd();
	}
	
	void GLRenderer::loadTexture(Texture *tex, bool repeat){
		GLuint texture = 0;			// This is a handle to our texture object
		GLenum texture_format;
		GLint  nOfColors;

		// Check that the image's width is a power of 2
		if ( (tex->getWidth() & (tex->getWidth() - 1)) != 0 ) {
			std::cout << "warning: " << tex << "'s width is not a power of 2\n";
		}
 
		// Also check if the height is a power of 2
		if ( (tex->getHeight() & (tex->getHeight() - 1)) != 0 ) {
			std::cout << "warning: " << tex << "'s height is not a power of 2\n";
		}
 
		// get the number of channels in the SDL surface
		nOfColors = tex->getSurface()->format->BytesPerPixel;
		if (nOfColors == 4)     // contains an alpha channel
		{
			if (tex->getSurface()->format->Rmask == 0x000000ff)
				texture_format = GL_RGBA;
			else
				texture_format = GL_BGRA;
		} else if (nOfColors == 3)     // no alpha channel
		{
			if (tex->getSurface()->format->Rmask == 0x000000ff)
				texture_format = GL_RGB;
			else
				texture_format = GL_BGR;
		} else {
			std::cout << "warning: the image is not truecolor..  this will probably break\n";
			// this error should not go unhandled
		}

		std::cout << "Mode: " << texture_format << " GL_RGBA: " << GL_RGBA << " GL_RGB: " << GL_RGB << " GL_BGRA: " << GL_BGRA << " GL_BGR: " << GL_BGR << "\n";

		// Have OpenGL generate a texture object handle for us
		glGenTextures( 1, &texture );
 
		// Bind the texture object
		glBindTexture( GL_TEXTURE_2D, texture );
		 
		// Set the texture's stretching properties
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
		if (repeat){
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		} else {
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		}
		
		// Load the image
		glTexImage2D(GL_TEXTURE_2D, 0, nOfColors, tex->getSurface()->w, tex->getSurface()->h, 0, texture_format, GL_UNSIGNED_BYTE, tex->getSurface()->pixels);
 
		tex->setID(texture);
	}

	void GLRenderer::loadSkybox(std::string tex){
		skyboxup = new Texture(tex+"_up.bmp");
		loadTexture(skyboxup);
		skyboxdown = new Texture(tex+"_down.bmp");
		loadTexture(skyboxdown);
		skyboxleft = new Texture(tex+"_left.bmp");
		loadTexture(skyboxleft);
		skyboxright = new Texture(tex+"_right.bmp");
		loadTexture(skyboxright);
		skyboxfront = new Texture(tex+"_front.bmp");
		loadTexture(skyboxfront);
		skyboxback = new Texture(tex+"_back.bmp");
		loadTexture(skyboxback);

		renderSkybox = true;
	}

}
