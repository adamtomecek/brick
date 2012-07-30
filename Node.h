/*
 *  Node.h
 *  sfml
 *
 *  Created by Adam Tomeček on 7/19/12
 *  Copyright 2012 Brain Dead Cookie. All rights reserved.
 *
 */

#ifndef NODE_H
#define NODE_H

#include "Game.h"

class Node{
	public:
		Node(float xPos, float yPos, float angle = 0.0f);
		Node();

		virtual void Render(void);
		virtual void Move(float xMove, float yMove);
		virtual void Rotate(float angle);
		virtual void RotateAroundPoint(float xPos, float yPos, float angle);
		virtual void AddChild(Node *child);

		/* Getters */
		float GetYPos(void);
		float GetXPos(void);
		float GetAngle(void);
		Position GetPosition(void);

		/* Setters */
		virtual void SetPosition(float xPos, float yPos);
		virtual void SetAngle(float angle);
	
		virtual ~Node() {}

	protected:
		virtual void RenderChilds(void);
		virtual void MoveChilds(float xMove, float yMove);
		virtual void RotateChilds(float angle);
	
		float xPos;
		float yPos;
		float angle;
		std::list<Node *> childs;	

		

};

#endif
