/*
 *  Joint.h
 *  sfml
 *
 *  Created by Adam Tomeček on 2/1/13.
 *  Copyright 2013 Brain Dead Cookie. All rights reserved.
 *
 */

#ifndef JOINT_H
#define JOINT_H

#include "Includes.h"
#include "Node.h"
#include "Object.h"

enum JointType{
	REVOLUTE
};

class Joint : public Node{
	public:
		Joint(Object *a, Object *b);	
		void Revolute(float x, float y);

	private:
		Object *a;
		Object *b;
		int type;
		void *joint;

};

#endif

