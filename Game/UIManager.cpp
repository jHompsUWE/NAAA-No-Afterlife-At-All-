#include "pch.h"
#include "UIManager.h"


/// <summary>
/// Constructer initalises the Ui Remote, the 6 toggleable view windows, and the 3 types of building tier selection windows
/// </summary>
/// <param name="_GD"></param>
UIManager::UIManager(ID3D11Device* _GD)
{
	remote = new UIRemote(_GD);
    remote->SetPos(100, 230);
    remote->SetButtonBounds();

    viewWindows[0] = new Window("bug_test", _GD, "Planetview", false, Colors::LightSkyBlue);
    viewWindows[0]->SetPos(300, 100);

    viewWindows[1] = new Window("bug_test", _GD, "Graphview", false, Colors::LightBlue);
    viewWindows[1]->SetPos(600, 100);

    viewWindows[2] = new Window("bug_test", _GD, "Soulview", false, Colors::LightGreen);
    viewWindows[2]->SetPos(300, 200);

    viewWindows[3] = new Window("bug_test", _GD, "Macro\nManager", false, Colors::LightYellow);
    viewWindows[3]->SetPos(600, 200);

    viewWindows[4] = new Window("bug_test", _GD, "Mapview", false, Colors::LightPink);
    viewWindows[4]->SetPos(300, 300);

    viewWindows[5] = new Window("bug_test", _GD, "MicroView", false, Colors::LightCoral);
    viewWindows[5]->SetPos(300, 400);


    for (int j = 0; j < 6; j++)
    {
        viewWindows[j]->SetTextPos();
    }

	for (int i = 0; i < 3; i++)
	{
        buildWindows[i] = new BuildingWindow(_GD, i + 3);
        buildWindows[i]->SetPos(300, 400);
        buildWindows[i]->SetButtonBounds();
	}

    remote->SetButtonToggle(26, viewWindows[0]);
    remote->SetButtonToggle(27, viewWindows[1]);
    remote->SetButtonToggle(28, viewWindows[2]);
    remote->SetButtonToggle(29, viewWindows[3]);
    remote->SetButtonToggle(30, viewWindows[4]);
    remote->SetButtonToggle(32, viewWindows[5]);

    remote->SetButtonToggle(8, buildWindows[1]);
    remote->SetButtonToggle(10, buildWindows[0]);
    remote->SetButtonToggle(12, buildWindows[1]);

    remote->SetButtonToggle(13, buildWindows[0]);
    remote->SetButtonToggle(14, buildWindows[0]);
    remote->SetButtonToggle(15, buildWindows[0]);

    remote->SetButtonToggle(16, buildWindows[2]);
    remote->SetButtonToggle(17, buildWindows[0]);
    remote->SetButtonToggle(18, buildWindows[0]);


}

/// <summary>
/// 
/// </summary>
/// <param name="_game_data"></param>
void UIManager::update(GameData& _game_data)
{
   
}

void UIManager::Draw(DrawData2D* _DD)
{

}