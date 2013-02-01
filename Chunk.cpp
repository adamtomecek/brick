/*
 *  Chunk.cpp
 *  sfml
 *
 *  Created by Adam Tomeček on 7/27/12.
 *  Copyright 2012 Brain Dead Cookie. All rights reserved.
 *
 */

#include "Chunk.h"

Chunk::~Chunk(){
#ifdef DEBUG
	std::cout << "Destruct Chunk" << std::endl;
#endif
}

Chunk::Chunk(void){}

Chunk::Chunk(float w, float h){
	this->width = w;
	this->height = h;
}

Chunk::Chunk(float w, float h, float x, float y){
	this->width = w;
	this->height = h;
	this->xPos = x;
	this->yPos = y;
}

float Chunk::GetWidth(void){
	return this->width;
}

float Chunk::GetHeight(void){
	return this->height;
}

Position Chunk::GetCenter(void){
	Position p = {this->xPos + this->width / 2,
		this->yPos + this->height / 2};
	
	return p;
}

void Chunk::RotateChilds(float angle){
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
