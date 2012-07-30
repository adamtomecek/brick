/*
 *  Chunk.cpp
 *  sfml
 *
 *  Created by Adam Tomeček on 7/27/12.
 *  Copyright 2012 Brain Dead Cookie. All rights reserved.
 *
 */

#include "Chunk.h"

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

void Chunk::Rotate(float angle){
	this->RotateChilds(angle);

	std::list<Node *>::iterator i;
	
	Node *node;

	for(i = this->childs.begin(); i != this->childs.end(); ++i){
		node = *i;
		Position center = this->GetCenter();
		node->RotateAroundPoint(center.x, center.y, angle);
	}
	
	this->angle += angle;
}

void Chunk::RotateAroundPoint(float xPos, float yPos, float angle){
	float centerXPos = this->xPos + this->width / 2;
	float centerYPos = this->yPos + this->height / 2;

	/*
	float pointDistance = pow(centerXPos - xPos, 2.0f) + pow(centerYPos - yPos, 2.0f);
	pointDistance = sqrt(pointDistance);
	float pointDistanceX = centerXPos - xPos;

	float pointDistanceY = centerYPos - yPos;
	float baseAngle = atan(pointDistanceX / pointDistanceY) / (M_PI / 180);
	
	
	if(baseAngle < 0)
		baseAngle += 360;

	float targetAngle = baseAngle + angle;
 /*
	float finX = pointDistanceX * sin(targetAngle * (M_PI / 180));
	float finY = pointDistanceY * cos(targetAngle * (M_PI / 180));
*/

	/*

	float finPointDistance = 2 * pow(pointDistance, 2.0f) - (2 * pow(pointDistance, 2.0f) * cos(angle * M_PI / 180));
	finPointDistance = sqrt(finPointDistance);
	
	
	
	float xMove = finX - xPos;
	float yMove = finY - yPos;
	 */
	

	float s = sin(angle * (M_PI / 180));
	float c = cos(angle * (M_PI / 180));
	
	centerXPos -= xPos;
	centerYPos -= yPos;
	
	float finX = centerXPos * c - centerYPos * s;
	float finY = centerXPos * s + centerYPos * c;
	
	Position center = this->GetCenter();
	
	finX += xPos;
	finY += yPos;
	
	float xMove = finX - center.x;
	float yMove = finY - center.y;

	this->Move(xMove, yMove);
}
