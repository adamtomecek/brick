/*
 *  CircleObjectWrapper.h
 *  sfml
 *
 *  Created by Adam Tomeček on 12/3/12.
 *  Copyright 2012 Brain Dead Cookie. All rights reserved.
 *
 */

#ifndef CIRCLE_OBJECT_WRAPPER_H
#define CIRCLE_OBJECT_WRAPPER_H

#include "Includes.h"
#include "CircleObject.h"

struct CircleObjectWrapper : CircleObject, luabind::wrap_base{

	CircleObjectWrapper(Chunk *representation) :
		CircleObject(representation) {}	

	CircleObjectWrapper(float radius, float xPos, float yPos,
			float angle = 0.0f) :
		CircleObject(radius, xPos, yPos, angle) {}	

	static void Lua(lua_State *lua){
		luabind::module(lua)
		[
		 luabind::class_<CircleObject, CircleObjectWrapper, Object,
			boost::shared_ptr<Node> >("CircleObject")
		 .def(luabind::constructor<Chunk *>(), luabind::adopt(luabind::result))
		 /* .def(luabind::constructor<b2World *, boost::shared_ptr<Chunk> >()) */
		 /* .def(luabind::constructor<b2World *, float, float, float, float>()) */
		 .def(luabind::constructor<float, float, float, float>())
		 ];
	}

};

#endif
 
