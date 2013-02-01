/*
 *  DynamicObjectWrapper.h
 *  sfml
 *
 *  Created by Adam Tomeček on 1/31/13.
 *  Copyright 2013 Brain Dead Cookie. All rights reserved.
 *
 */

#ifndef DYNAMIC_OBJECT_WRAPPER_H
#define DYNAMIC_OBJECT_WRAPPER_H

#include "Includes.h"
#include "DynamicObject.h"

struct DynamicObjectWrapper : DynamicObject, luabind::wrap_base{

	DynamicObjectWrapper(Chunk *representation) :
		DynamicObject(representation) {}	

	static void Lua(lua_State *lua){
		luabind::module(lua)
		[
		 luabind::class_<DynamicObject, DynamicObjectWrapper, Object,
			boost::shared_ptr<Node> >("DynamicObject")
		 .def(luabind::constructor<Chunk *>(), luabind::adopt(luabind::result))
		 /* .def(luabind::constructor<b2World *, boost::shared_ptr<Chunk> >()) */
		 /* .def(luabind::constructor<b2World *, float, float, float, float>()) */
		 /* .def(luabind::constructor<float, float, float, float>()) */
		 ];
	}

};

#endif
 
