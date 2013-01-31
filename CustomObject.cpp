/*
 *  CustomObject.cpp
 *  sfml
 *
 *  Created by Adam Tomeček on 12/27/12.
 *  Copyright 2012 Brain Dead Cookie. All rights reserved.
 *
 */
#include "CustomObject.h"

void CustomObject::DefineBody(void){
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

