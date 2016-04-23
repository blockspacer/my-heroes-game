#include "Engine/StateEngine.h"
#include "States/MainMenuState/MainMenuState.h"

int main(int argc, char** argv)
{
	using namespace Heroes;
	using namespace Heroes::Engine;

	
	//// Create a new lua state
	//lua_State *luaState = luaL_newstate();

	//// Connect LuaBind to this lua state
	//luabind::open(luaState);

	//luabind::module(luaState)[
	//	luabind::def("SDL_GameControllerGetButton", &print_hello)
	//];

	//luabind::object f = luabind::globals(luaState);
	//g_assert(f);
	//luabind::object t = f["SDL_GameControllerGetButton"];
	//g_assert(t.is_valid());
	//t(SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_BACK);

	////luabind::call_function<Uint8>(luaState, "SDL_GameControllerGetButton", nullptr, SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_BACK)

	////luabind::object f;

	//// Now call our function in a lua script
	///*luaL_dostring(
	//	myLuaState,
	//	"print_hello(123)\n"
	//	);*/

	StateEngine stateEngine;
	if (!stateEngine.Init())
	{
		return 1;
	}

	StateCreationPackage firstStateCreationPackage = StateCreationPackage(States::MainMenu::CreateMainMenuState, StateCreationData(NoStateCreationData, false));
	stateEngine.Run(firstStateCreationPackage); // main menu
	
	stateEngine.Destroy();

    return 0;
}