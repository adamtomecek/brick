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

#include "Includes.h"
#include "Chunk.h"

class Sprite : public Chunk{
	public:
		Sprite(float width, float height, float xPos, float yPos,
			   float angle = 0.0f);
		Sprite(std::string texture, float xPos, float yPos, float angle = 0.0f);
		Sprite(std::string texture, float width, float height, float xPos,
				float yPos, float angle = 0.0f);

		void init(std::string texture, float width, float height, float xPos,
					float yPos, float angle = 0.0f);

		void Render();

		/* Getters */
		sf::Image* GetTexture(void);
		Size GetSize(void);

		/* Setters */
		void SetSize(float width, float height);

		static boost::shared_ptr<Sprite> Init(std::string texture,
				float xPos, float yPos, float angle){
				return boost::shared_ptr<Sprite> (new Sprite(texture, xPos, yPos, angle));
		}
		
		/* Lua binding */
		static void Lua(lua_State *lua){
			luabind::module(lua)
			[
			 luabind::class_<Sprite, Chunk, boost::shared_ptr<Node> >("Sprite")
			 .def(luabind::constructor<float, float, float, float, float>())
			 .def(luabind::constructor<std::string, float, float, float>())
			 .def(luabind::constructor<std::string, float, float, float, float, float>())
			 .scope[
				 luabind::def("Init", &Sprite::Init)
			 ]
			 ];
		}

	private:
		bool LoadTexture(std::string texture);
		GLuint texture_handle;
		void LoadGLTexture(void);

		std::string textureName;
		sf::Image *textureData;
};

#endif

