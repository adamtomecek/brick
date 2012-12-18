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

#include "Includes.h"
#include "Node.h"

class Chunk : public Node{
	public:
		~Chunk();
		Chunk(void);
		Chunk(float w, float h);

		/* void Destroy(void); */

		void RotateChilds(float angle);

		float GetWidth(void);
		float GetHeight(void);
		Position GetCenter(void);

	protected:
		float width;
		float height;
		
		std::list<PointRotation> pointRotations;
};

#endif
