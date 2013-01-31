/*
 *  Object.cpp
 *  sfml
 *
 *  Created by Adam Tomeček on 6/18/12.
 *  Copyright 2012 OwnSoft. All rights reserved.
 *
 */

#include "Object.h"

Object::~Object(void){
#ifdef DEBUG
	std::cout << "Destruct Object" << std::endl;
#endif

	this->world->DestroyBody(this->body);
	this->body = NULL;	

	/* delete this->representation; */
	this->representation = NULL;
}

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

	this->fixedRotation = false;	
	this->body = NULL;
	this->xPos = xPos;
	this->yPos = yPos;
	this->world = world;
	this->angle = angle;
	this->width = width;
	this->height = height;

	this->CreateBody();

	return ;
}

void Object::CreateBody(void){
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set((this->xPos + this->width / 2) / RATIO,
						 (this->yPos + this->height / 2)/ RATIO);
	bodyDef.angle = this->angle * (M_PI / 180);
	
	this->body = this->world->CreateBody(&bodyDef);

	return ;
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

void Object::Destroy(void){
#ifdef DEBUG
	std::cout << "Destroy Object" << std::endl;
#endif

	/* delete this->representation; */
	delete this;
}

void Object::ApplyPhysics(){
	b2Vec2 position = this->body->GetPosition();
	this->angle = this->body->GetAngle() / (M_PI / 180);

	this->xPos = (position.x * RATIO - this->width / 2);
	this->yPos = (position.y * RATIO - this->height / 2);

	return ;
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

void Object::SetFixedRotation(bool fixed){
	this->fixedRotation = fixed;
}


		/*************** Box2D functions *************************/
void Object::ApplyForce(float forceX, float forceY, float pointX, float pointY){
	b2Vec2 force(forceX / RATIO, forceY / RATIO);
	b2Vec2 point(pointX / RATIO, pointY / RATIO);
	this->body->ApplyForce(force, point);

	return ;
}

void Object::ApplyForceToCenter(float forceX, float forceY){
	b2Vec2 force(forceX / RATIO, forceY / RATIO);
	this->body->ApplyForceToCenter(force);

	return ;
}

void Object::ApplyTorque(float32 torque){
	this->body->ApplyTorque(torque);

	return;
}

void Object::ApplyLinearImpulse(float impX, float impY, float pointX,
				float pointY){
	b2Vec2 impulse(impX / RATIO, impY / RATIO);
	b2Vec2 point(pointX / RATIO, pointY / RATIO);

	this->body->ApplyLinearImpulse(impulse, point);

	return ;
}

void Object::ApplyAngularImpulse(float32 impulse){
	this->body->ApplyAngularImpulse(impulse);

	return;
}
