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

		virtual void DefineBody(void);

		/* Getters */
		Size GetSize(void);

		/* Setters */
		void SetSize(float width, float height);

		/* Lua binding */
		static void Lua(lua_State *lua){
		luabind::module(lua)
		[
		 luabind::class_<Object, Chunk, boost::shared_ptr<Node> >("Object")
		 .def(luabind::constructor<Chunk*>(), luabind::adopt(luabind::result))
		 /* .def(luabind::constructor<b2World *, boost::shared_ptr<Chunk> >()) */
		 /* .def(luabind::constructor<b2World *, float, float, float, float, float>()) */
		 /* .def(luabind::constructor<float, float, float, float, float>()) */
		 ];
		}

	protected:
		b2World *world;
		b2Body *body;
		Chunk *representation;
};

#endif
