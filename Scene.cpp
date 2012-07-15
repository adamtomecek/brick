/*
 *  Scene.cpp
 *  sfml
 *
 *  Created by Adam Tomeček on 7/10/12.
 *  Copyright 2012 Brain Dead Cookie. All rights reserved.
 *
 */

#include "Scene.h"

Scene::Scene(){
	this->frameCount = 0;
	this->previousTime = 0;
	this->currentTime = 0;
}

void Scene::drawFPS(float fps){
	printw(20, 20, 0, "FPS: %4.2f", fps);
}

float Scene::calculateFPS(void){
	float fps = 0;

	this->frameCount++;

	this->currentTime = glutGet(GLUT_ELAPSED_TIME);

	int timeInterval = this->currentTime - this->previousTime;

	if(timeInterval > 1000){
		fps = this->frameCount / (timeInterval / 1000.0f);

		this->previousTime = this->currentTime;

		this->frameCount = 0;
	}

	return fps;
}

void Scene::printw (float x, float y, float z, char* format, ...)
{
	va_list args;	//  Variable argument list
	int len;		//	String length
	int i;			//  Iterator
	char * text;	//	Text

	//  Initialize a variable argument list
	va_start(args, format);

	//  Return the number of characters in the string referenced the list of arguments.
	//  _vscprintf doesn't count terminating '\0' (that's why +1)
	len = vsnprintf(NULL, 0, format, args) + 1; 

	//  Allocate memory for a string of the specified size
	text = (char *)malloc(len * sizeof(char));

	//  Write formatted output using a pointer to the list of arguments
	vsnprintf(text, len, format, args);

	//  End using variable argument list 
	va_end(args);

	//  Specify the raster position for pixel operations.
	glRasterPos2f(x, y);

	GLvoid *font_style = GLUT_BITMAP_TIMES_ROMAN_24;

	//  Draw the characters one by one
	glPushAttrib(GL_CURRENT_BIT);
	glColor4f(1.f, 0.f, 0.f, 0.f);

    for (i = 0; text[i] != '\0'; i++)
        glutBitmapCharacter(font_style, text[i]);

	glPopAttrib();

	//  Free the allocated memory for the string
	free(text);
}

