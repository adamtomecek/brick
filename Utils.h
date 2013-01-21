/*
 *  Utils.h
 *  sfml
 *
 *  Created by Adam Tomeček on 7/15/12.
 *  Copyright 2012 Brain Dead Cookie. All rights reserved.
 *
 */

#ifndef UTILS_H
#define UTILS_H

#include "Includes.h"
#include "lua.h"
#include "lualib.h"

struct Position{
	float x;
	float y;
	float z;
};

struct Size{
	float width;
	float height;
};

struct PointRotation{
	float x;
	float y;
	float angle;
};

struct Point{
	float x;
	float y;
};

class Utils{
public:
	static Utils& GetInstance(){
		static  Utils *singleClass = NULL;
		if (singleClass == NULL)
			singleClass = new Utils;
		return *singleClass;
	}
	
	static b2World* GetWorld(){
		return world;
	}
	
	static b2World* SetWorld(b2World *w){
		world = w;
	}

	static lua_State* SetLuaState(lua_State *s){
		luaState = s;
	}

	static lua_State* GetLuaState(){
		return luaState;
	}

	static sem_t* GetBoxSem(void){
		return boxSem;
	}

	static void SetBoxSem(sem_t *sem){
		boxSem = sem;
	}
private:
	Utils();
        // Dont forget to declare these two. You want to make sure they
        // are unaccessable otherwise you may accidently get copies of
        // your singleton appearing.
	Utils(Utils const&);              // Don't Implement
	void operator=(Utils const&); // Dont implement
	
	static b2World *world;
	static lua_State *luaState;
	static sem_t* boxSem;
};


#endif

