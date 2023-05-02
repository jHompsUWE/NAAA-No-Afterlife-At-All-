#include "pch.h"
#include "CursorController.h"
#include "debug.h"
#include "DrawData2D.h"
#include "DDSTextureLoader.h"
#include "GameManager.h"
#include "Helper.h"

CursorController::CursorController(string _fileName, ID3D11Device* _device)
{
    string fullfilename = "../Assets/" + _fileName + ".dds";
    HRESULT hr = CreateDDSTextureFromFile(_device, Helper::charToWChar(fullfilename.c_str()), nullptr, &m_pTextureRV);
    if (hr != S_OK)
    {
        CreateDDSTextureFromFile(_device, L"../Assets/white.dds", nullptr, &m_pTextureRV);
        cout << "Missing Texture : " << _fileName << endl;
    }
    
    SetScale(Vector2{0.06,0.06});
    SetPos(400, 300);
}

void CursorController::Tick(GameData* _game_data)
{
    if (abs(move_direction.x) + abs(move_direction.y) != 0.0f)
    {
        SetPos(GetPos().x + (move_direction.x * speed * _game_data->m_dt), GetPos().y + (move_direction.y * speed * _game_data->m_dt));

        Event event{};
        event.type = EventType::CURSOR_MOVED;
        event.payload.cursor_data.x = GetPos().x;
        event.payload.cursor_data.y = GetPos().y;
        event.priority = 1;
        
        GameManager::get()->getEventManager()->triggerEvent(std::make_shared<Event>(event));
    }
}

void CursorController::Draw(DrawData2D* _draw_data)
{
    _draw_data->m_Sprites->Draw(m_pTextureRV, m_pos, nullptr, m_colour, m_rotation, m_origin, m_scale, SpriteEffects_None);
}


void CursorController::onEvent(const Event& _event)
{
    switch (_event.type)
    {
        case EventType::MOVE_CURSOR:
        {                
            move_direction = Vector2{_event.payload.input_vector2_data.x, _event.payload.input_vector2_data.y};

            Event event{};
            event.type = EventType::CURSOR_MOVED;
            event.payload.cursor_data.x = GetPos().x;
            event.payload.cursor_data.y = GetPos().y;
            event.payload.cursor_data.selected = false;
            event.priority = 1;
            
            GameManager::get()->getEventManager()->triggerEvent(std::make_shared<Event>(event));
            break;
        }
        case EventType::SELECT_CURSOR:
        {
            Event event{};
            event.type = EventType::CURSOR_SELECTED;
            event.payload.cursor_data.x = GetPos().x;
            event.payload.cursor_data.y = GetPos().y;
            event.payload.cursor_data.selected = _event.payload.input_button_data.down;
            event.priority = 1;
                
            GameManager::get()->getEventManager()->triggerEvent(std::make_shared<Event>(event));
        }
        default: ;
    }    
}
