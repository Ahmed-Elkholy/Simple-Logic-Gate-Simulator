#ifndef _TRUTHTABLE_H
#define _TRUTHTABLE_H

#include "action.h"
#include "..\Components\AND2.h"
#include<fstream>
class TruthTable :	public Action
{
private:
	//Parameters for rectangular area to be occupied by the gate
	int Cx, Cy;	//Center point of the gate
	int x1, y1, x2, y2;	//Two corners of the rectangluar area
	ofstream Outputfile;
public:
	TruthTable(ApplicationManager *pApp);
	virtual ~TruthTable(void);

	//Reads parameters required for action to execute
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();


};

#endif