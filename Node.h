/*
 *  Node.h
 *  sfml
 *
 *  Created by Adam Tomeček on 7/19/12
 *  Copyright 2012 Brain Dead Cookie. All rights reserved.
 *
 */

#include "Game.h"

class Node{
	public:
		Node(float xPos, float yPos, float angle = 0.0f);

		void Render(void);
		void Move(float xMove, float yMove);
		void Rotate(float angle);

		/* Getters */
		float GetYPos(void);
		float GetXPos(void);
		Position GetPosition(void);

		/* Setters */
		void SetPosition(float xPos, float yPos);

};

