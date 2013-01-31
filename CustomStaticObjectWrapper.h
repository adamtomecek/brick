/*
 *  CustomStaticObjectWrapper.h
 *  sfml
 *
 *  Created by Adam Tomeček on 1/31/13.
 *  Copyright 2013 Brain Dead Cookie. All rights reserved.
 *
 */

#ifndef CUSTOM_STATIC_OBJECT_WRAPPER_H
#define CUSTOM_STATIC_OBJECT_WRAPPER_H

#include "Includes.h"
#include "CustomStaticObject.h"

struct CustomStaticObjectWrapper : CustomStaticObject, luabind::wrap_base{

	CustomStaticObjectWrapper(Chunk *representation, std::string data) :
		CustomStaticObject(representation, data) {}

	static void Lua(lua_State *lua){
		luabind::module(lua)
		[
		 luabind::class_<CustomStaticObject, CustomStaticObjectWrapper, Object,
			boost::shared_ptr<Node> >("CustomStaticObject")
		 .def(luabind::constructor<Chunk *, std::string>(),
				 luabind::adopt(luabind::result))
		];
	}
};

#endif

