/*
 *  CircleObject.h
 *  sfml
 *
 *  Created by Adam Tomeček on 7/27/12.
 *  Copyright 2012 Brain Dead Cookie. All rights reserved.
 *
 */

#ifndef CIRCLEOBJECT_H
#define CIRCLEOBJECT_H

#include "Game.h"
#include "Object.h"

class CircleObject : public Object {
public:
	explicit CircleObject(b2World *world, float radius, 
					   float xPos, float yPos, float angle = 0.0f): 
	Object::Object(world, radius, radius, xPos, yPos, angle) {
		this->DefineBody();
	}
	explicit CircleObject(b2World *world, Chunk *representation) : 
	Object::Object(world, representation) {
		this->DefineBody();
	}
	
	virtual void DefineBody(void);
};

#endif
