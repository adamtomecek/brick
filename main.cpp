#include "Game.h"
#include "Object.h"
#include "BoxObject.h"
#include "CircleObject.h"
#include "Scene.h"
#include "Sprite.h"
#include "DebugDraw.h"

int main(int argc, char **argv)
{
	// Create main window
    sf::RenderWindow App(sf::VideoMode(800, 600), "SFML OpenGL");

	sf::WindowSettings Settings = App.GetSettings();

	Settings.DepthBits = 24;
	Settings.StencilBits = 8;
	Settings.AntialiasingLevel = 4;

    App.PreserveOpenGLStates(true);
	App.SetFramerateLimit(60);
	
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


	// Create a clock for measuring the time elapsed
    sf::Clock Clock;
	
	
	float lastTime = 0;
	
	int luaErr;
		
	lua_State *luaState = lua_open();
	luaL_openlibs(luaState);
	
	/* Load Lua Game instance source file */
	luaErr = luaL_dofile(luaState, "main.lua");
	if (luaErr != 0)
		std::cout << "Lua load file error: " << lua_tostring(luaState, -1) << std::endl;
	
	luaL_openlibs(luaState);
	luabind::open(luaState);
	Node::Lua(luaState);
	Chunk::Lua(luaState);
	Sprite::Lua(luaState);
	Object::Lua(luaState);
	BoxObject::Lua(luaState);
	CircleObject::Lua(luaState);

	luabind::module(luaState)
		[
		 luabind::class_<sf::Event::KeyEvent>("Key")
		 .enum_("constants")
		 [
		  luabind::value("down", sf::Key::Down),
		  luabind::value("up", sf::Key::Up),
		  luabind::value("left", sf::Key::Left),
		  luabind::value("right", sf::Key::Right)
		 ]
		];
	
	bool doSleep = true;
	b2Vec2 gravity(0, 1.0f);

	float timestep = 1 / 60;
	b2World *world = Utils::GetWorld();
	world = new b2World(gravity);
	Utils::SetWorld(world);
	
	if (DEBUG_DRAW) {
		DebugDraw debug;
		uint32 flags = 0;
		flags += 1	* b2Draw::e_shapeBit;
		flags += 1	* b2Draw::e_jointBit;
		//flags += 1	* b2Draw::e_aabbBit;
		flags += 1	* b2Draw::e_pairBit;
		flags += 1	* b2Draw::e_centerOfMassBit;
	
		debug.SetFlags(flags);
	
		world->SetDebugDraw(&debug);
	}
	
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0.0f, 0.0f);

	b2Body *groundBody = world->CreateBody(&groundBodyDef);

	b2EdgeShape groundEdge;
	b2FixtureDef boxShapeDef;
	boxShapeDef.shape = &groundEdge;
	groundEdge.Set(b2Vec2(0.0f, 600.0f / RATIO), b2Vec2(800.0f / RATIO, 600.0f / RATIO));
	groundBody->CreateFixture(&boxShapeDef);

	Sprite *x = new Sprite("icon.jpg", 200, 200);

	boost::shared_ptr<BoxObject> o (new BoxObject(x));	
	boost::shared_ptr<Node> n (new Node());

	n->AddChild(o);


	luaErr = luaL_dostring(luaState,
			"game = MyGame.new()\n"
	);

	if (luaErr != 0)
		std::cout << "Lua init error: " << lua_tostring(luaState, -1) << std::endl;
	
	luabind::object myGame = luabind::globals(luaState)["game"];
	luabind::object inputCallback;
	luabind::object loopCallback;
	
	if (myGame){
		inputCallback = myGame["handle_input"];
		loopCallback = myGame["loop"];
	}else {
		std::cout << "Lua init error: can't get 'game' variable" << std::endl;
	}
	

	Scene *myScene = new Scene();

	// Start game loop
    while (App.IsOpened())
    {
			// Process events
        sf::Event Event;
        while (App.GetEvent(Event))
        {
				// Close window : exit
            if (Event.Type == sf::Event::Closed)
                App.Close();
			
				// Escape key : exit
            if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Escape))			
				App.Close();

			if(Event.Type == sf::Event::KeyPressed){
				if (inputCallback) {
					luabind::call_function<void>(inputCallback, Event.Key.Code);
				}else {
					std::cout << "Lua input error: method 'MyGame.handle_input' doesn't exist" << std::endl;
				}

			}



				// Adjust the viewport when the window is resized
            if (Event.Type == sf::Event::Resized)
                glViewport(0, 0, Event.Size.Width, Event.Size.Height);
		}
		
		world->Step(TIME_STEP, VELOCITY_ITERATIONS, POSITION_ITERATIONS);
		
		
		if (DEBUG_DRAW) {
			glLoadIdentity();
			glDisable(GL_TEXTURE_2D);
			glDisableClientState(GL_COLOR_ARRAY);
			glDisableClientState(GL_TEXTURE_COORD_ARRAY);
			glEnableClientState(GL_VERTEX_ARRAY);
			glPushMatrix();
			glScalef(RATIO, RATIO, 0);
			world->DrawDebugData();
			glPopMatrix();
			glEnable(GL_TEXTURE_2D);
			glEnableClientState(GL_COLOR_ARRAY);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		}
		
		n->Render();
		
		/* call Lua Game instance Loop function */
		
		if (loopCallback) {
			luabind::call_function<void>(loopCallback);
		}else {
			/* std::cout << "Lua loop error: method 'MyGame.loop' doesn't exist" << std::endl; */
		}

		if (luaErr != 0)
			std::cout << "Lua loop error: " << lua_tostring(luaState, -1) << std::endl;
		
		
/*
		float elapsed = Clock.GetElapsedTime();
		float fps = 1.f / App.GetFrameTime();
		lastTime = elapsed;

		myScene->drawFPS(fps);
*/
		// Finally, display the rendered frame on screen
        App.Display();
		App.Clear();
    }
	lua_close(luaState);
    return EXIT_SUCCESS;
}
