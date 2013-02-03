/*
 *  KinematicObject.cpp
 *  sfml
 *
 *  Created by Adam Tomeček on 2/1/13.
 *  Copyright 2013 Brain Dead Cookie. All rights reserved.
 *
 */

#include "KinematicObject.h"

void KinematicObject::CreateBody(void){
	b2BodyDef bodyDef;
	bodyDef.type = b2_kinematicBody;
	bodyDef.position.Set((this->xPos + this->width / 2) / RATIO,
						 (this->yPos + this->height / 2)/ RATIO);
	bodyDef.angle = this->angle * (M_PI / 180);
	
	this->body = this->world->CreateBody(&bodyDef);

	return ;
}

