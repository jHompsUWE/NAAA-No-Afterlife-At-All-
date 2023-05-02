#pragma once

#include "Manager.h"
#include "Listener.h"
#include "GameObject2D.h"
#include "DDSTextureLoader.h"

class CursorController : public GameObject2D, public Listener
{
public:
    CursorController(string _fileName, ID3D11Device* _device);
    ~CursorController() = default;

    ////////////////////////////////////////////////////////////
    /// \brief Called every cycle of the game loop.
    ///	\param _timer DeltaTime.
    ////////////////////////////////////////////////////////////
    void Tick(GameData* _game_data) override;

    void Draw(DrawData2D* _draw_data) override;

    ////////////////////////////////////////////////////////////
    /// \brief Interface function for concrete listeners to override. \n Allows listener derived classes to receive events from the EventManager.
    ///	\param event The event to be acted upon.
    ////////////////////////////////////////////////////////////
    void onEvent(const Event& _event) override;

private:
    Vector2 move_direction;
    float speed = 120;

    ID3D11ShaderResourceView* m_pTextureRV;
};

