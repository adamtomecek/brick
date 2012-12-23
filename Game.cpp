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

	glViewport(0,0,800,600);
	glEnable(GL_TEXTURE_RECTANGLE_EXT);
	glDisable( GL_LIGHTING );
	/* glDisable(GL_DITHER); */
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);

	// Setup a perspective projection
	glMatrixMode(GL_PROJECTION);

	glAlphaFunc(GL_GREATER, 0.5);
	glEnable(GL_ALPHA_TEST);

	glOrtho(0, 800, 600, 0, -100, 100);
	// Setup a perspective projection
	glMatrixMode(GL_MODELVIEW);

	// Displacement trick for exact pixelization
	glTranslatef(0.375, 0.375, 0);
	/* glTranslatef(0, 0, -5); */

	// Box2D initialization
	b2Vec2 gravity(0, 9.8f);

	b2World *w = Utils::GetWorld();
	w = new b2World(gravity);
	w->SetContinuousPhysics(true);
	this->world = w;
	Utils::SetWorld(w);

	// Ground definition
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0.0f / RATIO / 2, 0.0f / RATIO / 2);

	b2Body *groundBody = w->CreateBody(&groundBodyDef);

	b2EdgeShape groundEdge;
	b2FixtureDef boxShapeDef;
	boxShapeDef.shape = &groundEdge;
	groundEdge.Set(b2Vec2(0.0f, 600.0f / RATIO), b2Vec2(800.0f / RATIO, 600.0f / RATIO));

	/* b2PolygonShape groundBox; */
	/* groundBox.SetAsBox(800.0f / RATIO / 2, 600.0f / RATIO / 2); */
	/* groundBody->CreateFixture(&groundBox, 1.0f); */
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
		// Clear previouslz rendered objects
		this->app->Clear();

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


			// Adjust the viewport when the window is resized
            if (Event.Type == sf::Event::Resized)
                glViewport(0, 0, Event.Size.Width, Event.Size.Height);

			// Update input	
			this->input->Loop(&Event);
			this->HandleInput();
		}


		// Game logic for Lua
		this->Step();
		this->world->Step(TIME_STEP, VELOCITY_ITERATIONS, POSITION_ITERATIONS);

		if (DEBUG_DRAW) {
			std::cout << "DebugDraw" << std::endl;
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

		// Finally, display the rendered frame on screen
		this->scene->Render();
        this->app->Display();
		this->app->Clear();
		glClear(GL_DEPTH_BUFFER_BIT);
		glClear(GL_COLOR_BUFFER_BIT);

    }
	return EXIT_SUCCESS;
}

void Game::Step(void){

}

void Game::HandleInput(void){
	std::list<unsigned short> keys = this->input->GetKeys();
	std::list<unsigned short>::iterator i;

	MouseInput *m = this->input->GetMouse();

	unsigned short tmp;

	for(i = keys.begin(); i != keys.end(); i++){
		tmp = *i;
		this->scene->KeyboardInput(tmp);
	}

	if(m->buttonCode != -1)
		this->scene->MouseInput(m->x, m->y, m->buttonCode);
}

void Game::SetScene(Scene *s){
	this->scene = s;
}

