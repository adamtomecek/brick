/*
 *  Joint.cpp
 *  sfml
 *
 *  Created by Adam Tomeček on 2/1/13.
 *  Copyright 2013 Brain Dead Cookie. All rights reserved.
 *
 */

#include "Joint.h"

Joint::Joint(Object *a, Object *b){
	this->a = a;
	this->b = b;
}

void Joint::Revolute(float x, float y){
	this->type = REVOLUTE;

	b2RevoluteJointDef jointDef;

	b2Vec2 anchor(x / RATIO, y / RATIO);

	jointDef.Initialize(this->a->GetBody(), this->b->GetBody(), anchor);
	jointDef.enableLimit = true;
	this->joint = Utils::GetWorld()->CreateJoint(&jointDef);

}

