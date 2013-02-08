/*
 *  Sprite.cpp
 *  sfml
 *
 *  Created by Adam Tomeček on 7/15/12.
 *  Copyright 2012 Brain Dead Cookie. All rights reserved.
 *
 */

#include "Sprite.h"

/*
 * ********************************************************
 * Constructors 
 * ********************************************************
 */
void Sprite::init(std::string texture, float width, float height, float xPos,
			   float yPos, float zPos, float angle){
	this->xPos = xPos;
	this->yPos = yPos;
	this->zPos = zPos;
	this->angle = angle;
	
	this->width = width;
	this->height = height;
	
	this->LoadTexture(texture);
}

Sprite::Sprite(float width, float height, float xPos, float yPos, float zPos, 
		float angle){
	this->textureData = NULL;
	this->init("", width, height, xPos, yPos, zPos, angle);
}

Sprite::Sprite(std::string texture, float width, float height, float xPos,
		float yPos, float zPos, float angle){
	this->textureData = NULL;
	
	this->init(texture, width, height, xPos, yPos, zPos, angle);
}

Sprite::Sprite(std::string texture, float xPos,	float yPos, float zPos, float angle){
	this->textureData = NULL;
	this->LoadTexture(texture);
	
	this->init(texture, this->textureData->GetWidth(),this->textureData->GetHeight(),
			xPos, yPos, zPos, angle);
}

/*
 * ********************************************************
 * Logic 
 * ********************************************************
 */

/*
 * Loads texture image
 */
bool Sprite::LoadTexture(std::string fileName){
	/* no texture name was provided */
	if (fileName == "") {
		return false;
	}
	
	/* texture was not loaded before */
		if(this->textureData == NULL){
			this->textureData = new sf::Image;
			
			if (!this->textureData->LoadFromFile(fileName.c_str())){
				std::cout << "Error while loading image '"<< fileName << "." << std::endl;
				return false;
			}
		
			this->textureName = fileName;
		}

	this->LoadGLTexture();
	return true;
}

void Sprite::LoadGLTexture(void){
	if(!DEBUG_DRAW){

	glGenTextures(1, &this->texture_handle);
	
	glBindTexture(GL_TEXTURE_RECTANGLE_EXT, this->texture_handle);
	
	glTexParameteri(GL_TEXTURE_RECTANGLE_EXT, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_RECTANGLE_EXT, GL_TEXTURE_MIN_FILTER, GL_NEAREST);


glTexParameteri(GL_TEXTURE_RECTANGLE_EXT, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_RECTANGLE_EXT, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	/* Loads 2D texture from image */
	glTexImage2D(
		 GL_TEXTURE_RECTANGLE_EXT, 0, GL_RGBA,
		 this->textureData->GetWidth(), this->textureData->GetHeight(),
		 0,
		 GL_RGBA, GL_UNSIGNED_BYTE, this->GetTexture()->GetPixelsPtr()
	 );
	
	/* Transparency */
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	}
}

/*
 * Renders sprite
 */
void Sprite::Render(void){
	this->RenderChilds();
	glPushMatrix();
	glLoadIdentity();
	glPushAttrib(GL_CURRENT_BIT);
	Position center = this->GetCenter();

	/* move to proper location */	
	glTranslatef(center.x, center.y, 0.0f);
	glRotatef(this->angle, 0.0f, 0.0f, 1.0f);
	glTranslatef(-this->width / 2, -this->height / 2 , 0.0f);
	
	if(this->textureData != NULL){
		glBindTexture(GL_TEXTURE_RECTANGLE_EXT, this->texture_handle);
	}else {
		glColor4f(0, 1, 0, 1);
	}

	/* scale */	
	glScalef( this->scale, this->scale, 1.0f);

	float z = this->zPos;	
	/* Creates 3D cube */
	glBegin( GL_QUADS );
	glTexCoord3f( 0, this->height, z);                           
	glVertex3f( 0, 0, z);
	glTexCoord3f(this->width, this->height, z);
	glVertex3f(this->width, 0 , z);
	glTexCoord3f(this->width, 0 , z);
	glVertex3f(this->width, this->height, z);
	glTexCoord3f( 0, 0 , z);
	glVertex3f( 0, this->height, z);
	glEnd();

	glPopAttrib();	
	glPopMatrix();	

	/* GLfloat vertices[] = {1, 1, 1, */
	/* 					-1, 1, 1, */
	/* 					-1, -1, 1, */
	/* 					1, -1, 1 */
	/* 					 }; */

	/* GLfloat normals[] = { */
	/* 	 0, 0, 1,   0, 0, 1,   0, 0, 1,   0, 0, 1 */
	/* }; */

	/* GLfloat colors[] = { 1, 1, 1,   1, 1, 0,   1, 0, 0,   1, 0, 1}; */

	/* GLubyte indices[] = {0,1,2, // first triangle (bottom left - top left - top right) */
	/* 					 2,3,0}; // second triangle (bottom left - top right - bottom right) */

	/* glEnableClientState(GL_NORMAL_ARRAY); */
    /* glEnableClientState(GL_COLOR_ARRAY); */
    /* glEnableClientState(GL_VERTEX_ARRAY); */
    /* glNormalPointer(GL_FLOAT, 0, normals); */
    /* glColorPointer(3, GL_FLOAT, 0, colors); */
    /* glVertexPointer(3, GL_FLOAT, 0, vertices); */

    /* glPushMatrix(); */
    /* glTranslatef(-2, -2, 0);                // move to bottom-left corner */

    /* glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, indices); */

    /* glPopMatrix(); */

    /* glDisableClientState(GL_VERTEX_ARRAY);  // disable vertex arrays */
    /* glDisableClientState(GL_COLOR_ARRAY); */
    /* glDisableClientState(GL_NORMAL_ARRAY); */
}

/*
 * ********************************************************
 * Getters
 * ********************************************************
 */

sf::Image* Sprite::GetTexture(void){
	return this->textureData;
}

Size Sprite::GetSize(void){
	Size s = {this->width, this->height};
	return s;
}

