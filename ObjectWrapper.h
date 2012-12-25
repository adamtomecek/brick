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

	virtual void ApplyForce(float forceX, float forceY, float pointX, float pointY){
		call<void>("ApplyForce", forceX, forceY, pointX, pointY);
	}

	static void default_ApplyForce(Object *ptr, float forceX, float forceY,
			float pointX, float pointY){
		return ptr->Object::ApplyForce(forceX, forceY, pointX, pointY);
	}

	virtual void ApplyForceToCenter(float forceX, float forceY){
		call<void>("ApplyForceToCenter", forceX, forceY);
	}

	static void default_ApplyForceToCenter(Object *ptr, float forceX, float forceY){
		return ptr->Object::ApplyForceToCenter(forceX, forceY);
	}

	virtual void ApplyTorque(float32 torque){
		call<void>("ApplyTorque", torque);
	}

	static void default_ApplyTorque(Object *ptr, float32 torque){
		return ptr->Object::ApplyTorque(torque);
	}

	virtual void ApplyLinearImpulse(float impX, float impY, float pointX,
			float pointY){
		call<void>("ApplyLinearImpulse", impX, impY, pointX, pointY);
	}

	static void default_ApplyLinearImpulse(Object *ptr, float impX,
			float impY, float pointX, float pointY){
		return ptr->Object::ApplyLinearImpulse(impX, impY, pointX, pointY);
	}

	virtual void ApplyAngularImpulse(float32 impulse){
		call<void>("ApplyAngularImpulse", impulse);
	}

	static void default_ApplyAngularImpulse(Object *ptr, float32 impulse){
		return ptr->Object::ApplyAngularImpulse(impulse);
	}

	static void Lua(lua_State *lua){
		luabind::module(lua)
		[
		luabind::class_<Object, ObjectWrapper, Chunk,
			boost::shared_ptr<Node> >("Object")
			.def(luabind::constructor<Chunk *>(),
					luabind::adopt(luabind::result))
			.def("ApplyForce", &Object::ApplyForce,
					&ObjectWrapper::default_ApplyForce)
			.def("ApplyForceToCenter", &Object::ApplyForceToCenter,
					&ObjectWrapper::default_ApplyForceToCenter)
			.def("ApplyTorque", &Object::ApplyTorque,
					&ObjectWrapper::default_ApplyTorque)
			.def("ApplyLinearImpulse", &Object::ApplyLinearImpulse,
					&ObjectWrapper::default_ApplyLinearImpulse)
			.def("ApplyAngularImpulse", &Object::ApplyAngularImpulse,
					&ObjectWrapper::default_ApplyAngularImpulse)
		];
	}

};

#endif
