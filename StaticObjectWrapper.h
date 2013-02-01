/*
 *  StaticObjectWrapper.h
 *  sfml
 *
 *  Created by Adam Tomeček on 1/31/13.
 *  Copyright 2013 Brain Dead Cookie. All rights reserved.
 *
 */

#ifndef STATIC_OBJECT_WRAPPER_H
#define STATIC_OBJECT_WRAPPER_H

#include "Includes.h"
#include "StaticObject.h"

struct StaticObjectWrapper : StaticObject, luabind::wrap_base{

	StaticObjectWrapper(Chunk *representation) :
		StaticObject(representation) {}	

	StaticObjectWrapper(float width, float height, float xPos, float yPos) :
		StaticObject(width, height, xPos, yPos) {}	

	static void Lua(lua_State *lua){
		luabind::module(lua)
		[
		 luabind::class_<StaticObject, StaticObjectWrapper, Object,
			boost::shared_ptr<Node> >("StaticObject")
		 .def(luabind::constructor<Chunk *>(),
			 luabind::adopt(luabind::result))
		 .def(luabind::constructor<float, float, float, float>())
		 ];
	}

};

#endif
 
