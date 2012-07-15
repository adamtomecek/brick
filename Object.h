/*
 *  Object.h
 *  sfml
 *
 *  Created by Adam Tomeček on 6/18/12.
 *  Copyright 2012 Brain Dead Cookie. All rights reserved.
 *
 */


#include "Game.h"

class Object{
	public:
		Object(b2World *world, float width, float height, float xPos, float yPos, float zPos);
		int move(float xMove, float yMove, float zMove);

		int draw(void);
		int applyPhysics(void);

		int remove(void);

		float getXPos(void);
		float getYPos(void);
		float getZPos(void);
	private:
		float xPos;
		float yPos;
		float zPos;
		float angle;

		float width;
		float height;

		b2World *world;
		b2Body *body;
};
