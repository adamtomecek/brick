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

#include "Includes.h"

class Node : public boost::enable_shared_from_this<Node> {
	public:
		~Node(void);
		Node(float xPos, float yPos, float zPos = 0.0f, float angle = 0.0f);
		Node();

		boost::shared_ptr<Node> shared_ptr(){
			return shared_from_this();
		}

		virtual void Destroy();
		virtual void DeleteChild(boost::shared_ptr<Node> child);

		virtual void Render(void);
		virtual void Move(float xMove, float yMove);
		virtual void Rotate(float angle);
		virtual void RotateChilds(float angle);
		virtual void RotateAroundPoint(float xPos, float yPos, float angle);
		virtual void RotateChildsAroundPoint(float xPos, float yPos, float angle);
		virtual void AddChild(boost::shared_ptr<Node> child);
	
		static boost::shared_ptr<Node> Init(void){
			return boost::shared_ptr<Node> (new Node);
		}

		/* Getters */
		virtual const float GetXPos(void);
		virtual const float GetYPos(void);
		virtual const float GetZPos(void);
		virtual const float GetAngle(void);
		virtual Position GetPosition(void);
		virtual Position GetCenter(void);

		/* Setters */
		virtual void SetXPos(float x);
		virtual void SetYPos(float y);
		virtual void SetZPos(float z);
		virtual void SetAngle(float angle);
		virtual void SetPosition(float xPos, float yPos, float zPos = 0.0f);

	protected:
		virtual void RenderChilds(void);
		virtual void MoveChilds(float xMove, float yMove);
	
		float xPos;
		float yPos;
		float zPos;
		float angle;
		std::list< boost::shared_ptr<Node> > childs;	

};

#endif
