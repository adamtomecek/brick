/*
 *  Object.h
 *  sfml
 *
 *  Created by Adam Tomeček on 6/18/12.
 *  Copyright 2012 Brain Dead Cookie. All rights reserved.
 *
 */


#include "Game.h"
#include "Node.h"
#include "Sprite.h"

class Object : public Node{
	public:
		Object(b2World *world, float width, float height, float xPos, float yPos, float zPos);
		Object(b2World *world, Sprite *sprite);

		void init(b2World *world, float width, float height, float xPos, float yPos,
				float angle = 0.0f);

		void ApplyPhysics(void);
		void Render(void);

		/* Getters */
		float GetWidth(void);
		float GetHeight(void);
		Size GetSize(void);

		/* Setters */
		void SetSize(float width, float height);

	private:
		float width;
		float height;

		b2World *world;
		b2Body *body;
		Sprite *sprite;
};
