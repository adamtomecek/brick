/*
 *  Game.cpp
 *  sfml
 *
 *  Created by Adam Tomeček on 11/18/12.
 *  Copyright 2012 Brain Dead Cookie. All rights reserved.
 *
 */

#include "Game.h"

Game::Game(){
	// create app window
	this->app = new sf::RenderWindow(sf::VideoMode(800, 600), "Game");

	this->luaState = Utils::GetLuaState();
	const sf::Input &in = this->app->GetInput();
	this->input = new Input(&in);
	this->b2Sem = Utils::GetBoxSem();

	this->Setup();
}

void Game::Setup(void){
	sf::WindowSettings s = this->app->GetSettings();

	s.DepthBits = 24;
	s.StencilBits = 8;
	s.AntialiasingLevel = 4;


    this->app->PreserveOpenGLStates(true);
	this->app->SetFramerateLimit(60);

	// Setup a perspective projection
    glMatrixMode(GL_PROJECTION);
	glOrtho (0, 800, 600, 0, 0, 1);
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_RECTANGLE_EXT);
	glMatrixMode(GL_MODELVIEW);
	glDisable(GL_BLEND);
	glDisable( GL_LIGHTING );
	glDisable( GL_DITHER );

	// Displacement trick for exact pixelization
	glTranslatef(0.375, 0.375, 0);


	// Box2D initialization
	b2Vec2 gravity(0, 1.0f);

	b2World *w = Utils::GetWorld();
	w = new b2World(gravity);
	w->SetContinuousPhysics(true);
	this->world = w;
	Utils::SetWorld(w);

	// Ground definition
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0.0f, 0.0f);

	b2Body *groundBody = w->CreateBody(&groundBodyDef);

	b2EdgeShape groundEdge;
	b2FixtureDef boxShapeDef;
	boxShapeDef.shape = &groundEdge;
	groundEdge.Set(b2Vec2(0.0f, 600.0f / RATIO), b2Vec2(800.0f / RATIO, 600.0f / RATIO));
	groundBody->CreateFixture(&boxShapeDef);

	// DebugDraw initialization
	if (DEBUG_DRAW) {
		DebugDraw debug;
		uint32 flags = 0;
		flags += 1	* b2Draw::e_shapeBit;
		flags += 1	* b2Draw::e_jointBit;
		//flags += 1	* b2Draw::e_aabbBit;
		flags += 1	* b2Draw::e_pairBit;
		flags += 1	* b2Draw::e_centerOfMassBit;
	
		debug.SetFlags(flags);
	
		this->world->SetDebugDraw(&debug);
	}

}
int Game::Loop(void){
	// Start game loop
    while (this->app->IsOpened())
    {
		// Process events
        sf::Event Event;
        while (this->app->GetEvent(Event))
        {
			// Close window : exit
            if (Event.Type == sf::Event::Closed)
                this->app->Close();
			
			// Escape key : exit
            if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Escape))			
				this->app->Close();

			/* if(Event.Type == sf::Event::KeyPressed){ */
			/* 	if (keyboardInputCallback) { */
			/* 		luabind::call_function<void>(keyboardInputCallback, Event.Key.Code); */
			/* 	}else { */
			/* 		std::cout << "Lua input error: method 'MyGame.handle_keyboard_input' doesn't exist" << std::endl; */
			/* 	} */
			/* } */

			/* if(Event.Type == sf::Event::MouseButtonPressed){ */
			/* 	if (mouseInputCallback) { */
			/* 		luabind::call_function<void>(mouseInputCallback, Event.MouseButton.Button, Event.MouseButton.X, Event.MouseButton.Y); */
			/* 	}else { */
			/* 		std::cout << "Lua input error: method 'MyGame.handle__input' doesn't exist" << std::endl; */
			/* 	} */
			/* } */

			// Adjust the viewport when the window is resized
            if (Event.Type == sf::Event::Resized)
                glViewport(0, 0, Event.Size.Width, Event.Size.Height);
		}

		this->world->Step(TIME_STEP, VELOCITY_ITERATIONS, POSITION_ITERATIONS);
		
		if (DEBUG_DRAW) {
			glLoadIdentity();
			glDisable(GL_TEXTURE_2D);
			glDisableClientState(GL_COLOR_ARRAY);
			glDisableClientState(GL_TEXTURE_COORD_ARRAY);
			glEnableClientState(GL_VERTEX_ARRAY);
			glPushMatrix();
			glScalef(RATIO, RATIO, 0);
			this->world->DrawDebugData();
			glPopMatrix();
			glEnable(GL_TEXTURE_2D);
			glEnableClientState(GL_COLOR_ARRAY);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		}
		
		/* /1* call Lua Game instance Loop function *1/ */
		
		/* if (loopCallback) { */
		/* 	luabind::call_function<void>(loopCallback); */
		/* }else { */
		/* 	/1* std::cout << "Lua loop error: method 'MyGame.loop' doesn't exist" << std::endl; *1/ */
		/* } */

		/* if (luaErr != 0) */
		/* 	std::cout << "Lua loop error: " << lua_tostring(this->luaState, -1) << std::endl; */
		
		// Update input	
		this->input->Loop();

		// Finally, display the rendered frame on screen

		this->scene->Render();
        this->app->Display();
		this->app->Clear();
    }
	return EXIT_SUCCESS;
}

void Game::SetScene(Scene *s){
	this->scene = s;
}

