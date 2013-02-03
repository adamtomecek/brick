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
		Chunk(float w, float h, float x, float y);

		/* void Destroy(void); */

		void RotateChilds(float angle);

		virtual const float GetWidth(void);
		virtual const float GetHeight(void);
		virtual const float GetScale(void);
		Position GetCenter(void);

		void SetWidth(float w);
		void SetHeight(float h);
		void SetScale(float scale);

	protected:
		float width;
		float height;
		float scale;
		
		std::list<PointRotation> pointRotations;
};

#endif
