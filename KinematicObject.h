/*
 *  KinematicObject.h
 *  sfml
 *
 *  Created by Adam Tomeček on 2/1/13.
 *  Copyright 2013 Brain Dead Cookie. All rights reserved.
 *
 */

#ifndef KINEMATIC_OBJECT_H
#define KINEMATIC_OBJECT_H

#include "Object.h"

class KinematicObject : public Object{
		public: 
		explicit KinematicObject(Chunk *representation) : 
			Object::Object(representation) {
				this->CreateBody();
			}

		explicit KinematicObject(float width, float height, float xPos, float yPos,
				float angle = 0.0f) : 
			Object::Object(width, height, xPos, yPos, angle) {
				this->CreateBody();
			}

	protected:
		virtual void CreateBody(void);

};

#endif

