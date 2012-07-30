/*
 *  Scene.h
 *  sfml
 *
 *  Created by Adam Tomeček on 7/10/12.
 *  Copyright 2012 Brain Dead Cookie. All rights reserved.
 *
 */


#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include <OpenGL/CGLTypes.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

class Scene{
	public:
		Scene();
		void drawFPS(float fps);
	
	private:
		float calculateFPS(void);
		void printw(float x, float y, float z, const char* format, ...);

		float frameCount;

		float previousTime;
		float currentTime;

};
