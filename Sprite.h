/*
 *  Sprite.h
 *  sfml
 *
 *  Created by Adam Tomeček on 7/15/12.
 *  Copyright 2012 Brain Dead Cookie. All rights reserved.
 *
 */

#ifndef SPRITE_H
#define SPRITE_H

#include "Game.h"
#include "Node.h"

class Sprite : public Node{
	public:
		Sprite(float width, float height, float xPos, float yPos,
			   float angle = 0.0f);
		Sprite(std::string texture, float xPos, float yPos, float angle = 0.0f);
		Sprite(std::string texture, float width, float height, float xPos,
				float yPos, float angle = 0.0f);

		void init(std::string texture, float width, float height, float xPos,
					float yPos, float angle = 0.0f);

		void Render(void);
		int Move(float xMove, float yMove);
		int Rotate(float angle);

		/* Getters */
		float GetWidth(void);
		float GetHeight(void);
		sf::Image* GetTexture(void);
		Size GetSize(void);

		/* Setters */
		void SetSize(float width, float height);
		
		/* Lua binding */
		static void Lua(lua_State *lua){
			luabind::module(lua)
			[
			 luabind::class_<Sprite>("Sprite")
			 .def(luabind::constructor<float, float, float, float, float>())
			 .def(luabind::constructor<std::string, float, float, float>())
			 .def(luabind::constructor<std::string, float, float, float, float, float>())
			 .def("Render", &Sprite::Render)
			 ];
		}

	private:
		bool LoadTexture(std::string texture);

		
		float width;
		float height;
		std::string textureName;
		sf::Image *textureData;
};

#endif