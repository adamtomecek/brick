/*
 *  ChunkWrapper.h
 *  sfml
 *
 *  Created by Adam Tomeček on 12/2/12.
 *  Copyright 2012 Brain Dead Cookie. All rights reserved.
 *
 */

#ifndef CHUNK_WRAPPER_H
#define CHUNK_WRAPPER_H

#include "Includes.h"
#include "Chunk.h"

struct ChunkWrapper : Chunk, luabind::wrap_base{

	ChunkWrapper() : Chunk () {}

	ChunkWrapper(float w, float h) : Chunk (w, h) {}
	ChunkWrapper(float w, float h, float x, float y) : Chunk (w, h, x, y) {}

	static void Lua(lua_State *lua){
		luabind::module(lua)
		[
		luabind::class_<Chunk, ChunkWrapper, Node, boost::shared_ptr<Node> >("Chunk")
			.def(luabind::constructor<>())
			.def(luabind::constructor<float, float>())
			.def(luabind::constructor<float, float, float, float>())
		];
	}
	
};

#endif
