/*
 *  CustomObjectWrapper.h
 *  sfml
 *
 *  Created by Adam Tomeček on 1/21/13.
 *  Copyright 2013 Brain Dead Cookie. All rights reserved.
 *
 */

#ifndef CUSTOM_OBJECT_WRAPPER_H
#define CUSTOM_OBJECT_WRAPPER_H

#include "Includes.h"
#include "CustomObject.h"

struct CustomObjectWrapper : CustomObject, luabind::wrap_base{

	CustomObjectWrapper(Chunk *representation, std::string data) :
		CustomObject(representation, data) {}

	static void Lua(lua_State *lua){
		luabind::module(lua)
		[
		 luabind::class_<CustomObject, CustomObjectWrapper, Object,
			boost::shared_ptr<Node> >("CustomObject")
		 .def(luabind::constructor<Chunk *, std::string>(),
				 luabind::adopt(luabind::result))
		];
	}
};

#endif

