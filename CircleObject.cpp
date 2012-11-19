/*
 *  CircleObject.cpp
 *  sfml
 *
 *  Created by Adam Tomeček on 7/27/12.
 *  Copyright 2012 Brain Dead Cookie. All rights reserved.
 *
 */

#include "CircleObject.h"

void CircleObject::DefineBody(void){
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set((this->xPos + this->width / 2) / RATIO,
						 (this->yPos + this->height / 2)/ RATIO);
	bodyDef.angle = this->angle * (M_PI / 180);
	
	this->body = this->world->CreateBody(&bodyDef);
	
	b2CircleShape circle;
	circle.m_radius = (this->width / RATIO) / 2;
	
	b2FixtureDef shapeDef;
	shapeDef.shape = &circle;
	
	shapeDef.density = 1.0f;
	shapeDef.friction = 0.8f;
	shapeDef.restitution = 0.2f;
	
	this->body->CreateFixture(&shapeDef);
}
