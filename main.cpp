#include "Game.h"
#include "Object.h"
#include "Scene.h"
#include "Sprite.h"


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

	bool doSleep = true;
	b2Vec2 gravity(0, 9.8f);

	float scale = 30;
	float timestep = 1 / 60;

	b2World world(gravity);

	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0.0f, 0.0f);

	b2Body *groundBody = world.CreateBody(&groundBodyDef);

	b2EdgeShape groundEdge;
	b2FixtureDef boxShapeDef;
	boxShapeDef.shape = &groundEdge;
	groundEdge.Set(b2Vec2(0.0f, 600.0f / RATIO), b2Vec2(800.0f / RATIO, 600.0f / RATIO));
	groundBody->CreateFixture(&boxShapeDef);

	Sprite *s = new Sprite("test.png", 100.0, 100.0, 100.0, 100.0);
	Sprite *s2 = new Sprite(100.0, 100.0, 300.0, 300.0);
	Sprite *s3 = new Sprite("icon.jpg", 200.0, 200.0, 150.0, 150.0);


	Object *o = new Object(&world, s);
	Object *o2 = new Object(&world, s2);
	Object *o3 = new Object(&world, s3);
	
	Node *n = new Node();
	n->AddChild(o);
	n->AddChild(o2);
	n->AddChild(o3);

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
			//o2->draw();
			//o->draw();
		
		/* o->move(1, 1, 0); */
		
			n->Render();
			//s->Render();
			//s2->Render();

		float elapsed = Clock.GetElapsedTime();
		float fps = 1.f / App.GetFrameTime();
		lastTime = elapsed;

		myScene->drawFPS(fps);

		// Finally, display the rendered frame on screen
        App.Display();
		App.Clear();
    }
	
    return EXIT_SUCCESS;
}
