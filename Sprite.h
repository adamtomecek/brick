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
		Sprite(float width, float height, float xPos, float yPos, float zPos = 0.0f,
			   float angle = 0.0f);
		Sprite(std::string texture, float xPos, float yPos, float zPos = 0.0f, 
				float angle = 0.0f);
		/* Sprite(std::string texture, float width, float height, float xPos, */
		/* 		float yPos, float zPos = 0.0f, float angle = 0.0f); */

		void init(std::string texture, float width, float height, float xPos,
					float yPos, float zPos = 0.0f, float angle = 0.0f);

		void Render();

		/* Getters */
		sf::Image* GetTexture(void);
		Size GetSize(void);

	private:
		bool LoadTexture(std::string texture);
		GLuint texture_handle;
		void LoadGLTexture(void);

		std::string textureName;
		sf::Image *textureData;
};

#endif

