/*
 *  DynamicObject.h
 *  sfml
 *
 *  Created by Adam Tomeček on 1/31/13.
 *  Copyright 2013 Brain Dead Cookie. All rights reserved.
 *
 */

#ifndef DYNAMIC_OBJECT_H
#define DYNAMIC_OBJECT_H

#include "Object.h"

class DynamicObject : public Object{
	public: 
		explicit DynamicObject(Chunk *representation) : 
			Object::Object(representation) {
				this->CreateBody();
			}

		explicit DynamicObject(float width, float height, float xPos,
				float yPos) : Object::Object(width, height, xPos, yPos) {
				this->CreateBody();
			}

	protected:
		virtual void CreateBody(void);

};

#endif

