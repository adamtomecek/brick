
	////////////////////////////////////////////////////////////
	// Headers
	////////////////////////////////////////////////////////////

#include "Game.h"
#include "Object.h"
#include "Scene.h"


	////////////////////////////////////////////////////////////
	/// Entry point of application
	///
	/// \return Application exit code
	///
	////////////////////////////////////////////////////////////
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
	glLoadIdentity();

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

	Object *o = new Object(&world, 64, 64, 420.0f, 000.0f, 10);
	Object *o2 = new Object(&world, 128, 128, 440.0f, 150.0f, 10);

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
			
				// Adjust the viewport when the window is resized
            if (Event.Type == sf::Event::Resized)
                glViewport(0, 0, Event.Size.Width, Event.Size.Height);
		}
		
		o2->draw();
		o->draw();
		/* o->move(1, 1, 0); */

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
