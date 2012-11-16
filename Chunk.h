/*
 *  Chunk.h
 *  sfml
 *
 *  Created by Adam Tomeček on 7/27/12.
 *  Copyright 2012 Brain Dead Cookie. All rights reserved.
 *
 */

#ifndef CHUNK_H
#define CHUNK_H

#include "Game.h"
#include "Node.h"

class Chunk : public Node{
	public:
		void RotateChilds(float angle);

		float GetWidth(void);
		float GetHeight(void);
		Position GetCenter(void);

		/* Lua binding */
		static void Lua(lua_State *lua){
			luabind::module(lua)
			[
			 luabind::class_<Chunk, Node, boost::shared_ptr<Node> >("Chunk")
			 .def(luabind::constructor<>())
			 ];
		}
	
	protected:
		float width;
		float height;
		
		std::list<PointRotation> pointRotations;
};

#endif
