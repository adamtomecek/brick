/*
 *  Sprite.h
 *  sfml
 *
 *  Created by Adam Tomeček on 7/15/12.
 *  Copyright 2012 Brain Dead Cookie. All rights reserved.
 *
 */

#include "Game.h"

class Sprite{
	public:
		Sprite(float width, float height, float xPos, float yPos,
			   float angle = 0.0f);
		Sprite(std::string texture, float xPos, float yPos, float angle = 0.0f);
		Sprite(std::string texture, float width, float height, float xPos,
				float yPos, float angle = 0.0f);

		void init(std::string texture, float width, float height, float xPos,
					float yPos, float angle = 0.0f);

		bool Render(void);
		int Move(float xMove, float yMove);
		int Rotate(float angle);

		/* Getters */
		float GetWidth(void);
		float GetHeight(void);
		float GetXPos(void);
		float GetYPos(void);
		float GetAngle(void);
		sf::Image* GetTexture(void);
		Position GetPosition(void);
		Size GetSize(void);

		/* Setters */
		void SetPosition(float xPos, float yPos);
		void SetSize(float width, float height);

	private:
		bool LoadTexture(std::string texture);

		float xPos;
		float yPos;
		float angle;
		float width;
		float height;
		std::string textureName;
		sf::Image *textureData;
};

