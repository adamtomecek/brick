/*
 *  BoxObject.cpp
 *  sfml
 *
 *  Created by Adam Tomeček on 7/27/12.
 *  Copyright 2012 Brain Dead Cookie. All rights reserved.
 *
 */


#include "BoxObject.h"

void BoxObject::DefineBody(void){
	b2PolygonShape box;
	box.SetAsBox((this->width / 2) / RATIO, (this->height / 2) / RATIO);

	b2FixtureDef shapeDef;
	shapeDef.shape = &box;
	shapeDef.density = 0.8f;
	shapeDef.friction = 0.3f;
	shapeDef.restitution = 0.2f;

	this->body->CreateFixture(&shapeDef);
}

