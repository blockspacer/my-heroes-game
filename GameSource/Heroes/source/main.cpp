#include "Engine/StateEngine.h"
#include "States/MainMenuState/MainMenuState.h"

int main(int argc, char** argv)
{
	using namespace Heroes;
	using namespace Heroes::Engine;

	StateEngine stateEngine = StateEngine();
	if (!stateEngine.Init())
	{
		return 1;
	}

	StateCreationPackage firstStateCreationPackage = StateCreationPackage(States::MainMenu::CreateMainMenuState, StateCreationData());
	stateEngine.Run(firstStateCreationPackage); // main menu
	
	stateEngine.Destroy();

    return 0;
}