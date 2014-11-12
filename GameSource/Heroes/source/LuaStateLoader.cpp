
#include <SDL_assert.h>

#include "States/GamePlayState/LuaStateLoader.h"

namespace Heroes
{
	namespace States
	{
		namespace GamePlay
		{

			LuaStateLoader::LuaStateLoader() {}
			LuaStateLoader::~LuaStateLoader() {}

			lua_State* LuaStateLoader::GetRendererEntityLuaState()
			{
				lua_State* luaState = CreateAndBindLuaState();
				LoadGeneralEntityAccess(luaState);
				LoadRendererEntityAccess(luaState);
				return luaState;
			}

			lua_State* LuaStateLoader::GetGerneralEntityLuaState()
			{
				lua_State* luaState = CreateAndBindLuaState();
				LoadGeneralEntityAccess(luaState);
				return luaState;
			}

			void LuaStateLoader::CloseLuaState(lua_State* luaState)
			{
				SDL_assert(luaState != nullptr);
				lua_close(luaState);
			}

			lua_State* LuaStateLoader::CreateAndBindLuaState()
			{
				lua_State *luaState = luaL_newstate();
				SDL_assert(luaState != nullptr);
				luabind::open(luaState);
				return luaState;
			}

			void LuaStateLoader::LoadGeneralEntityAccess(lua_State* luaState)
			{
				//// all the class and functions for general lua scripts
				//// Add our function to the state's global scope
				//luabind::module(luaState)[
				//	luabind::def("print_hello", print_hello)
				//];

				//luabind::module(luaState)[
				//	luabind::def("SDL_GameControllerGetButton", &SDL_GameControllerGetButton)
				//];

				////luabind::call_function(myLuaState, "SDL_GameControllerGetButton", nullptr, SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_BACK)

				//// Now call our function in a lua script
				//luaL_dostring(
				//	myLuaState,
				//	"print_hello(123)\n"
				//	);
			}

			void LuaStateLoader::LoadRendererEntityAccess(lua_State* luaState)
			{
				// the specifc sdl rendering componenets for lua scripts
			}

		} // namespace GamePlay
	} // namespace States
} //namespace Heroes

