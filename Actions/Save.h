#ifndef _SAVE_H
#define _SAVE_H

#include "action.h"
#include "..\Components\AND2.h"
#include<fstream>
using namespace std;
class Save1 :	public Action
{
private:
	//Parameters for rectangular area to be occupied by the gate
	int Cx, Cy;	//Center point of the gate
	int x1, y1, x2, y2;	//Two corners of the rectangluar area
	ofstream Outputfile;
public:
	Save1(ApplicationManager *pApp);
	virtual ~Save1(void);

	//Reads parameters required for action to execute
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();


};

#endif