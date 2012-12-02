/*
 *  Input.cpp
 *  sfml
 *
 *  Created by Adam Tomeček on 11/17/12.
 *  Copyright 2012 Brain Dead Cookie. All rights reserved.
 *
 */

#include "Input.h"

Input::Input(const sf::Input *i){
	this->input = i;
}

MouseInput* Input::GetMouse(void){
	return &this->mouse;
}

std::list<unsigned short> Input::GetKeys(void){
	return keys;
}

bool Input::IsKeyDown(unsigned short key){
	std::list<unsigned short>::iterator i;

	unsigned short tmp;
	
	for(i = this->keys.begin(); i != this->keys.end(); i++){
		tmp = *i;
		if(tmp == key)
			return true;
	}
	
	return false;	
}

void Input::Loop(sf::Event *e){
	keys.clear();
	mouse.buttonCode = -1;

	if(this->input->IsKeyDown(sf::Key::Left))
		keys.push_back(sf::Key::Left);

	if(this->input->IsKeyDown(sf::Key::Right))
		keys.push_back(sf::Key::Right);

	if(this->input->IsKeyDown(sf::Key::Up))
		keys.push_back(sf::Key::Up);

	if(this->input->IsKeyDown(sf::Key::Down))
		keys.push_back(sf::Key::Down);


	/* mouse input */
	if(e->Type == sf::Event::MouseButtonReleased){
		this->mouse.x = e->MouseButton.X;
		this->mouse.y = e->MouseButton.Y;
		this->mouse.buttonCode = e->MouseButton.Button;
	}
}

