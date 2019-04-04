#ifndef _UNDO_H_
#define _UNDO_H_
#include "Action.h"
#include "../Components/Gate.h"

class Undo :public Action
{
private:

	int Cx, Cy;//Center point of the gate
	Component*	pA;
	bool CheckPasted;
public:
	Undo(ApplicationManager *pApp);
	~Undo(void);

	//Reads parameters required for action to execute
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();

	//virtual void Undo();
	//virtual void Redo();

	bool checkPasted();

};

#endif