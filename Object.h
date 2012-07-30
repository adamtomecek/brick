/*
 *  Object.h
 *  sfml
 *
 *  Created by Adam Tomeček on 6/18/12.
 *  Copyright 2012 Brain Dead Cookie. All rights reserved.
 *
 */

#ifndef OBJECT_H
#define OBJECT_H

#include "Game.h"
#include "Chunk.h"

class Object : public Chunk{
	public:
		explicit Object(b2World *world, float width, float height, float xPos, float yPos, float angle = 0.0f);
		explicit Object(b2World *world, Chunk *representation);

		void init(b2World *world, float width, float height, float xPos, float yPos,
				float angle = 0.0f);

		void ApplyPhysics(void);
		void Render(void);

		virtual void DefineBody(void);

		/* Getters */
		Size GetSize(void);

		/* Setters */
		void SetSize(float width, float height);

	protected:
		b2World *world;
		b2Body *body;
		Chunk *representation;
};

#endif
