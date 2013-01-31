/*
 *  CustomStaticObject.cpp
 *  sfml
 *
 *  Created by Adam Tomeček on 1/31/13.
 *  Copyright 2013 Brain Dead Cookie. All rights reserved.
 *
 */

#include "CustomStaticObject.h"

void CustomStaticObject::CreateBody(void){
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set((this->xPos + this->width / 2) / RATIO,
						 (this->yPos + this->height / 2)/ RATIO);
	bodyDef.angle = this->angle * (M_PI / 180);
	
	this->body = this->world->CreateBody(&bodyDef);

	return ;
}

void CustomStaticObject::DefineBody(void){
	this->CreateBody();
	std::list<Point> *points = this->json->GetPoints();
	int size = points->size();
	b2Vec2 verticles[size];

	std::list<Point>::iterator i;
	Point p;	

	int j = 0;	
	for(i = points->begin(); i != points->end(); ++i){
		p = *i;
		verticles[j].Set(p.x, p.y);
		j++;
	}

	b2PolygonShape polygonShape;
	polygonShape.Set(verticles, size);
	
	b2FixtureDef shapeDef;
	shapeDef.shape = &polygonShape;
	shapeDef.density = 0.8f;
	shapeDef.friction = 0.3f;
	shapeDef.restitution = 0.2f;

	this->body->CreateFixture(&shapeDef);
	delete this->json;

	return ;
}

