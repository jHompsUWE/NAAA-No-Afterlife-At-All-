#ifndef _TEXT_GO_2D_H_
#define _TEXT_GO_2D_H_

//=================================================================
//a Game Object 2D for displaying text
//=================================================================

#include "GameObject2D.h"
#include <vector>

class TextGO2D :public GameObject2D
{
public:
	TextGO2D(string _text);
	TextGO2D();

	void SetString(string _text);
	void SetString(string _text, Color _colour);
	void AddToString(string _text);
	void AddToString(string _text, Color _colour);
	string GetString();

	virtual void Tick(GameData* _GD);
	virtual void Draw(DrawData2D* _DD);

	//Position of the right edge of the string
	RECT t_boundaries;
	//Vector2 string_width;
	Vector2 n_string_position;

	float differenceX = 0.0f;
	float differenceY = 0.0f;

protected:


	vector<Color> colours;
	vector<string> strings;
};

#endif