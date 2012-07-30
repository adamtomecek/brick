#include "Game.h"
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
	glEnable(GL_TEXTURE_2D);
	glMatrixMode(GL_MODELVIEW);

	// Displacement trick for exact pixelization
	glTranslatef(0.375, 0.375, 0);


	// Create a clock for measuring the time elapsed
    sf::Clock Clock;
	float lastTime = 0;
	
	lua_State *luaState = luaL_newstate();
	luabind::open(luaState);
	Sprite::Lua(luaState);
	
	
	

	bool doSleep = true;
	b2Vec2 gravity(0, 1.0f);

	float timestep = 1 / 60;

	b2World world(gravity);
	
	/*
	DebugDraw debug;
	uint32 flags = 0;
	flags += 1	* b2Draw::e_shapeBit;
	flags += 1	* b2Draw::e_jointBit;
		//flags += 1	* b2Draw::e_aabbBit;
	flags += 1	* b2Draw::e_pairBit;
	flags += 1	* b2Draw::e_centerOfMassBit;
	
	debug.SetFlags(flags);
	
	world.SetDebugDraw(&debug);
	*/
	
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0.0f, 0.0f);

	b2Body *groundBody = world.CreateBody(&groundBodyDef);

	b2EdgeShape groundEdge;
	b2FixtureDef boxShapeDef;
	boxShapeDef.shape = &groundEdge;
	groundEdge.Set(b2Vec2(0.0f, 600.0f / RATIO), b2Vec2(800.0f / RATIO, 600.0f / RATIO));
	groundBody->CreateFixture(&boxShapeDef);

	Sprite *s = new Sprite("circle.png", 64.0, 64.0, 100.0, 0.0);
	Sprite *s2 = new Sprite("circle.png", 120.0, 120.0, 300.0, 100.0);
	Sprite *s3 = new Sprite("circle.png", 100.0, 100.0, 500.0, 100.0);
	Sprite *s4 = new Sprite("icon.jpg", 64.0, 64.0, 60.0, 200.0);
	Sprite *s5 = new Sprite("icon.jpg", 120.0, 120.0, 280.0, 300.0);
	Sprite *s6 = new Sprite("icon.jpg", 100.0, 100.0, 700.0, 0.0, 40);

	Sprite *x = new Sprite("icon.jpg", 100, 100);
	Sprite *x2 = new Sprite("icon.jpg", 200, 200);
	Sprite *x3 = new Sprite("icon.jpg", 300, 0);

	x2->AddChild(x3);
	x->AddChild(x2);



	CircleObject *o = new CircleObject(&world, s);
	CircleObject *o2 = new CircleObject(&world, s2);
	CircleObject *o3 = new CircleObject(&world, s3);
	BoxObject *o4 = new BoxObject(&world, s4);
	BoxObject *o5 = new BoxObject(&world, s5);
	BoxObject *o6 = new BoxObject(&world, s6);

	
	Node *n = new Node();
	n->AddChild(o);
	n->AddChild(o2);
	n->AddChild(o3);
	n->AddChild(o4);
	n->AddChild(o5);
	n->AddChild(o6);
	

	n->AddChild(x);
	
	luaL_dostring(luaState,
		"s = Sprite(\"icon.jpg\", 0, 0, 0)\n"
	);
	
	

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


				// Adjust the viewport when the window is resized
            if (Event.Type == sf::Event::Resized)
                glViewport(0, 0, Event.Size.Width, Event.Size.Height);
		}
		
		world.Step(TIME_STEP, VELOCITY_ITERATIONS, POSITION_ITERATIONS);
		
		x->Rotate(1.0f);
		x2->Rotate(-2.0f);
		Position x1center = x3->GetCenter();
		x->RotateAroundPoint(x1center.x, x1center.y, 0.2f);
		
		/*
		glLoadIdentity();
		glDisable(GL_TEXTURE_2D);
		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glEnableClientState(GL_VERTEX_ARRAY);
		glPushMatrix();
		glScalef(RATIO, RATIO, 0);
		world.DrawDebugData();
		glPopMatrix();
		glEnable(GL_TEXTURE_2D);
		glEnableClientState(GL_COLOR_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		*/
		
		n->Render();
		
		
		/* luaL_dostring(luaState, */
		/* 			  "s:Render()\n" */
		/* 			  ); */

		float elapsed = Clock.GetElapsedTime();
		float fps = 1.f / App.GetFrameTime();
		lastTime = elapsed;

		myScene->drawFPS(fps);

		// Finally, display the rendered frame on screen
        App.Display();
		App.Clear();
    }
	lua_close(luaState);
    return EXIT_SUCCESS;
}
