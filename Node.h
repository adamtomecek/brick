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

class Node{
	public:
		Node(float xPos, float yPos, float angle = 0.0f);
		Node();

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
		virtual float GetYPos(void);
		virtual float GetXPos(void);
		virtual float GetAngle(void);
		virtual Position GetPosition(void);
		virtual Position GetCenter(void);

		/* Setters */
		virtual void SetPosition(float xPos, float yPos);
		virtual void SetAngle(float angle);
	
		virtual ~Node() {}

		/* Lua binding */
		static void Lua(lua_State *lua){
			luabind::module(lua)
			[
			 luabind::class_<Node, boost::shared_ptr<Node> >("Node")
			 .def(luabind::constructor<>())
			 .def(luabind::constructor<float, float, float>())

			 .def("Render", &Node::Render)
			 .def("Move", &Node::Move)
			 .def("Rotate", &Node::Rotate)
			 .def("AddChild", &Node::AddChild, luabind::adopt(luabind::result))
			 .def("RotateAroundPoint", &Node::RotateAroundPoint)
			 .def("Init", &Node::Init)
			 ];
		}

	protected:
		virtual void RenderChilds(void);
		virtual void MoveChilds(float xMove, float yMove);
	
		float xPos;
		float yPos;
		float angle;
		std::list< boost::shared_ptr<Node> > childs;	

		

};

#endif
