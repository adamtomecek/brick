#include "Includes.h"
#include "Game.h"
#include "Object.h"
#include "BoxObject.h"
#include "CircleObject.h"
#include "Scene.h"
#include "Sprite.h"
#include "Game.h"

int main(int argc, char **argv)
{
	/* sem_t *sem = Utils::GetBoxSem(); */
	/* if ((sem = sem_open( */
	/* 		B2DSEM, O_CREAT, S_IRUSR | S_IWUSR, 1) */
	/* 	) == SEM_FAILED){ */
	/* 	std::cout << "Semaphore error" << std::endl; */	
	/* }else{ */
	/* 	std::cout << "Sem created" << std::endl; */
	/* } */

	/* sem_post(sem); */

	int luaErr;
		
	lua_State *luaState = lua_open();
	luaL_openlibs(luaState);
	
	if (luaErr != 0)
		std::cout << "Lua load file error: " << lua_tostring(luaState, -1) << std::endl;
	/* Load Lua Game instance source file */

	
	luabind::open(luaState);
	Game::Lua(luaState);
	Node::Lua(luaState);
	Scene::Lua(luaState);
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

	/* luaErr = luaL_dostring(luaState, */
	/* 		"game = MyGame.new()\n" */
	/* ); */

	if (luaErr != 0)
		std::cout << "Lua init error: " << lua_tostring(luaState, -1) << std::endl;
	
	/* luabind::object myGame = luabind::globals(luaState); */
	/* luabind::object keyboardInputCallback; */
	/* luabind::object mouseInputCallback; */
	/* luabind::object loopCallback; */
	
	/* if (myGame){ */
	/* 	keyboardInputCallback = myGame["handle_keyboard_input"]; */
	/* 	mouseInputCallback = myGame["handle_mouse_input"]; */
	/* 	loopCallback = myGame["loop"]; */
	/* }else { */
	/* 	std::cout << "Lua init error: can't get 'game' variable" << std::endl; */
	/* } */

	Utils::SetLuaState(luaState);
	
	luaErr = luaL_dofile(luaState, "main.lua");
	if (luaErr != 0)
		std::cout << "Lua load file error: " << lua_tostring(luaState, -1) << std::endl;

	/* Game *game = new Game(); */
	/* game->Loop(); */
	while(1){

	}

	lua_close(luaState);
    return EXIT_SUCCESS;
}

