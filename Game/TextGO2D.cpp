#include "pch.h"
#include "TextGO2D.h"
#include "DrawData2D.h"
#include "helper.h"
#include <iostream>

TextGO2D::TextGO2D(string _text)
{
	strings.push_back(_text);
	colours.push_back(m_colour);
}

TextGO2D::TextGO2D()
{
}


// -- Set String --
void TextGO2D::SetString(string _text)
{
	strings.clear();
	colours.clear();
	strings.push_back(_text);
	colours.push_back(m_colour);
}

void TextGO2D::SetString(string _text, Color _colour)
{
	strings.clear();
	colours.clear();
	strings.push_back(_text);
	colours.push_back(_colour);
}

// -- Add to string --

void TextGO2D::AddToString(string _text)
{
	strings.push_back(_text);
}

void TextGO2D::AddToString(string _text, Color _colour)
{
	strings.push_back(_text);
	colours.push_back(_colour);
}

string TextGO2D::GetString()
{
	string m_text = "";
	for (int i = 0; i < strings.size(); i++)
	{
		m_text += strings[i];
	}
	return m_text;
}

void TextGO2D::Tick(GameData* _GD)
{

}


void TextGO2D::Draw(DrawData2D* _DD)
{


	if (colours.size() == 1)
	{
		//right click and "Go to Defintion/Declaration" to see other version of this in DXTK
		_DD->m_Font->DrawString(_DD->m_Sprites.get(), Helper::charToWChar(strings[0].c_str()), m_pos, m_colour, m_rotation, m_origin, m_scale);
	}
	else
	{
		t_boundaries = { lroundf(m_pos.x), lroundf(m_pos.y), 0, 0 };
		n_string_position = Vector2(m_pos.x + (t_boundaries.right * m_scale.x), m_pos.y);
		std::string curr_full_string = "";
		for (int i = 0; i < strings.size(); ++i)
		{
			_DD->m_Font->DrawString(_DD->m_Sprites.get(), Helper::charToWChar(strings[i].c_str()), n_string_position, colours[i], m_rotation, m_origin, m_scale);
			curr_full_string += strings[i];
			t_boundaries = _DD->m_Font->MeasureDrawBounds(Helper::charToWChar(curr_full_string.c_str()), XMFLOAT2(0.f, 0.f), false);
			n_string_position = Vector2(m_pos.x + (t_boundaries.right * m_scale.x), m_pos.y);

		}
	}
}