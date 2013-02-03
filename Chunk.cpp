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

Chunk::Chunk(void){
	this->scale = 1.0f;
}

Chunk::Chunk(float w, float h){
	this->width = w;
	this->height = h;
	this->scale = 1.0f;
}

Chunk::Chunk(float w, float h, float x, float y){
	this->width = w;
	this->height = h;
	this->xPos = x;
	this->yPos = y;
	this->scale = 1.0f;
}

const float Chunk::GetWidth(void){
	return this->width * this->scale;
}

const float Chunk::GetHeight(void){
	return this->height * this->scale;
}

const float Chunk::GetScale(void){
	return this->scale;
}

Position Chunk::GetCenter(void){
	Position p = {this->xPos + this->width / 2,
		this->yPos + this->height / 2};
	
	return p;
}

void Chunk::SetWidth(float w){
	this->width = w;
}

void Chunk::SetHeight(float h){
	this->height = h;
}

void Chunk::SetScale(float scale){
	this->scale = scale;
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
