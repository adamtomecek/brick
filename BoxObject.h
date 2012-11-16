/*
 *  BoxObject.h
 *  sfml
 *
 *  Created by Adam Tomeček on 7/27/12.
 *  Copyright 2012 Brain Dead Cookie. All rights reserved.
 *
 */

#ifndef BOXOBJECT_H
#define BOXOBJECT_H

#include "Game.h"
#include "Object.h"

class BoxObject : public Object {
	public:
		explicit BoxObject(b2World *world, float width, float height, 
				float xPos, float yPos, float angle = 0.0f): 
			Object::Object(world, width, height, xPos, yPos, angle) {
				this->DefineBody();
			}
		explicit BoxObject(b2World *world, Chunk *representation) :
			Object::Object(world, representation) {
				this->DefineBody();
			}
	explicit BoxObject(float width, float height, 
					   float xPos, float yPos, float angle = 0.0f): 
	Object::Object(width, height, xPos, yPos, angle) {
		this->DefineBody();
	}
	explicit BoxObject(Chunk *representation) : 
	Object::Object(representation) {
		this->DefineBody();
	}

		virtual void DefineBody(void);


	/* Lua binding */
	static void Lua(lua_State *lua){
		luabind::module(lua)
		[
		 luabind::class_<BoxObject, Object, boost::shared_ptr<Node> >("BoxObject")
		 .def(luabind::constructor<Chunk* >(), luabind::adopt(luabind::result))
		 /* .def(luabind::constructor<b2World *, boost::shared_ptr<Chunk> >()) */
		 /* .def(luabind::constructor<b2World *, float, float, float, float, float>()) */
		 .def(luabind::constructor<float, float, float, float, float>())
		 ];
	}
};

#endif
