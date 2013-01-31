/*
 *  CustomObject.h
 *  sfml
 *
 *  Created by Adam Tomeček on 12/27/12.
 *  Copyright 2012 Brain Dead Cookie. All rights reserved.
 *
 */

#ifndef CUSTOM_OBJECT_H
#define CUSTOM_OBJECT_H
/* #define DEBUG */

#include "Object.h"
#include "JsonLoader.h"

class CustomObject : public Object{
	public: 
		explicit CustomObject(Chunk *representation, std::string data) : 
		Object::Object(representation) {
			this->json = new JsonLoader(data);
			this->DefineBody();
		}

		virtual void DefineBody(void);
		JsonLoader *json;

};

#endif

