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
#include "vjson/json.h"
/* #include "block_allocator.h" */

enum{
	X, Y
};

class CustomObject : public Object{
	public: 
		explicit CustomObject(Chunk *representation, std::string data) : 
		Object::Object(representation) {
			this->LoadJSON(data);
			this->DefineBody();
		}

		virtual void DefineBody(void);

	private:
		void LoadJSON(std::string file);
		void LoadVertexes(json_value *root);
		void PrintTree(json_value *root, int ident);

		std::list<Point> points;
};

#endif

