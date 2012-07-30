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
		virtual void RotateAroundPoint(float xPos, float yPos, float angle);
		void Rotate(float angle);

		float GetWidth(void);
		float GetHeight(void);
		Position GetCenter(void);
	
	protected:
		float width;
		float height;
		
		std::list<PointRotation> pointRotations;
};

#endif
