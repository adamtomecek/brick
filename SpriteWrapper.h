/*
 *  SpriteWrapper.h
 *  sfml
 *
 *  Created by Adam Tomeček on 12/3/12.
 *  Copyright 2012 Brain Dead Cookie. All rights reserved.
 *
 */

#ifndef SPRITE_WRAPPER_H
#define SPRITE_WRAPPER_H

#include "Includes.h"
#include "Sprite.h"

struct SpriteWrapper : Sprite, luabind::wrap_base{

	SpriteWrapper(float width, float height, float xPos, float yPos,
			float zPos = 0.0f, float angle = 0.0f) : 
		Sprite(width, height, xPos, yPos, zPos, angle){}

	SpriteWrapper(std::string texture, float xPos, float yPos,
			float zPos, float angle) : 
		Sprite(texture, xPos, yPos, zPos, angle){}

	SpriteWrapper(std::string texture, float width, float height,
			float xPos, float yPos,	float zPos, float angle): 
		Sprite(texture, width, height, xPos, yPos, zPos, angle){}

	/* SpriteWrapper(std::string texture, float widht, float height, */
	/* 		float xPos, float yPos,	float zPos, float angle = 0.0f): */ 
	/* 	Sprite(texture, width, height, xPos, yPos, zPos, angle){} */

	static void Lua(lua_State *lua){
		luabind::module(lua)
		[
		 luabind::class_<Sprite, SpriteWrapper, Chunk, 
			boost::shared_ptr<Node> >("Sprite")
		 .def(luabind::constructor<float, float, float, float, float,
				 float>())
		 .def(luabind::constructor<std::string, float, float, float,float>())
		 .def(luabind::constructor<std::string, float, float, float, float,
				 float, float>())
		 ];
	}
};

#endif

