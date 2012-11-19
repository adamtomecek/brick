/*
 *  Utils.cpp
 *  sfml
 *
 *  Created by Adam Tomeček on 7/15/12.
 *  Copyright 2012 Brain Dead Cookie. All rights reserved.
 *
 */

#include "Utils.h"

b2World *Utils::world = NULL;
lua_State *Utils::luaState = NULL;
sem_t *Utils::boxSem = NULL;
