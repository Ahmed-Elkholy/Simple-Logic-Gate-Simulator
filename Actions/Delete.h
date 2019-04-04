
#ifndef _DELETE_H
#define _DELETE_H
#include "Action.h"
#include "..\Components\Gate.h"
class Delete :
	public Action
{
private:

	int Cx, Cy;	//Center point of the gate
	Component**del;
	int delcnt;
public:
	Delete(ApplicationManager *pApp);
	virtual ~Delete(void);

	//Reads parameters required for action to execute
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();
};

#endif
