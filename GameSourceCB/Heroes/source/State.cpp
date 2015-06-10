// Heroes Game
// Author: Samuel Hall
// Last Commented ? Need to migrate code to InputHandler

#include "Engine/Log.h"
#include "Engine/State.h"

namespace Heroes
{
namespace Engine
{
// These functions are all just initialization code for a state

State* CreateEndState(Engine::InputHandler& inputHandler, Engine::SDLUtilityTool& sdlUtilityTool, StateCreationData& structData)
{
    return NULL;
}

StateCreationData::StateCreationData(UserDataType userData, bool dataAllocated) : m_userData(userData), m_dateAllocated(dataAllocated) {}

bool StateCreationData::HasUserData()
{
    return m_userData != NULL;
}

UserDataType StateCreationData::GetUserData()
{
    return m_userData;
}

StateCreationFunction::StateCreationFunction(CreateStateFunc createStateFunc) : m_createStateFunc(createStateFunc) {}

bool StateCreationFunction::HasStateCreationFunc()
{
    return m_createStateFunc != NULL;
}

State* StateCreationFunction::CallStateCreationFunction(Engine::InputHandler& inputHandler, Engine::SDLUtilityTool& sdlUtilityTool, StateCreationData& stateCreationData)
{
    g_assert(HasStateCreationFunc() == true);
    return m_createStateFunc(inputHandler, sdlUtilityTool, stateCreationData);
}



State::State(Engine::InputHandler& inputHandler,
             Engine::SDLUtilityTool& sdlUtilityTool,
             Engine::StateCreationData& stateCreationData) : m_sdlUtilityTool(sdlUtilityTool),
    m_inputHandler(inputHandler),
    m_stateCreatePackage(Engine::CreateEndState,
                         Engine::StateCreationData(Engine::NoStateCreationData, false))
{
    /*
     * This creates the common SDL resources that all states should need
     * Window, Renderer, Surface, Texture
     *
     */

    m_sdlWindow = sdlUtilityTool.CreateWindow("Heroes", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1366, 768, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
    g_assert(m_sdlWindow != NULL);

    m_sdlRenderer = sdlUtilityTool.CreateRenderer(m_sdlWindow, -1, SDL_RENDERER_ACCELERATED);
    g_assert(m_sdlRenderer != NULL);

    SDL_DisplayMode display;
    SDL_GetWindowDisplayMode(m_sdlWindow, &display);

    m_sdlSurface = sdlUtilityTool.CreateRGBSurface(0, display.w, display.h, 32);
    g_assert(m_sdlSurface != NULL);

    m_sdlTexture = sdlUtilityTool.CreateTextureFromSurface(m_sdlRenderer, m_sdlSurface);
    g_assert(m_sdlTexture != NULL);

    // TODO - REMOVE THIS AND PUT IT IN THE INPUT HANDLER
    g_assert(SDL_NumJoysticks() != 0);
    if (SDL_IsGameController(0))
    {
        m_controller = sdlUtilityTool.GameControllerOpen(0);
    }
    g_assert(m_controller != NULL);
}

State::~State()
{
    // broken because input handler cant be destroyed
    m_sdlUtilityTool.GameControllerClose(m_controller);
    m_sdlUtilityTool.DestroyTexture(m_sdlTexture);
    m_sdlUtilityTool.DestroySurface(m_sdlSurface);
    m_sdlUtilityTool.DestroyRenderer(m_sdlRenderer);
    m_sdlUtilityTool.DestroyWindow(m_sdlWindow);
}

void State::Render()
{
    SDL_UpdateTexture(m_sdlTexture, NULL, m_sdlSurface->pixels, m_sdlSurface->w * sizeof (Uint32));
    SDL_RenderClear(m_sdlRenderer);
    SDL_RenderCopy(m_sdlRenderer, m_sdlTexture, NULL, NULL);
    SDL_RenderPresent(m_sdlRenderer);
}

bool State::HasNextState() const
{
    return m_nextState;
}

StateCreationPackage State::GetNextStateCreationPackage()
{
    g_assert(m_nextState == true);
    return m_stateCreatePackage;
}

void State::ClearSurface()
{
    SDL_FillRect(m_sdlSurface, NULL, SDL_MapRGB(m_sdlSurface->format, 100, 100, 200));
}

void State::SetNextState(StateCreationPackage stateCreatePackage)
{
    m_nextState = true;
    m_stateCreatePackage = stateCreatePackage;
}

} // namespace Engine
} // namespace Heroes
