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
#include <sdl\SDL_ttf.h>
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

		// Clear back buffer and depth buffer before any drawing
		glDepthMask(GL_TRUE);		// depth mask must be true to clear buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Set up camera
		if (camera!=NULL){

			setCamera(camera);

			if (renderSkybox){		
				glDisable(GL_CULL_FACE);
				glDisable(GL_DEPTH_TEST);
				glDisable(GL_LIGHTING);
				glDisable(GL_FOG);
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);	
				glEnable(GL_TEXTURE_2D);				
				glDisable(GL_BLEND);
				
				float camAngle;
				Vector3 camAxis;

				//camera->gameObject->getTransform()->getQuaternion().toAngleAxis(camAngle,camAxis);
				//glRotatef(-(camAngle*Math::RAD2DEG),camAxis.x,camAxis.y,camAxis.z);
				
				glMatrixMode(GL_MODELVIEW);
				glPushMatrix();
				glLoadIdentity();

				Matrix3x3 rot3 = Matrix3x3::IDENTITY;
				camera->gameObject->getTransform()->getWorldMatrix().extract3x3Matrix(rot3);
				Matrix4x4 rot4 = Matrix4x4::IDENTITY;
				rot4 = rot3.transpose();
				glLoadTransposeMatrixf(rot4.getData());

				drawSkybox();

				glMatrixMode(GL_MODELVIEW);
				glPopMatrix();
			}
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
		glEnable(GL_DEPTH_TEST);		
		glDisable(GL_BLEND);
	}

	void GLRenderer::postrender()
	{
		showD2DOverlays();

		SDL_GL_SwapBuffers();
	}

	void GLRenderer::setCamera(Camera *cam)
	{
		if (cam!=NULL){

			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();

			if (cam->type == Camera::PERSPECTIVE) {
				gluPerspective(cam->fovy, cam->aspect, cam->near, cam->far);
			}
			else if (cam->type == Camera::ORTHOGRAPHIC) {
				glOrtho(cam->left, cam->right, cam->bottom, cam->top, cam->near, cam->far);
			}

			if (cam->gameObject != NULL)
			{
				glMatrixMode(GL_MODELVIEW);
				glLoadIdentity();
				Matrix4x4 invCamMatrix = (cam->gameObject->getTransform()->getWorldMatrix()).inverse();
				glLoadTransposeMatrixf(invCamMatrix.getData());
			}
		}
	}

	void GLRenderer::loadMaterial(Material* mat){

		if (mat != NULL){
			glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat->getDiffuse());
			glMaterialfv(GL_FRONT, GL_SPECULAR, mat->getSpecular());
			glMaterialfv(GL_FRONT, GL_EMISSION, mat->getEmissive());
			glMaterialf(GL_FRONT,GL_SHININESS, mat->getShininess());
			glShadeModel(mat->getSmoothShading() ? GL_SMOOTH : GL_FLAT);
			glDepthMask(mat->getDisablDepth() ?  GL_FALSE : GL_TRUE);	// enable/disable depth buffer write

			if (mat->getBlending() == Material::BLEND_NONE) {
				glDisable(GL_BLEND);						// No Blending (although diffuse alpha will still be used)

				// enable "on/off" transparency ("cookie cutter alpha")
				// This will only work for textures with an alpha channel (i.e. not bmp)
				glAlphaFunc(GL_GREATER, 0.99f);
				glEnable(GL_ALPHA_TEST);
			} 
			else {
				glDisable(GL_ALPHA_TEST);
				glEnable(GL_BLEND);						// Enable Blending

				// Material only supports a limited number of predefined blending modes
				if (mat->getBlending() == Material::BLEND_ADD) {
					// colors are added (values >1 are clipped to 1)
					glBlendFunc(GL_ONE, GL_ONE);
				}
				else if (mat->getBlending() == Material::BLEND_MULTIPLY) {
					// colors are multiplied (values >1 are clipped to 1)
					glBlendFunc(GL_ZERO, GL_SRC_COLOR);
				}
				else {
					// Assume Material::BLEND_DEFAULT
					// transparency: alpha=0 - invisible, alpha=1 - no transparency
					glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
				}
			}

			if (mat->isTextured()){
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D,mat->getTexID());
				glEnableClientState(GL_TEXTURE_COORD_ARRAY);

				glMatrixMode(GL_TEXTURE);
				glLoadIdentity();
				float s = mat->getTextureScale();
				glScalef(s,s,s);
			}
			else {
				glDisable(GL_TEXTURE_2D);
			}
		}	
	}

	void GLRenderer::draw(GameObject* object){
		Mesh *mesh = object->getMesh();
		if (mesh != NULL){	
			glMatrixMode(GL_MODELVIEW);
			glPushMatrix();
			glMultTransposeMatrixf((object->getTransform()->getWorldMatrix()).getData());
			drawMesh(mesh);
			glPopMatrix();
		}
	}
	
	void GLRenderer::drawMesh(Mesh* mesh){
		glEnableClientState(GL_VERTEX_ARRAY);
		//glEnableClientState(GL_COLOR_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);

		glVertexPointer(3,GL_FLOAT,0,mesh->getVertices());
		glNormalPointer(GL_FLOAT,0,mesh->getNormals());
		glTexCoordPointer(2, GL_FLOAT, 0, mesh->getUVs());
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

	// Helper function to get the GL texture format from a texture
	GLint GLRenderer::getTextureFormat(Texture *tex){

		GLenum texture_format;
		GLint  nOfColors;

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

		return texture_format;
	}


	void GLRenderer::loadTexture(Texture *tex, bool repeat){
		GLuint textureID = 0;			// This is a handle to our texture object
		GLint minFilter, magFilter;

		// Check that the image's width is a power of 2
		if ( (tex->getWidth() & (tex->getWidth() - 1)) != 0 ) {
			std::cout << "warning: " << tex << "'s width is not a power of 2\n";
		}
 
		// Also check if the height is a power of 2
		if ( (tex->getHeight() & (tex->getHeight() - 1)) != 0 ) {
			std::cout << "warning: " << tex << "'s height is not a power of 2\n";
		}
 
		// Have OpenGL generate a texture object handle for us
		glGenTextures( 1, &textureID );
		tex->setID(textureID);

 		// Bind the texture object
		glBindTexture( GL_TEXTURE_2D, textureID );

		// Set the texture filtering
		if (tex->getCountinuousTone()) {
			// for a continuous-tone image we want bilinear interpolation
			magFilter = GL_LINEAR;
			if (tex->getMipmap())	{
				// linear interpolation on the nearest mipmap for distant objects
				minFilter = GL_LINEAR_MIPMAP_LINEAR;
			}
			else {
				minFilter = GL_LINEAR;
			}
		}
		else {
			// a discrete-tone image, we want GL_NEAREST (so the texture doesn't appear out of focus)
			minFilter = GL_NEAREST;
			magFilter = GL_NEAREST;
		}
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter );

		// Set the texture's stretching properties
		if (repeat){
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		} else {
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		}
		
		// really loading for the first time but reload works if texture ID has been generated
		reloadTexture(tex);
	}

	// Reload the texture from the SDL surface.
	// It is assumed that the cahracterisics of the texture are unchanged
	void GLRenderer::reloadTexture(Texture *tex)
	{
		GLuint textureID = 0;			// This is a handle to our texture object
		GLenum texture_format;
		GLint  nOfColors;

		textureID = tex->getID();		// texture must have been previously loaded with loadTexture

		// get the number of channels in the SDL surface
		nOfColors = tex->getSurface()->format->BytesPerPixel;
		// get the GL texture format
		texture_format = getTextureFormat(tex);

		//std::cout << "Mode: " << texture_format << " GL_RGBA: " << GL_RGBA << " GL_RGB: " << GL_RGB << " GL_BGRA: " << GL_BGRA << " GL_BGR: " << GL_BGR << "\n";

		// Bind the texture object
		glBindTexture( GL_TEXTURE_2D, textureID );
		 
		// Load the image
		glTexImage2D(GL_TEXTURE_2D, 0, nOfColors, tex->getSurface()->w, tex->getSurface()->h, 0, texture_format, GL_UNSIGNED_BYTE, tex->getSurface()->pixels);

		if (tex->getMipmap()) {
			// have GLU build mipmaps
			int err = gluBuild2DMipmaps(GL_TEXTURE_2D, nOfColors, tex->getSurface()->w, tex->getSurface()->h, texture_format, GL_UNSIGNED_BYTE, tex->getSurface()->pixels);
			if (err != 0) {
				std::cout << "Failed to generate mipmaps : " << gluErrorString(err) << std::endl;
			}
		}
	}

	void GLRenderer::unloadTexture(Texture *tex)
	{
		GLuint textureID = tex->getID();
		glDeleteTextures(1, &textureID);
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

	// 2D overlay (used for on screen diagnostic messages mainly)
	void GLRenderer::add2DOverlay(Texture *texture, int x, int y)
	{
		overlay2D *overlay = new overlay2D;
		overlay->texture = texture;
		overlay->x = x;
		overlay->y = y;
		overlays.push_back(overlay);
	}

	// remove overlay
	void GLRenderer::remove2DOverlay(Texture *texture)
	{
		std::list<overlay2D *>::iterator i = overlays.begin();
		while (i != overlays.end())
		{
			overlay2D *overlay = *i;
			if (overlay->texture == texture)
			{
				overlays.remove(overlay);
				return;
			}
			i++;
		}
	}

	// Render overlay as a simple 2D Mesh
	// It is assumed that a 2D orthographic rendering context is in effect (enable2D)
	// based on code from http://www.gamedev.net/topic/284259-for-reference-using-sdl_ttf-with-opengl/
	void GLRenderer::draw2DMesh(overlay2D *overlay)
	{
		int x = overlay->x;
		int y = overlay->y;
		int w = overlay->texture->getWidth();
		int h = overlay->texture->getHeight();

		unsigned int texture = overlay->texture->getID();
	
		/* GL_NEAREST looks horrible, if scaled... */
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	

		/* prepare to render our texture */
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture);
		glColor3f(1.0f, 1.0f, 1.0f);

		/* Draw a quad at location */
		glBegin(GL_QUADS);
		/* Recall that the origin is in the lower-left corner
			That is why the TexCoords specify different corners
			than the Vertex coors seem to. */
		glTexCoord2f(0.0f, 1.0f); 
		glVertex2f(x    , y);
		glTexCoord2f(1.0f, 1.0f); 
		glVertex2f(x + w, y);
		glTexCoord2f(1.0f, 0.0f); 
		glVertex2f(x + w, y + h);
		glTexCoord2f(0.0f, 0.0f); 
		glVertex2f(x    , y + h);
		glEnd();
	
		glFinish();
	
	}


	// Show all diagnostic messages
	// Messages are rendered and then deleted. A persistant message must be added every frame
	// This isn't ideal but a better soloution would be to implement 2D sprites withing
	void GLRenderer::showD2DOverlays()
	{
		if (!overlays.empty())
		{
			// orthographic projection view is fixed to the GL viewport size
			int vPort[4];
			glGetIntegerv(GL_VIEWPORT, vPort);
			Camera overlayCam(Camera::ORTHOGRAPHIC, -1, 1, 0, vPort[2], 0, vPort[3]);		// temp hardwired camera for overlay
			setCamera(&overlayCam);

			glDisable(GL_DEPTH_TEST);		
			glDisable(GL_LIGHTING);
			glDisable(GL_FOG);

			glEnable(GL_BLEND);                         // Enable Blending
			//glBlendFunc(GL_SRC_COLOR,GL_ONE);			// transparent black background (sort of)
			glBlendFunc(GL_ONE,GL_ONE);			// add overlay (works well for white text)

			std::list<overlay2D *>::iterator i;
			for (i = overlays.begin(); i != overlays.end(); i++)
			{

				glMatrixMode(GL_MODELVIEW);
				glPushMatrix();
				glLoadIdentity();

				overlay2D *overlay = *i;
				draw2DMesh(overlay);

				glPopMatrix();
			}


		}
	}

}
