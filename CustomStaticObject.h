/*
 *  CustomStaticObject.h
 *  sfml
 *
 *  Created by Adam Tomeček on 1/31/13.
 *  Copyright 2013 Brain Dead Cookie. All rights reserved.
 *
 */

#ifndef CUSTOM_STATIC_OBJECT_H
#define CUSTOM_STATIC_OBJECT_H
/* #define DEBUG */

#include "Object.h"
#include "JsonLoader.h"

class CustomStaticObject : public Object{
	public: 
	explicit CustomStaticObject(Chunk *representation, std::string data) : 
		Object::Object(representation) {
			this->json = new JsonLoader(data);
			this->CreateBody();
			this->DefineBody();
		}

		virtual void DefineBody(void);
		virtual void CreateBody(void);

	private:
		JsonLoader *json;

};

#endif

