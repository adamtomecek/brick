/*
 *  BoxObject.cpp
 *  sfml
 *
 *  Created by Adam Tomeček on 7/27/12.
 *  Copyright 2012 Brain Dead Cookie. All rights reserved.
 *
 */

#include "Game.h"
#include "BoxObject.h"

void BoxObject::DefineBody(void){
	std::cout << "child" << std::endl;
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(this->xPos / RATIO, (this->yPos / RATIO + this->height / RATIO));
	
	body = this->world->CreateBody(&bodyDef);
	bodyDef.angle = angle / 2 * M_PI;

	b2CircleShape circle;
	circle.m_radius = (this->width / RATIO) / 2;

	b2FixtureDef shapeDef;
	shapeDef.shape = &circle;
	shapeDef.density = 1.0f;
	shapeDef.friction = 0.2f;
	shapeDef.restitution = 0.5f;

	body->CreateFixture(&shapeDef);

	this->body = body;
}
