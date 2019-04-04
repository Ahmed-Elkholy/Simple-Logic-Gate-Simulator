#pragma once

#include "..\CMUgraphicsLib\CMUgraphics.h"
#include "UI_Info.h"

class Output;
class Input		//The application manager should have a pointer to this class
{
private:
	window *pWind;	//Pointer to the Graphics Window

public:
	Input(window*);
	void GetPointClicked(int &, int &);	//Get coordinate where user clicks
	clicktype GetMouseType(int &x, int &y);
	void GetCurrentClick(int &x, int &y);
	string GetString(Output*);		//Returns a string entered by the user
	string EditString(Output*,string s);
	ActionType GetUserAction() const; //Reads the user click and maps it to an action
	void CheckCoordinates(int &x, int &y, Output * pOut,int type=0);
	~Input();
};
