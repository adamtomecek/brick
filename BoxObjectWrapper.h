/*
 *  BoxObjectWrapper.h
 *  sfml
 *
 *  Created by Adam Tomeček on 12/3/12.
 *  Copyright 2012 Brain Dead Cookie. All rights reserved.
 *
 */

#ifndef BOX_OBJECT_WRAPPER_H
#define BOX_OBJECT_WRAPPER_H

#include "Includes.h"
#include "BoxObject.h"

struct BoxObjectWrapper : BoxObject, luabind::wrap_base{

	BoxObjectWrapper(Chunk *representation) :
		BoxObject(representation) {}	

	BoxObjectWrapper(float width, float height, float xPos, float yPos,
			float angle = 0.0f) :
		BoxObject(width, height, xPos, yPos, angle) {}	

	static void Lua(lua_State *lua){
		luabind::module(lua)
		[
		 luabind::class_<BoxObject, BoxObjectWrapper, Object,
			boost::shared_ptr<Node> >("BoxObject")
		 .def(luabind::constructor<Chunk *>(), luabind::adopt(luabind::result))
		 /* .def(luabind::constructor<b2World *, boost::shared_ptr<Chunk> >()) */
		 /* .def(luabind::constructor<b2World *, float, float, float, float>()) */
		 .def(luabind::constructor<float, float, float, float>())
		 ];
	}

};

#endif
 
