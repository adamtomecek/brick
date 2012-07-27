/*
 *  Game.h
 *  sfml
 *
 *  Created by Adam Tomeček on 7/11/12.
 *  Copyright 2012 Brain Dead Cookie. All rights reserved.
 *
 */

#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <list>
#include <typeinfo>
#include <memory>
#include <tr1/functional>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <OpenGL/CGLTypes.h>
#include <Box2D/Box2D.h>

extern "C"
{
#include "lua.h"
}

#include <luabind/luabind.hpp>

#include "Utils.h"

#define RATIO 75.0f
#define TIME_STEP 1.0f / 60.0f
#define VELOCITY_ITERATIONS 8
#define POSITION_ITERATIONS 3


#endif