/*
 *  Node.cpp
 *  sfml
 *
 *  Created by Adam Tomeček on 7/19/12.
 *  Copyright 2012 Brain Dead Cookie. All rights reserved.
 *
 */

#include "Node.h"
#include "Sprite.h"

Node::Node(){
}

Node::Node(float xPos, float yPos, float angle){
	this->xPos = xPos;
	this->yPos = yPos;
	this->angle = angle;
}

void Node::Render(void){
	this->RenderChilds();
}

void Node::RenderChilds(void){
	std::list<Node *>::iterator i;
	
	Node *node;
	Sprite *sprite;

	for(i = this->childs.begin(); i != this->childs.end(); ++i){
		node = *i;
		node->Render();
			//std::tr1::function<void (void)> callback;
		
			//callback = std::tr1::bind(&Node::Render, node);
		
			//this->CallChild(node, cRENDER);
	}
}

/*void Node::CallChild(Node *node, int type){
		if (Sprite *s = dynamic_cast<Sprite *>(node)){
			switch(type){
				case cRENDER:
					s->Render();
					break;
			}
		}

}*/


void Node::AddChild(Node *child){
	this->childs.push_front(child);
}


/*
 * ********************************************************
 * Getters
 * ********************************************************
 */

float Node::GetXPos(void){
	return this->xPos;
}

float Node::GetYPos(void){
	return this->yPos;
}

float Node::GetAngle(void){
	return this->angle;
}

Position Node::GetPosition(void){
	Position p = {this->xPos, this->yPos};
	return p;
}

/*
 * ********************************************************
 * Setters 
 * ********************************************************
 */

void Node::SetPosition(float xPos, float yPos){
	this->xPos = xPos;
	this->yPos = yPos;
}

void Node::SetAngle(float angle){
	this->angle = angle;
}

