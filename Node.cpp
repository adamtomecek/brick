/*
 *  Node.cpp
 *  sfml
 *
 *  Created by Adam Tomeček on 7/19/12.
 *  Copyright 2012 Brain Dead Cookie. All rights reserved.
 *
 */

#include "Node.h"

Node::~Node(void){

#ifdef DEBUG
	std::cout << "Destruct Node" << std::endl;
#endif

	std::list< boost::shared_ptr<Node> >::iterator i;
	
	boost::shared_ptr<Node> ptr;
	Node *node;

	for(i = this->childs.begin(); i != this->childs.end(); ++i){
		ptr = *i;
		node = ptr.get();
		ptr.reset();
	}
}

Node::Node(){

}

Node::Node(float xPos, float yPos, float zPos, float angle){
	this->xPos = xPos;
	this->yPos = yPos;
	this->zPos = zPos;
	this->angle = angle;
}

void Node::DeleteChild(boost::shared_ptr<Node> child){
	this->childs.remove(child);
	child->Destroy();
}

void Node::Destroy(){

#ifdef DEBUG
	std::cout << "Destroy Node" << std::endl;
#endif

	delete this;
}

void Node::Render(void){
	this->RenderChilds();
}

void Node::RenderChilds(void){
	std::list< boost::shared_ptr<Node> >::iterator i;
	
	boost::shared_ptr<Node> ptr;
	Node *node;

	for(i = this->childs.begin(); i != this->childs.end(); ++i){
		ptr = *i;
		node = ptr.get();
		node->Render();
	}
}

void Node::Move(float xMove, float yMove){
	this->MoveChilds(xMove, yMove);

	this->xPos += xMove;
	this->yPos += yMove;
}

void Node::MoveChilds(float xMove, float yMove){
	std::list< boost::shared_ptr<Node> >::iterator i;
	
	boost::shared_ptr<Node> ptr;
	Node *node;

	for(i = this->childs.begin(); i != this->childs.end(); ++i){
		ptr = *i;
		node = ptr.get();
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
	std::list< boost::shared_ptr<Node> >::iterator i;
	
	boost::shared_ptr<Node> ptr;
	Node *node;
	Position center = this->GetCenter();
	
	for(i = this->childs.begin(); i != this->childs.end(); ++i){
		ptr = *i;
		node = ptr.get();
		node->RotateAroundPoint(center.x, center.y, angle);
	}
}

void Node::RotateChildsAroundPoint(float xPos, float yPos, float angle){
	std::list< boost::shared_ptr<Node> >::iterator i;
	
	boost::shared_ptr<Node> ptr;
	Node *node;
	
	for(i = this->childs.begin(); i != this->childs.end(); ++i){
		ptr = *i;
		node = ptr.get();
		node->RotateAroundPoint(xPos, yPos, angle);
	}
}

void Node::RotateAroundPoint(float xPos, float yPos, float angle){
		//this->RotateChildsAroundPoint(xPos, yPos, angle);
	
	Position center = this->GetCenter();
	float centerXPos = center.x;
	float centerYPos = center.y;
	
	float s = sin(angle * (M_PI / 180));
	float c = cos(angle * (M_PI / 180));
	
	centerXPos -= xPos;
	centerYPos -= yPos;
	
	float finX = centerXPos * c - centerYPos * s;
	float finY = centerXPos * s + centerYPos * c;
	
	finX += xPos;
	finY += yPos;
	
	float xMove = finX - center.x;
	float yMove = finY - center.y;
	
	this->Move(xMove, yMove);
	this->angle += angle;
}

void Node::AddChild(boost::shared_ptr<Node> child){
	this->childs.push_back(child);
}


/*
 * ********************************************************
 * Getters
 * ********************************************************
 */

const float Node::GetXPos(void){
	return this->xPos;
}

const float Node::GetYPos(void){
	return this->yPos;
}

const float Node::GetZPos(void){
	return this->zPos;
}

const float Node::GetAngle(void){
	return this->angle;
}

Position Node::GetPosition(void){
	Position p = {this->xPos, this->yPos, this->zPos};
	return p;
}

Position Node::GetCenter(void){
	Position p = {this->xPos, this->yPos};
	
	return p;
}

/*
 * ********************************************************
 * Setters 
 * ********************************************************
 */

void Node::SetXPos(float x){
	this->xPos = x;
}

void Node::SetYPos(float y){
	this->yPos = y;
}

void Node::SetZPos(float z){
	this->zPos = z;
}

void Node::SetAngle(float angle){
	if(angle < 0)
		angle += 360;
	
	this->angle = angle;
}

void Node::SetPosition(float xPos, float yPos, float zPos){
	this->xPos = xPos;
	this->yPos = yPos;
	this->zPos = zPos;
}


