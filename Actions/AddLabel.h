#ifndef _ADD_LABEL_H
#define _ADD_LABEL_H

#include "Action.h"
#include "..\Components\Connection.h"
class AddLabel:public Action
{
	string oldlabel;
	string newlabel;
	Component* pc;
private:
public:
	AddLabel(ApplicationManager *pApp);
	virtual ~AddLabel(void);

	//Reads parameters required for action to execute
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();


};







#endif
