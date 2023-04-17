#include "pch.h"
#include "CursorController.h"

#include "GameManager.h"

CursorController::CursorController(string _fileName, ID3D11Device* _GD) : ImageGO2D(_fileName, _GD)
{
    SetScale(Vector2{100,100});
}
void CursorController::update(GameData& _game_data)
{
    if (abs(move_direction.x) + abs(move_direction.y) != 0.0f)
    {
        SetPos(GetPos().x + (move_direction.x * _game_data.m_dt), GetPos().y + (move_direction.y * _game_data.m_dt));

        Event event{};
        event.type = EventType::CURSOR_MOVED;
        event.payload.cursor_data.x = GetPos().x;
        event.payload.cursor_data.y = GetPos().y;
        
        GameManager::get()->getEventManager()->triggerEvent(std::make_shared<Event>(event));
    }
}

void CursorController::onEvent(const Event& event)
{
    if (event.type == EventType::MOVE_CURSOR)
    {
        move_direction = Vector2{event.payload.input_vector2_data.x, event.payload.input_vector2_data.y};
        std::cout << move_direction.x << " : " << move_direction.y;
    }
}
