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

	for(i = this->childs.begin(); i != this->childs.end(); ++i){
		node = *i;
		node->Render();
	}
}

void Node::Move(float xMove, float yMove){
	this->MoveChilds(xMove, yMove);

	this->xPos += xMove;
	this->yPos += yMove;
}

void Node::MoveChilds(float xMove, float yMove){
	std::list<Node *>::iterator i;
	
	Node *node;

	for(i = this->childs.begin(); i != this->childs.end(); ++i){
		node = *i;
		node->Move(xMove, yMove);
	}
}

void Node::Rotate(float angle){
	this->RotateChilds(angle);

	this->angle += angle;

	if(this->angle < 0)
		this->angle += 360;
}

void Node::RotateChilds(float angle){
	std::list<Node *>::iterator i;
	
	Node *node;

	for(i = this->childs.begin(); i != this->childs.end(); ++i){
		node = *i;
		node->Rotate(angle);
	}
}

void Node::RotateAroundPoint(float xPos, float yPos, float angle){
	
}

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
	if(angle < 0)
		angle += 360;
	
	this->angle = angle;
}

