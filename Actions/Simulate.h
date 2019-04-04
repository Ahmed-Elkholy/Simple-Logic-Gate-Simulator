#ifndef _SIM_H
#define _SIM_H

#include "Action.h"
#include "..\Components\Connection.h"
class Simulate1:public Action
{
	string label;
	int Cx;
	int Cy;
public:
	Simulate1(ApplicationManager *pApp);
	virtual ~Simulate1(void);

	//Reads parameters required for action to execute
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();


};







#endif
