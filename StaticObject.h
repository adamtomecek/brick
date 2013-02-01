/*
 *  StaticObject.h
 *  sfml
 *
 *  Created by Adam Tomeček on 1/31/13.
 *  Copyright 2013 Brain Dead Cookie. All rights reserved.
 *
 */

#ifndef STATIC_OBJECT_H
#define STATIC_OBJECT_H

#include "Object.h"

class StaticObject : public Object{
		public: 
		explicit StaticObject(Chunk *representation) : 
			Object::Object(representation) {
				this->CreateBody();
			}

		explicit StaticObject(float width, float height, float xPos, float yPos,
				float angle = 0.0f) : 
			Object::Object(width, height, xPos, yPos, angle) {
				this->CreateBody();
			}

	protected:
		virtual void CreateBody(void);

};

#endif

