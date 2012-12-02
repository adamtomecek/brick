#include "Includes.h"
#include "Game.h"
#include "Object.h"
#include "BoxObject.h"
#include "CircleObject.h"
#include "Scene.h"
#include "Sprite.h"
#include "GameWrapper.h"
#include "SceneWrapper.h"
#include "NodeWrapper.h"

int main(int argc, char **argv)
{
	int luaErr;
		
	lua_State *luaState = lua_open();
	luaL_openlibs(luaState);
	
	if (luaErr != 0)
		std::cout << "Lua load file error: " << lua_tostring(luaState, -1) << std::endl;
	/* Load Lua Game instance source file */

	
	luabind::open(luaState);
	NodeWrapper::Lua(luaState);
	GameWrapper::Lua(luaState);
	SceneWrapper::Lua(luaState);
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

	while(1){

	}

	lua_close(luaState);
    return EXIT_SUCCESS;
}

