#ifndef __MODULETEXT_H__
#define  __MODULETEXT_H__

#include "Module.h"
#include "Globals.h"

// FreeType Headers

#include <freetype/config/ft2build.h>
#include <freetype/freetype.h>
#include <freetype/ftglyph.h>


#include "../Libraries/OpenGL/include/GL/glew.h"

// Some STL Headers
#include <vector>
#include <string>

// Using The STL Exception Library Increases The
// Chances That Someone Else Using Our Code Will Correctly
// Catch Any Exceptions That We Throw.
#include <stdexcept>

// MSVC Will Spit Out All Sorts Of Useless Warnings If
// You Create Vectors Of Strings, This Pragma Gets Rid Of Them.
#pragma warning(disable: 4786)

// This Holds All Of The Information Related To Any
// FreeType Font That We Want To Create. 
struct font_data {
		float h;                                        // Holds The Height Of The Font.
		GLuint * textures;                                  // Holds The Texture Id's
		GLuint list_base;                                   // Holds The First Display List Id

		

		// The Init Function Will Create A Font With
															// The Height h From The File fname.
		void init(const char * fname, unsigned int h);

		// This Function Gets The First Power Of 2 >= The
		// Int That We Pass It.
		inline int next_p2(int a)
		{
			int rval = 1;
			// rval<<=1 Is A Prettier Way Of Writing rval*=2;
			while (rval<a) rval <<= 1;
			return rval;
		}

		void make_dlist(FT_Face face, char ch, GLuint list_base, GLuint * tex_base);

		// Free All The Resources Associated With The Font.
		void clean();

	
};

class ModuleText : public Module
{
public:

	ModuleText(bool start_enabled = true);
	~ModuleText();

	bool Init();
	bool CleanUp();

	// A Fairly Straightforward Function That Pushes
	// A Projection Matrix That Will Make Object World
	// Coordinates Identical To Window Coordinates.
	inline void pushScreenCoordinateMatrix() {
		glPushAttrib(GL_TRANSFORM_BIT);
		GLint   viewport[4];
		glGetIntegerv(GL_VIEWPORT, viewport);
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		gluOrtho2D(viewport[0], viewport[2], viewport[1], viewport[3]);
		glPopAttrib();
	}

	// Pops The Projection Matrix Without Changing The Current
	// MatrixMode.
	inline void pop_projection_matrix() {
		glPushAttrib(GL_TRANSFORM_BIT);
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glPopAttrib();
	}

	void print(const font_data &ft_font, float x, float y, const char *fmt, ...);

	
};

#endif 