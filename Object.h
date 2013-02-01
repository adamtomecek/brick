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

#include "Includes.h"
#include "Chunk.h"
#include "JsonLoader.h"

class Object : public Chunk{
	public:
		~Object(void);
		explicit Object(b2World *world, float width, float height, float xPos, float yPos, float angle = 0.0f);
		explicit Object(float width, float height, float xPos, float yPos, float angle = 0.0f);
		explicit Object(b2World *world, Chunk *representation);
		explicit Object(Chunk *representation);

		void init(b2World *world, float width, float height, float xPos, float yPos,
				float angle = 0.0f);

		void ApplyPhysics(void);
		void Render(void);
		void Destroy(void);

		/* Getters */
		Size GetSize(void);

		/* Setters */
		void SetSize(float width, float height);
		void SetFixedRotation(bool fixed);

		/*************** Box2D functions *************************/
		void ApplyForce(float forceX, float forceY, float pointX,
				float pointY);
		void ApplyForceToCenter(float forceX, float forceY);
		void ApplyTorque(float32 torque);
		void ApplyLinearImpulse(float impX, float impY, float pointX,
				float pointY);
		void ApplyAngularImpulse(float32 impulse);

		/**************** Shapes creation ************************/
		void CreateBox();
		void CreateCircle();
		void CreateCustomShape(std::string data);

	protected:
		virtual void CreateBody(void);

		b2World *world;
		b2Body *body;
		Chunk *representation;
		bool fixedRotation;
};

#endif

