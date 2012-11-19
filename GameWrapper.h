/*
 *  GameWrapper.h
 *  sfml
 *
 *  Created by Adam Tomeček on 11/18/12.
 *  Copyright 2012 Brain Dead Cookie. All rights reserved.
 *
 */

#ifndef GAME_WRAPPER_H
#define GAME_WRAPPER_H

#include "Includes.h"
#include "Game.h"
#include "Scene.h"

struct GameWrapper: Game, luabind::wrap_base{
	GameWrapper()
		: Game()
			{}

    virtual int Loop(void){
         call<int>("Loop");
    }

	static int default_Loop(Game* ptr){
		return ptr->Game::Loop();
	}

    virtual void Step(void){
         call<void>("Step");
    }

	static void default_Step(Game* ptr){
		return ptr->Game::Step();
	}

    virtual void SetScene(Scene *s){
         call<void>("SetScene", s);
    }

	static void default_SetScene(Game* ptr, Scene *s){
		return ptr->Game::SetScene(s);
	}

	static void Lua(lua_State *lua){
		luabind::module(lua)
		[
		luabind::class_<Game, GameWrapper>("Game")
			.def(luabind::constructor<>())
			.def("Loop", &Game::Loop, &GameWrapper::default_Loop)
			.def("Step", &Game::Step, &GameWrapper::default_Step)
			.def("SetScene", &Game::SetScene, &GameWrapper::default_SetScene)
		];
	}
};	

#endif

