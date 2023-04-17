#pragma once

#include "Manager.h"
#include "Listener.h"

class CursorController : public Manager, public Listener
{
public:
    CursorController() = default;
    ~CursorController() = default;
    
    ////////////////////////////////////////////////////////////
    /// \brief Is called when the program initializes.
    ////////////////////////////////////////////////////////////
     void awake(GameData& _game_data) override;

    ////////////////////////////////////////////////////////////
    /// \brief Called every cycle of the game loop.
    ///	\param _timer DeltaTime.
    ////////////////////////////////////////////////////////////
    void update(GameData& _game_data) override;

    ////////////////////////////////////////////////////////////
    /// \brief Interface function for concrete listeners to override. \n Allows listener derived classes to receive events from the EventManager.
    ///	\param event The event to be acted upon.
    ////////////////////////////////////////////////////////////
    void onEvent(const Event& event) override;

    ////////////////////////////////////////////////////////////
    /// \brief Called every cycle of the game loop, but after update.
    ///	\param _m_DD DrawData pointer.
    ////////////////////////////////////////////////////////////
    void render(DrawData* m_DD) override;

private:
    
};

