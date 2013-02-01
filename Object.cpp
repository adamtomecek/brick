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

	return ;
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

b2Body *Object::GetBody(void){
	return this->body;
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

void Object::CreateBody(){
}

/*************** Shapes cration *************************/
void Object::CreateBox(void){
	b2PolygonShape box;
	box.SetAsBox(this->width / 2 / RATIO, this->height / 2 / RATIO);

	b2FixtureDef shapeDef;
	shapeDef.shape = &box;
	shapeDef.density = 10.0f;
	shapeDef.friction = 0.3f;
	shapeDef.restitution = 0.0f;

	this->body->CreateFixture(&shapeDef);
}

void Object::CreateCircle(void){
	b2CircleShape circle;

	circle.m_radius = this->width / 2 / RATIO;
	
	b2FixtureDef shapeDef;
	shapeDef.shape = &circle;
	
	shapeDef.density = 1.0f;
	shapeDef.friction = 0.8f;
	shapeDef.restitution = 0.2f;
	
	this->body->CreateFixture(&shapeDef);
}

void Object::CreateCustomShape(std::string data){
	JsonLoader *json = new JsonLoader(data);	
	std::list<Point> *points = json->GetPoints();
	int size = points->size();
	b2Vec2 verticles[size];

	std::list<Point>::iterator i;
	Point p;	

	int j = 0;	
	for(i = points->begin(); i != points->end(); ++i){
		p = *i;
		verticles[j].Set(p.x, p.y);
		j++;
	}

	b2PolygonShape polygonShape;
	polygonShape.Set(verticles, size);
	
	b2FixtureDef shapeDef;
	shapeDef.shape = &polygonShape;
	shapeDef.density = 0.8f;
	shapeDef.friction = 0.3f;
	shapeDef.restitution = 0.2f;

	this->body->CreateFixture(&shapeDef);
	delete json;

	return ;
}

