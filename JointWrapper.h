/*
 *  JointWrapper.h
 *  sfml
 *
 *  Created by Adam Tomeček on 2/1/13.
 *  Copyright 2013 Brain Dead Cookie. All rights reserved.
 *
 */

#ifndef JOINT_WRAPPER_H
#define JOINT_WRAPPER_H

#include "Includes.h"
#include "Joint.h"

struct JointWrapper : Joint, luabind::wrap_base{

	JointWrapper(Object *a, Object *b) :
		Joint(a, b) {}

	virtual void Revolue(float x, float y){
		call<void>("Revolute", x, y);
	}

	static void default_Revolute(Joint *ptr, float x, float y){
		return ptr->Joint::Revolute(x, y);
	}

	static void Lua(lua_State *lua){
		luabind::module(lua)
		[
		 luabind::class_<Joint, JointWrapper, Node,
			boost::shared_ptr<Node> >("Joint")
		 .def(luabind::constructor<Object *, Object *>())

		.def("Revolute", &Joint::Revolute,
				&JointWrapper::default_Revolute)
		 ];
	}

};

#endif

