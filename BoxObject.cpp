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
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set((this->xPos + this->width / 2)/ RATIO, 
						 (this->yPos + this->height / 2) / RATIO);
	bodyDef.angle = this->angle * (M_PI / 180);

	this->body = Utils::GetWorld()->CreateBody(&bodyDef);

	b2PolygonShape box;
	box.SetAsBox((this->width / 2) / RATIO, (this->height / 2) / RATIO);

	b2FixtureDef shapeDef;
	shapeDef.shape = &box;
	shapeDef.density = 0.8f;
	shapeDef.friction = 0.3f;
	shapeDef.restitution = 0.2f;

	this->body->CreateFixture(&shapeDef);
}

