/*
 *  SceneWrapper.h
 *  sfml
 *
 *  Created by Adam Tomeček on 11/19/12.
 *  Copyright 2012 Brain Dead Cookie. All rights reserved.
 *
 */


#ifndef SCENE_WRAPPER_H
#define SCENE_WRAPPER_H

#include "Includes.h"
#include "Scene.h"

struct SceneWrapper: Scene, luabind::wrap_base{
	SceneWrapper()
		: Scene()
			{}

    virtual void KeyboardInput(unsigned short keyCode){
         call<void>("KeyboardInput", keyCode);
    }

	static void default_KeyboardInput(Scene* ptr, unsigned short keyCode){
		return ptr->Scene::KeyboardInput(keyCode);
	}

    virtual void MouseInput(unsigned int x, unsigned int y, short buttonCode){
         call<void>("MouseInput", x, y, buttonCode);
    }

    static void default_MouseInput(Scene *ptr, unsigned int x, unsigned int y,
			short buttonCode){
		return ptr->Scene::MouseInput(x, y, buttonCode);
	}

	static void Lua(lua_State *lua){
		luabind::module(lua)
		[
		luabind::class_<Scene, SceneWrapper, Node >("Scene")
			.def(luabind::constructor<>())
			.def("KeyboardInput", &Scene::KeyboardInput,
					&SceneWrapper::default_KeyboardInput)
			.def("MouseInput", &Scene::MouseInput,
					&SceneWrapper::default_KeyboardInput)
		];
	}
};	

#endif

