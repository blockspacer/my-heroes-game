// Heroes Game
// Author: Samuel Hall
// Last Commented ? Needs to have all GameController code migrated here

#pragma once

#include <mutex>

namespace Heroes
{
namespace Engine
{
class StateEngine;
class SDLUtilityTool;

/*
 * This class should be the one place in the program that user input is recieved, if
 * not the desing is wrong. This class is not extendable and should be a singleton.
 */
class InputHandler final
{
public:

    // Returns that acive status of the InputHandler
    bool IsActive();

    // public functions for states to call
    bool GetRightBumberPressed();

    bool Start_Button();
    bool Select_Button();

    bool R_Button();
    bool RB_Button();
    bool L_Button();
    bool LB_Button();

    bool A_Button();
    bool B_Button();
    bool X_Button();
    bool Y_Button();

    bool Up_Button();
    bool Down_Button();
    bool Left_Button();
    bool Right_Button();


private:

    // only the state engine can create this class, this is to control the access and creation of the InputHandler
    friend class StateEngine;

    friend int ProcessInputFunction(void* inputHandler);

    void SetRightBumberPressed();

    // Constructor does not start the InputHandler (see Start)
    InputHandler(SDLUtilityTool& m_sdlUtilityTool);
    virtual ~InputHandler();

    // This function starts the thread that handles SDL input events
    void StartInputThread(const char* name);

    SDLUtilityTool& m_sdlUtilityTool;
    SDL_Thread* m_sdlInputThread { 0 };

    bool m_active { true };

    // should prolly have mutexs for each type of input
    //std::mutex m_mutex;

    // TODO - figure out the inputs are handled
    // key presses, holds and old input should be removed

    bool m_rightBumberPressed { false };
    bool m_rightBumberReleased { false };
    bool m_rightBumberHold { false };

};

} // namespace Engine
} // namespace Heroes
