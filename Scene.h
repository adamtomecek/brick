/*
 *  Scene.h
 *  sfml
 *
 *  Created by Adam Tomeček on 7/10/12.
 *  Copyright 2012 Brain Dead Cookie. All rights reserved.
 *
 */

#ifndef SCENE_H
#define SCENE_H

#include "Includes.h"
#include "Node.h"

class Scene : public Node{
	public:
		Scene();
		void drawFPS(float fps);

		virtual void KeyboardInput(unsigned short keyCode);
		virtual void MouseInput(unsigned int x, unsigned int y,
				short buttonCode);

	private:
		float calculateFPS(void);
		void printw(float x, float y, float z, const char* format, ...);

		float frameCount;

		float previousTime;
		float currentTime;


};

#endif

