/*
 *  Object.cpp
 *  sfml
 *
 *  Created by Adam Tomeček on 6/18/12.
 *  Copyright 2012 OwnSoft. All rights reserved.
 *
 */

#include "Game.h"
#include "Object.h"


Object::Object(Chunk *representation){
	this->init(Utils::GetWorld(), representation->GetWidth(), representation->GetHeight(),
		representation->GetXPos(), representation->GetYPos(),
		representation->GetAngle());
	
	this->representation = representation;	
}

Object::Object(b2World *world, Chunk *representation){
	this->init(world, representation->GetWidth(), representation->GetHeight(),
			   representation->GetXPos(), representation->GetYPos(),
			   representation->GetAngle());
	
	this->representation = representation;	
}

Object::Object(float width, float height, float xPos, float yPos,
		float angle){
	this->init(Utils::GetWorld(), width, height, xPos, yPos, angle);
	
		//this->representation = NULL;
}

Object::Object(b2World *world, float width, float height, float xPos, float yPos,
		float angle){
	this->init(world, width, height, xPos, yPos, angle);
	
		//this->representation = NULL;
}


void Object::init(b2World *world, float width, float height, float xPos,
		float yPos, float angle){
	
	this->body = NULL;
	this->xPos = xPos;
	this->yPos = yPos;
	this->world = world;
	this->angle = angle;
	this->width = width;
	this->height = height;
}

void Object::DefineBody(void){
	
}

void Object::Render(void){
	this->RenderChilds();
	this->ApplyPhysics();
	
	if(this->representation != NULL){
		this->representation->SetPosition(this->xPos,this->yPos);
		this->representation->SetAngle(this->angle);
		this->representation->Render();
	}
}

void Object::ApplyPhysics(){
	b2Vec2 position = this->body->GetPosition();
	float angel = this->body->GetAngle() / (M_PI / 180);
	this->angle = this->body->GetAngle() / (M_PI / 180);

	this->xPos = (position.x * RATIO - this->width / 2);
	this->yPos = (position.y * RATIO - this->height / 2);

}

/*
 * ********************************************************
 * Getters
 * ********************************************************
 */

Size Object::GetSize(void){
	Size s = {this->width, this->height};
	return s;
}

/*
 * ********************************************************
 * Setters 
 * ********************************************************
 */

void Object::SetSize(float width, float height){
	this->width = width;
	this->height = height;
}

