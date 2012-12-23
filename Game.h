/*
 *  Game.h
 *  sfml
 *
 *  Created by Adam Tomeček on 7/11/12.
 *  Copyright 2012 Brain Dead Cookie. All rights reserved.
 *
 */

#ifndef GAME_H
#define GAME_H

#include "Includes.h"
#include "DebugDraw.h"
#include "Input.h"
#include "Scene.h"

/* #define RATIO 100.0f */
/* #define TIME_STEP 1.0f / 60.0f */
/* #define VELOCITY_ITERATIONS 8 */
/* #define POSITION_ITERATIONS 3 */
#define DEBUG_DRAW false

	//b2World *wrld;

class Game{
	public:
		Game();
		virtual int Loop(void);
		virtual void Step(void);
		void SetScene(Scene *s);

		Input *input;

		static void Lua(lua_State *lua){
			luabind::module(lua)
			[
			luabind::class_<Game>("Game")
			.def(luabind::constructor<>())
			.def("Loop", &Game::Loop)
			.def("Step", &Game::Step)
			.def("SetScene", &Game::SetScene)
			];
		}

	private:
		void Setup(void);
		void HandleInput(void);

		sf::RenderWindow *app;
		sf::WindowSettings *settings;
		sf::Clock *clock;
		b2World *world;
		lua_State *luaState;
		Scene *scene;
		sem_t *b2Sem;
};

#endif

