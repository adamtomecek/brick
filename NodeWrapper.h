/*
 *  NodeWrapper.h
 *  sfml
 *
 *  Created by Adam Tomeček on 12/2/12.
 *  Copyright 2012 Brain Dead Cookie. All rights reserved.
 *
 */

#ifndef NODE_WRAPPER_H
#define NODE_WRAPPER_H

#include "Includes.h"
#include "Node.h"

struct NodeWrapper : Node, luabind::wrap_base{
	NodeWrapper() : Node() {}

	NodeWrapper(float xPos, float yPos, float zPos = 0.0f,
			float angle = 0.0f)

		: Node(xPos, yPos, zPos, angle) {}
	
	virtual void Destroy(void){
		call<void>("Destroy");
	}

	static void default_Destroy(Node *ptr){
		return ptr->Node::Destroy();
	}

	virtual void DeleteChild(boost::shared_ptr<Node> child){
		call<void>("DeleteChild", child);
	}

	static void default_DeleteChild(Node *ptr, boost::shared_ptr<Node> child){
		return ptr->Node::DeleteChild(child);
	}

    virtual void Render(void){
         call<void>("Render");
    }

	static void default_Render(Node* ptr){
		return ptr->Node::Render();
	}

	virtual void Move(float xMove, float yMove){
		call<void>("Move", xMove, yMove);
	}

	static void default_Move(Node *ptr, float xMove, float yMove){
		return ptr->Node::Move(xMove, yMove);
	}

	virtual void Rotate(float angle){
		call<void>("Rotate", angle);
	}

	static void default_Rotate(Node *ptr, float angle){
		return ptr->Node::Rotate(angle);
	}

	virtual void AddChild(boost::shared_ptr<Node> child){
		call<void>("AddChild", child);
	}

	static void default_AddChild(Node *ptr, boost::shared_ptr<Node> child){
		return ptr->Node::AddChild(child);
	}

	virtual void RotateAroundPoint(float xPos, float yPos, float angle){
		call<void>("RotateAroundPoint", xPos, yPos, angle);
	}

	static void default_RotateAroundPoint(Node *ptr, float xPos, float yPos,
			float angle){
		return ptr->Node::RotateAroundPoint(xPos, yPos, angle);
	}


	static void Lua(lua_State *lua){
		luabind::module(lua)
		[
		luabind::class_<Node, NodeWrapper, boost::shared_ptr<Node> >("Node")
			.def(luabind::constructor<>())
			.def(luabind::constructor<float, float, float, float>())
			.def("Destroy", &Node::Destroy, &NodeWrapper::default_Destroy)
			.def("DeleteChild", &Node::DeleteChild, &NodeWrapper::default_DeleteChild)
			.def("Render", &Node::Render, &NodeWrapper::default_Render)
			.def("Move", &Node::Move, &NodeWrapper::default_Move)
			.def("Rotate", &Node::Rotate, &NodeWrapper::default_Move)
			.def("AddChild", &Node::AddChild, &NodeWrapper::default_AddChild)
			.def("RotateAroundPoint", &Node::RotateAroundPoint,
					&NodeWrapper::default_RotateAroundPoint)
		];
	}
};

#endif

