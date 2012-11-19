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
			   float yPos, float angle){
	this->xPos = xPos;
	this->yPos = yPos;
	this->angle = angle;
	
	this->width = width;
	this->height = height;
	
	this->LoadTexture(texture);
}

Sprite::Sprite(float width, float height, float xPos, float yPos, float angle){
	this->textureData = NULL;
	this->init("", width, height, xPos, yPos, angle);
}

Sprite::Sprite(std::string texture, float width, float height, float xPos,
		float yPos, float angle){
	this->textureData = NULL;
	
	this->init(texture, width, height, xPos, yPos, angle);
}

Sprite::Sprite(std::string texture, float xPos,	float yPos, float angle){
	this->textureData = NULL;
	this->LoadTexture(texture);
	
	this->init(texture, this->textureData->GetWidth(), this->textureData->GetHeight(),
			xPos, yPos, angle);
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
	glGenTextures(1, &this->texture_handle);
	
	glBindTexture(GL_TEXTURE_RECTANGLE_EXT, this->texture_handle);
	
	glTexParameteri(GL_TEXTURE_RECTANGLE_EXT, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_RECTANGLE_EXT, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	
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

/*
 * Renders sprite
 */
void Sprite::Render(void){
	this->RenderChilds();
	glLoadIdentity();
	glPushMatrix();
	Position center = this->GetCenter();
	
	/* Ensures only local changes until matrix is popped */
	
	glTranslatef(center.x, center.y, 0.0f);
	glRotatef(this->angle, 0.0f, 0.0f, 1.0f);
	glTranslatef(-this->width / 2, -this->height / 2 , 0);
	
	if(this->textureData != NULL){	
		glBindTexture(GL_TEXTURE_RECTANGLE_EXT, this->texture_handle);
	}else {
		glPushAttrib(GL_CURRENT_BIT);
		glColor4f(0, 1, 0, 1);
	}
	
	/* Creates 3D cube */
	
	glBegin( GL_QUADS );
	glTexCoord2i( 0, this->GetHeight() );                           
	glVertex2i( 0, 0 );
	glTexCoord2i(this->GetWidth(), this->GetHeight());     
	glVertex2i(this->GetWidth(), 0 );
	glTexCoord2i(this->GetWidth(), 0 );    
	glVertex2i(this->GetWidth(), this->GetHeight());
	glTexCoord2i( 0, 0 );          
	glVertex2i( 0, this->GetHeight());
	glEnd();
	
	/*
	glBegin(GL_QUADS);
	glVertex2i(0, 0);
	glTexCoord2i(1, 0);
	glVertex2i(this->GetWidth(), 0);
	glTexCoord2i(1, 1);
	glVertex2i(this->GetWidth(), this->GetHeight());
	glTexCoord2i(0, 1);
	glVertex2i(0, this->GetHeight());
	glTexCoord2i(0, 0);
	glEnd();
	*/
		//glPopAttrib();
		//glDeleteTextures(1, &this->texture_handle);
	glPopMatrix();	
	glFlush();
	
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

/*
 * ********************************************************
 * Setters 
 * ********************************************************
 */

void Sprite::SetSize(float width, float height){
	this->width = width;
	this->height = height;
}

