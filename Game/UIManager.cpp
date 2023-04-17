#include "pch.h"
#include "UIManager.h"
#include "GameManager.h"

/// <summary>
/// Constructer initalises the Ui Remote, the 6 toggleable view windows, and the 3 types of building tier selection windows
/// </summary>
/// <param name="_GD"></param>
UIManager::UIManager(ID3D11Device* _ID, GameData* _GD) 
{
    m_ID = _ID;
    m_GD = _GD;
}

UIManager::~UIManager()
{

}

void UIManager::awake()
{
    remote = new UIRemote(m_ID);
    remote->SetPos(100, 230);
    remote->SetButtonBounds();

    viewWindows[0] = new WindowDraggable(m_ID, "Planetview", false, Colors::LightSkyBlue);
    viewWindows[0]->SetPos(300, 100);

    viewWindows[1] = new WindowDraggable(m_ID, "Graphview", false, Colors::LightBlue);
    viewWindows[1]->SetPos(600, 100);

    viewWindows[2] = new WindowDraggable(m_ID, "Soulview", false, Colors::LightGreen);
    viewWindows[2]->SetPos(300, 200);

    viewWindows[3] = new WindowDraggable(m_ID, "Macro\nManager", false, Colors::LightYellow);
    viewWindows[3]->SetPos(600, 200);

    viewWindows[4] = new WindowDraggable(m_ID, "Mapview", false, Colors::LightPink);
    viewWindows[4]->SetPos(300, 300);

    viewWindows[5] = new WindowDraggable(m_ID, "MicroView", false, Colors::LightCoral);
    viewWindows[5]->SetPos(300, 400);

    for (int i = 0; i < 6; i++)
    {
        viewWindows[i]->SetTextPos();
    }


    for (int i = 0; i < 3; i++)
    {
        buildWindows[i] = new BuildingWindow(m_ID, i + 3);
        buildWindows[i]->SetPos(300, 400);
        //buildWindows[i]->SetButtonBounds();
    }

    remote->SetButtonToggle(26, viewWindows[0]);
    remote->SetButtonToggle(27, viewWindows[1]);
    remote->SetButtonToggle(28, viewWindows[2]);
    remote->SetButtonToggle(29, viewWindows[3]);
    remote->SetButtonToggle(30, viewWindows[4]);
    remote->SetButtonToggle(32, viewWindows[5]);
}

/// <summary>
/// 
/// </summary>
/// <param name="_game_data"></param>
void UIManager::update(GameData& _game_data)
{
    remote->Tick(m_GD);

    for (int j = 0; j < 6; j++)
    {
        viewWindows[j]->Tick(m_GD);
    }
}

void UIManager::Draw(DrawData2D* _DD)
{
    remote->Draw(_DD);

    for (int j = 0; j < 6; j++)
    {
        viewWindows[j]->Draw(_DD);
    }

    for (int i = 0; i < 3; i++)
    {
        buildWindows[i]->Draw(_DD);
    }

}