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

#include "Transform.h"
#include "GameObject.h"
#include "Texture.h"
#include "Colour.h"

#include "GLRenderer.h"
#include "GameObject.h"
#include "Camera.h"
#include "Shader.h"
#include "Logger.h"

namespace T3D
{
	void GLRenderer::prerender()
	{
		// set up lighting
		glEnable(GL_NORMALIZE);

		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);
		
		for(unsigned int i = 0; i < lights.size(); ++i)
		{
			int lightid = GL_LIGHT0+i;
			if (lights[i]->enabled) {
				glEnable(lightid);
				
				float positiondata[4];
				float w;
				Vector3 position;
				if (lights[i]->type == Light::Type::DIRECTIONAL)
				{
					Matrix3x3 rot;
					lights[i]->gameObject->getTransform()->getWorldMatrix().extract3x3Matrix(rot);
					position = rot.GetColumn(2);
					w = 0;
				} else {
					position = lights[i]->gameObject->getTransform()->getWorldPosition();
					w = 1.0f;
				}

				positiondata[0] = position.x;
				positiondata[1] = position.y;
				positiondata[2] = position.z;
				positiondata[3] = w;

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
		if (camera) {

			setCamera(camera);

			if (renderSkybox){		
				glDisable(GL_CULL_FACE);
				glDisable(GL_DEPTH_TEST);
				glDisable(GL_LIGHTING);
				glDisable(GL_FOG);
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);	
				glEnable(GL_TEXTURE_2D);				
				glDisable(GL_BLEND);
				
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
		glDisable(GL_LIGHTING);
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
		glEnable(GL_LIGHTING);

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

		glPointSize(3.0);
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

			if (cam->type == Camera::Type::PERSPECTIVE) {
				gluPerspective(cam->fovy, cam->aspect, cam->near, cam->far);
			}
			else if (cam->type == Camera::Type::ORTHOGRAPHIC) {
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

			if (mat->getBlending() == Material::BlendMode::NONE) {
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
				if (mat->getBlending() == Material::BlendMode::ADD) {
					// colors are added (values >1 are clipped to 1)
					glBlendFunc(GL_ONE, GL_ONE);
				}
				else if (mat->getBlending() == Material::BlendMode::MULTIPLY) {
					// colors are multiplied (values >1 are clipped to 1)
					glBlendFunc(GL_ZERO, GL_SRC_COLOR);
				}
				else {
					// Assume Material::BlendMode::BLEND_DEFAULT
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

			Shader *shader = mat->getShader();
			if (shader) {
				shader->bindShader();
			}
		}	
	}		

	void GLRenderer::unloadMaterial(Material* mat){
			if (mat != NULL){
			Shader *shader = mat->getShader();
			if (shader) {
				shader->unbindShader();
			}
		}	
	}

	void GLRenderer::draw(GameObject* object){
		Mesh *mesh = object->getMesh();
		if (mesh != NULL) {

			float *matdiffuse = NULL;
			if (object->getAlpha() < 1.0)
			{
				// object override of material alpha
				float diffuse[4] = { 1.0, 1.0, 1.0, object->getAlpha() };
				if (object->getMaterial() != NULL) {
					matdiffuse = object->getMaterial()->getDiffuse();
					diffuse[0] = matdiffuse[0];
					diffuse[1] = matdiffuse[1];
					diffuse[2] = matdiffuse[2];
				}
				glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, diffuse);
			}

			glMatrixMode(GL_MODELVIEW);
			glPushMatrix();
			glMultTransposeMatrixf((object->getTransform()->getWorldMatrix()).getData());
			drawMesh(mesh);
			glPopMatrix();

			if (matdiffuse != NULL)
				glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, matdiffuse);	// restore material diffuse after alpha override

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
		glDrawElements(GL_QUADS, 4 * mesh->getNumQuads(), GL_UNSIGNED_INT, mesh->getQuadIndices());

		if (showPoints) glDrawArrays(GL_POINTS, 0, mesh->getNumVerts());
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
	int GLRenderer::getTextureFormat(Texture *tex){

		GLenum texture_format = GL_RGBA;
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
			logger::Log(priority::Warning, 
					    output_stream::All, 
					    category::Video, 
					    "Warning: loaded image is not truecolor..  this will probably break! Texture ID: %u\n"
					    ,
						tex->getID());
		}

		return texture_format;
	}


	void GLRenderer::loadTexture(Texture *tex, bool repeat){
		GLuint textureID = 0;			// This is a handle to our texture object
		GLint minFilter, magFilter;

		// Check that the image's width is a power of 2
		if ( (tex->getWidth() & (tex->getWidth() - 1)) != 0 ) {
			logger::Log(priority::Warning, 
					    output_stream::All, 
					    category::Video, 
					    "Warning: loaded texture's width is not a power of two. Texture ID: %u\n"
					    ,
						tex->getID());
		}
 
		// Also check if the height is a power of 2
		if ( (tex->getHeight() & (tex->getHeight() - 1)) != 0 ) {
			logger::Log(priority::Warning, 
					    output_stream::All, 
					    category::Video, 
					    "Warning: loaded texture's height is not a power of two. Texture ID: %u\n"
					    ,
						tex->getID());
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
		auto StretchingProperty = GL_REPEAT;
		if (!repeat) StretchingProperty = GL_CLAMP_TO_EDGE;

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, StretchingProperty);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, StretchingProperty);
		
		// really loading for the first time but reload works if texture ID has been generated
		reloadTexture(tex);
	}

	// Reload the texture from the SDL surface.
	// It is assumed that the characteristics of the texture are unchanged
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
		const char *formatString;

		if (texture_format == GL_RGBA) {
			formatString = "GL_RGBA";
		} else if (texture_format == GL_RGB) {
			formatString = "GL_RGB";

		} else if (texture_format == GL_BGRA) {
			formatString = "GL_BGRA";
		} else if (texture_format == GL_BGR) {
			formatString = "GL_BGRA";
		} else {
			formatString = "Unknown?!";
		}
		logger::Log(priority::Tracing,
					output_stream::File,
					category::Video,
					"Reloading texture.... Properties: "
					"Mode:    %s "
					,
					formatString);

		// Bind the texture object
		glBindTexture( GL_TEXTURE_2D, textureID );
		 
		// Load the image
		glTexImage2D(GL_TEXTURE_2D, 0, nOfColors, tex->getSurface()->w, tex->getSurface()->h, 0, texture_format, GL_UNSIGNED_BYTE, tex->getSurface()->pixels);

		if (tex->getMipmap()) {
			// have GLU build mipmaps
			int err = gluBuild2DMipmaps(GL_TEXTURE_2D, nOfColors, tex->getSurface()->w, tex->getSurface()->h, texture_format, GL_UNSIGNED_BYTE, tex->getSurface()->pixels);
			if (err != 0) {
				logger::Log(priority::Warning,
							output_stream::All,
							category::Video,
							"Failed to generate mipmaps : %s", gluErrorString(err));
			}
		}
	}

	void GLRenderer::unloadTexture(Texture *tex)
	{
		logger::Log(priority::Tracing,
					output_stream::File,
					category::Video,
					"Unloaded texture, ID: %u", tex->getID());
		GLuint textureID = tex->getID();
		glDeleteTextures(1, &textureID);
	}

	/* 
	 * Given the relative path `"Resources/Sunny1"`, this will attempt to load skybox as...
	 * ` "Sunny1_" + ["up" | "down" | "left" | "right" | "front" | "back"] + ".bmp"`
	 *
	 * \param tex path and base name of texture
	 *
	 * \note The path is relative. No attempt is made to handle UTF16 paths or non bitmap files.
	 */
	void GLRenderer::loadSkybox(std::string tex) {
		logger::Log(priority::Tracing,
					output_stream::File,
					category::Video,
					"Loading skybox sides :: %s", tex.c_str());

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

	// is there a existing 2D overlay using this texture?
	bool GLRenderer::exists2DOverlay(Texture *texture)
	{
		for (auto &overlay: overlays)
		{
			if (overlay->texture == texture) return true;
		}
		return false;
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
		for (auto &overlay: overlays)
		{
			if (overlay->texture == texture)
			{
				overlays.remove(overlay);
				return;
			}
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
		{
			/* Recall that the origin is in the lower-left corner and in clip space / screen space, Y increases upwards.
			   That is why the TexCoords specify different corners than the Vertex coords seem to. */
			float xLeft   = float(x);
			float xRight  = float(x + w);
			float yBottom = float(y);
			float yTop    = float(y + h);

			glTexCoord2f(0.0f, 1.0f);  glVertex2f(xLeft,  yBottom);
			glTexCoord2f(1.0f, 1.0f);  glVertex2f(xRight, yBottom);
			glTexCoord2f(1.0f, 0.0f);  glVertex2f(xRight, yTop);
			glTexCoord2f(0.0f, 0.0f);  glVertex2f(xLeft,  yTop);
		}
		glEnd();

		glDisable(GL_TEXTURE_2D);

		glFinish();
	}


	// Show all diagnostic messages
	// Messages are rendered and then deleted. A persistant message must be added every frame
	// This isn't ideal but a better soloution would be to implement 2D sprites withing
	void GLRenderer::showD2DOverlays()
	{
		if (overlays.empty()) return;

		// Orthographic projection view is fixed to the GL viewport size.
		int vPort[4] = {0};
		glGetIntegerv(GL_VIEWPORT, vPort);

		auto near   = -1;
		auto far    = 1;
		auto left   = 0;
		auto right  = vPort[2];
		auto bottom = 0;
		auto top    = vPort[3];

		// temp hardwired camera for overlay
		Camera overlayCam = Camera(near, far, left, right, bottom, top);		
		setCamera(&overlayCam);

		glDisable(GL_DEPTH_TEST);		
		glDisable(GL_LIGHTING);
		glDisable(GL_FOG);

		glEnable(GL_BLEND);                         // Enable Blending
		//glBlendFunc(GL_SRC_COLOR,GL_ONE);			// transparent black background (sort of)
		glBlendFunc(GL_ONE,GL_ONE);					// add overlay (works well for white text)

		for (auto &overlay : overlays)
		{
			glMatrixMode(GL_MODELVIEW);
			glPushMatrix();
			glLoadIdentity();

			draw2DMesh(overlay);
			glPopMatrix();
		}
		glDisable(GL_BLEND);
	}

}
