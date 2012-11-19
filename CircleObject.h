/*
 *  CircleObject.h
 *  sfml
 *
 *  Created by Adam Tomeček on 7/27/12.
 *  Copyright 2012 Brain Dead Cookie. All rights reserved.
 *
 */

#ifndef CIRCLEOBJECT_H
#define CIRCLEOBJECT_H

#include "Includes.h"
#include "Object.h"

class CircleObject : public Object {
public:
	explicit CircleObject(b2World *world, float radius, 
					   float xPos, float yPos, float angle = 0.0f): 
	Object::Object(world, radius, radius, xPos, yPos, angle) {
		this->DefineBody();
	}
	explicit CircleObject(b2World *world, Chunk *representation) : 
	Object::Object(world, representation) {
		this->DefineBody();
	}
	explicit CircleObject(float radius, 
						  float xPos, float yPos, float angle = 0.0f): 
	Object::Object(radius, radius, xPos, yPos, angle) {
		this->DefineBody();
	}
	explicit CircleObject(Chunk *representation) : 
	Object::Object(representation) {
		this->DefineBody();
	}
	
	virtual void DefineBody(void);


	/* Lua binding */
	static void Lua(lua_State *lua){
		luabind::module(lua)
		[
		 luabind::class_<CircleObject, Object, boost::shared_ptr<Node> >("CircleObject")
		 .def(luabind::constructor<Chunk *>(), luabind::adopt(luabind::result))
		 /* .def(luabind::constructor<b2World *, boost::shared_ptr<Chunk> >()) */
		 /* .def(luabind::constructor<b2World *, float, float, float, float>()) */
		 .def(luabind::constructor<float, float, float, float>())
		 ];
	}
};

#endif
