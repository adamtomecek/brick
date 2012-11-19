/*
 *  Input.h
 *  sfml
 *
 *  Created by Adam Tomeček on 11/17/12.
 *  Copyright 2012 Brain Dead Cookie. All rights reserved.
 *
 */

#ifndef INPUT_H
#define INPUT_H

#include "Includes.h"

typedef struct{
	unsigned int x;
	unsigned int y;
	short buttonCode;
}MouseInput;

class Input{

	public:
		Input(const sf::Input *input);
		void Loop(sf::Event *e);

		MouseInput* GetMouse(void);
		std::list<unsigned short> GetKeys(void);
		bool IsKeyDown(unsigned short key);

	private:
		const sf::Input *input;
		std::list<unsigned short> keys;
		MouseInput mouse;
};

#endif

