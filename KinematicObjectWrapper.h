/*
 *  KinematicBodyWrapper.h
 *  sfml
 *
 *  Created by Adam Tomeček on 2/1/13.
 *  Copyright 2013 Brain Dead Cookie. All rights reserved.
 *
 */

#ifndef KINEMATIC_OBJECT_WRAPPER_H
#define KINEMATIC_OBJECT_WRAPPER_H

#include "Includes.h"
#include "KinematicObject.h"

struct KinematicObjectWrapper : KinematicObject, luabind::wrap_base{

	KinematicObjectWrapper(Chunk *representation) :
		KinematicObject(representation) {}	

	KinematicObjectWrapper(float width, float height, float xPos, float yPos) :
		KinematicObject(width, height, xPos, yPos) {}	

	static void Lua(lua_State *lua){
		luabind::module(lua)
		[
		 luabind::class_<KinematicObject, KinematicObjectWrapper, Object,
			boost::shared_ptr<Node> >("KinematicObject")
		 .def(luabind::constructor<Chunk *>(),
			 luabind::adopt(luabind::result))
		 .def(luabind::constructor<float, float, float, float>())
		 ];
	}

};

#endif
