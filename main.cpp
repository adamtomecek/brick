#include "Includes.h"
#include "Game.h"
#include "NodeWrapper.h"
#include "SceneWrapper.h"
#include "ChunkWrapper.h"
#include "SpriteWrapper.h"
#include "ObjectWrapper.h"
#include "BoxObjectWrapper.h"
#include "CircleObjectWrapper.h"
#include "GameWrapper.h"

int main(int argc, char **argv)
{
	int luaErr;
		
	lua_State *luaState = lua_open();
	luaL_openlibs(luaState);
	
	if (luaErr != 0)
		std::cout << "Lua load file error: " << lua_tostring(luaState, -1) << std::endl;
	/* Load Lua Game instance source file */

	
	luabind::open(luaState);
	GameWrapper::Lua(luaState);
	NodeWrapper::Lua(luaState);
	SceneWrapper::Lua(luaState);
	ChunkWrapper::Lua(luaState);
	SpriteWrapper::Lua(luaState);
	ObjectWrapper::Lua(luaState);
	BoxObjectWrapper::Lua(luaState);
	CircleObjectWrapper::Lua(luaState);

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
	
	luabind::module(luaState)
		[
		 luabind::class_<sf::Event::MouseButtonEvent>("Mouse")
		 .enum_("constants")
		 [
		  luabind::value("left", sf::Mouse::Left),
		  luabind::value("right", sf::Mouse::Right),
		  luabind::value("middle", sf::Mouse::Middle)
		 ]
		];

	if (luaErr != 0)
		std::cout << "Lua init error: " << lua_tostring(luaState, -1) << std::endl;
	
	Utils::SetLuaState(luaState);
	
	luaErr = luaL_dofile(luaState, "main.lua");
	if (luaErr != 0)
		std::cout << "Lua load file error: " << lua_tostring(luaState, -1) << std::endl;

	/* Game *g = new Game(); */
	/* Sprite *sp = new Sprite("circle.png", 100, 100, 100, 100); */
	/* CircleObject *o = new CircleObject(sp); */
	/* Scene *s = new Scene(); */
	/* g->SetScene(s); */
	/* g->Loop(); */

	lua_close(luaState);
    return EXIT_SUCCESS;
}

