/*
 *  Includes.h
 *  sfml
 *
 *  Created by Adam Tomeček on 11/18/12.
 *  Copyright 2012 Brain Dead Cookie. All rights reserved.
 *
 */

#ifndef INCLUDES_H
#define INCLUDE_H

#include <iostream>
#include <list>
#include <typeinfo>
#include <memory>
#include <tr1/functional>
#include <string>
#include <cmath>
#include <fstream>
#include <boost/tr1/memory.hpp>
#include <boost/enable_shared_from_this.hpp>

#include <semaphore.h>
#include <pthread.h>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <OpenGl/OpenGL.h>
#include <OpenGl/CGLRenderers.h>
#include <OpenGL/CGLTypes.h>
#include <Box2D/Box2D.h>

extern "C"
{
#include "lua.h"
#include "lualib.h"
}

#include "lua/luabind/luabind.hpp"
#include "lua/luabind/function.hpp"
#include "lua/luabind/class.hpp"
#include "lua/luabind/adopt_policy.hpp"
#include "lua/luabind/object.hpp"
#include "lua/luabind/dependency_policy.hpp"
#include "lua/luabind/out_value_policy.hpp"
#include "lua/luabind/return_reference_to_policy.hpp"
#include "lua/luabind/copy_policy.hpp"
#include "lua/luabind/discard_result_policy.hpp"
#include "lua/luabind/raw_policy.hpp"


#include "Utils.h"

#define RATIO 100.0f
#define TIME_STEP 1.0f / 60.0f
#define VELOCITY_ITERATIONS 8
#define POSITION_ITERATIONS 3
#define DEBUG_DRAW false
/* #define DEBUG */

#define B2DSEM "sfml-box2d"

#endif

