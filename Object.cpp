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

Object::Object(b2World *world, Sprite *sprite){
	this->init(world, sprite->GetWidth(), sprite->GetHeight(),
		sprite->GetXPos(), sprite->GetYPos(), sprite->GetAngle());
	
	this->sprite = sprite;	
}

Object::Object(b2World *world, float width, float height, float xPos, float yPos,
		float angle){
	this->init(world, width, height, xPos, yPos, angle);
	
	this->sprite = NULL;
}


void Object::init(b2World *world, float width, float height, float xPos, float yPos,
		float angle){
	
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
	
	if(this->sprite != NULL){
		this->sprite->SetPosition(this->xPos, this->yPos);
		this->sprite->SetAngle(this->angle);
		this->sprite->Render();
	}
}

void Object::ApplyPhysics(){
	float timeStep = 1.0f / 60.0f;

	b2Vec2 position = this->body->GetPosition();

	this->angle = this->body->GetAngle() * 2 * M_PI;

	this->xPos = (position.x * RATIO - this->width / 2);
	this->yPos = (position.y * RATIO - this->height / 2);

}

/*
 * ********************************************************
 * Getters
 * ********************************************************
 */

float Object::GetWidth(void){
	return this->width;
}

float Object::GetHeight(void){
	return this->height;
}

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

