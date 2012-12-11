/*
 *  ObjectWrapper.h
 *  sfml
 *
 *  Created by Adam Tomeček on 12/3/12.
 *  Copyright 2012 Brain Dead Cookie. All rights reserved.
 *
 */

#ifndef OBJECT_WRAPPER_H
#define OBJECT_WRAPPER_H

#include "Includes.h"
#include "Object.h"

struct ObjectWrapper : Object, luabind::wrap_base{

	ObjectWrapper(Chunk *representation) : Object(representation) {}

	static void Lua(lua_State *lua){
		luabind::module(lua)
		[
		luabind::class_<Object, ObjectWrapper, Chunk,
			boost::shared_ptr<Node> >("Object")
			.def(luabind::constructor<Chunk *>(),
					luabind::adopt(luabind::result))
		];
	}

};

#endif
