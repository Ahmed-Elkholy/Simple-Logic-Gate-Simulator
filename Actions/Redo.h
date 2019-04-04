#ifndef _REDO_H_
#define _REDO_H_
#include"Action.h"
#include "../Components/Gate.h"
class Redo :public Action
{
private:

	int Cx, Cy;//Center point of the gate
	Component*	pA;
public:
	Redo(ApplicationManager *pApp);
	~Redo(void);

	//Reads parameters required for action to execute
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();

	//virtual void Undo();
	//virtual void Redo();

	

};

#endif