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
    delete(optBar);
    optBar = nullptr;

    delete(remote);
    remote = nullptr;

    delete(optBar);
    optBar = nullptr;

    for (int i = 0; i < 6; i++)
    {
        delete(viewWindows[i]);
        viewWindows[i] = nullptr;
    }

    for (int i = 0; i < 3; i++)
    {
        delete(buildWindows[i]);
        buildWindows[i] = nullptr;
    }
}

void UIManager::awake(GameData& _game_data)
{
    optBar = new OptionBar(m_ID);
    optBar->SetPos(400, 5);

    remote = new UIRemote(m_ID);
    remote->SetPos(100, 270);
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
        buildWindows[i]->SetButtonBounds();
    }

    //WindowToggles
    //View Windows
    remote->SetButtonToggle(0, viewWindows[0]);
    remote->SetButtonToggle(1, viewWindows[1]);
    remote->SetButtonToggle(2, viewWindows[2]);
    remote->SetButtonToggle(3, viewWindows[3]);
    remote->SetButtonToggle(4, viewWindows[4]);
    remote->SetButtonToggle(6, viewWindows[5]);

    //Building Windows
    remote->SetButtonToggle(0, buildWindows[1]);
    remote->SetButtonToggle(1, buildWindows[0]);
    remote->SetButtonToggle(2, buildWindows[1]);
    remote->SetButtonToggle(3, buildWindows[0]);
    remote->SetButtonToggle(4, buildWindows[0]);
    remote->SetButtonToggle(5, buildWindows[0]);
    remote->SetButtonToggle(6, buildWindows[2]);
    remote->SetButtonToggle(7, buildWindows[0]);
    remote->SetButtonToggle(8, buildWindows[0]);
}

/// <summary>
/// 
/// </summary>
/// <param name="_game_data"></param>
void UIManager::update(GameData& _game_data)
{
    bool buildingOpen = false;
    remote->buildingWindowOpen = false;

    for (int i = 0; i < 3; i++)
    {
        if (buildWindows[i]->renderable)
        {
            buildingOpen = true;
        }

        buildWindows[i]->Tick(m_GD);
    }

    if (buildingOpen)
    {
        remote->buildingWindowOpen = true;
        remote->dragged = false;
    }
    
    remote->Tick(m_GD);

    optBar->Tick(m_GD);
    
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

   optBar->Draw(_DD);
}