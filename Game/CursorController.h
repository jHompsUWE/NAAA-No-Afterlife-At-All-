#pragma once

#include "Manager.h"
#include "Listener.h"
#include "ImageGO2D.h"

class CursorController : public ImageGO2D, public Listener
{
public:
    CursorController(string _fileName, ID3D11Device* _GD);
    ~CursorController() = default;

    ////////////////////////////////////////////////////////////
    /// \brief Called every cycle of the game loop.
    ///	\param _timer DeltaTime.
    ////////////////////////////////////////////////////////////
    void update(GameData& _game_data);

    ////////////////////////////////////////////////////////////
    /// \brief Interface function for concrete listeners to override. \n Allows listener derived classes to receive events from the EventManager.
    ///	\param event The event to be acted upon.
    ////////////////////////////////////////////////////////////
    void onEvent(const Event& event) override;

private:
    Vector2 move_direction;
};

