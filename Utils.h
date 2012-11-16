/*
 *  Utils.h
 *  sfml
 *
 *  Created by Adam Tomeček on 7/15/12.
 *  Copyright 2012 Brain Dead Cookie. All rights reserved.
 *
 */

#ifndef UTILS_H
#define UTILS_H

#include "Game.h"

struct Position{
	float x;
	float y;
};

struct Size{
	float width;
	float height;
};

struct PointRotation{
	float x;
	float y;
	float angle;
};

class Utils{
public:
	static Utils& GetInstance(){
		static  Utils *singleClass = NULL;
		if (singleClass == NULL)
			singleClass = new Utils;
		return *singleClass;
	}
	
	static b2World* GetWorld(){
		return world;
	}
	
	static b2World* SetWorld(b2World *w){
		world = w;
	}
private:
	Utils();
        // Dont forget to declare these two. You want to make sure they
        // are unaccessable otherwise you may accidently get copies of
        // your singleton appearing.
	Utils(Utils const&);              // Don't Implement
	void operator=(Utils const&); // Dont implement
	
	static b2World *world;
};


#endif
