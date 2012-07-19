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

Object::Object(b2World *world, float width, float height, float xPos, float yPos, float zPos){
	this->xPos = xPos;
	this->yPos = yPos;
	this->zPos = zPos;
	this->world = world;

	this->angle = 0;

	this->width = width;
	this->height = height;


	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(this->xPos / RATIO, (this->yPos / RATIO + this->height / RATIO));
	body = this->world->CreateBody(&bodyDef);

	b2CircleShape circle;
	circle.m_radius = (this->width / RATIO) / 2;

	b2FixtureDef shapeDef;
	shapeDef.shape = &circle;
	shapeDef.density = 1.0f;
	shapeDef.friction = 0.2f;
	shapeDef.restitution = 0.5f;

	body->CreateFixture(&shapeDef);

	this->body = body;
}

int Object::applyPhysics(){
	float timeStep = 1.0f / 60.0f;

	this->world->Step(timeStep, 8, 3);
	b2Vec2 position = this->body->GetPosition();

	this->angle = this->body->GetAngle() * 2 * 3.14f;

	this->xPos = (position.x * RATIO - this->width / 2);
	this->yPos = (position.y * RATIO - this->height / 2);

}

int Object::move(float xMove, float yMove, float zMove){
	this->xPos += xMove;
	this->yPos += yMove;
	this->zPos += zMove;
	
	return 0;	
}

int Object::draw(void){
	this->applyPhysics();

	glLoadIdentity();

	sf::Image img_data;
	img_data.LoadFromFile("icon.jpg");

	GLuint texture_handle;
	glGenTextures(1, &texture_handle);

	glBindTexture(GL_TEXTURE_2D, texture_handle);

	glTexImage2D(
		GL_TEXTURE_2D, 0, GL_RGBA,
		img_data.GetWidth(), img_data.GetHeight(),
		0,
		GL_RGBA, GL_UNSIGNED_BYTE, img_data.GetPixelsPtr()
	);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	/* glRotatef(this->angle, 0.0f, 0.0f, 1.0f); */

	glBegin(GL_QUADS);
	glVertex2f(this->xPos, this->yPos);
	glTexCoord2f(1, 0);
	glVertex2f(this->xPos + this->width, this->yPos);
	glTexCoord2f(1, 1);
	glVertex2f(this->xPos + this->width, this->yPos + this->height);
	glTexCoord2f(0, 1);
	glVertex2f(this->xPos, this->yPos + this->height);
	glTexCoord2f(0, 0);
	glEnd();
	
	glFlush();
}


/*
 * ****************************************************************************
 * Getters
 * ****************************************************************************
 */

float Object::getXPos(void){
	return this->xPos;
}

float Object::getYPos(void){
	return this->yPos;
}

float Object::getZPos(void){
	return this->zPos;
}

