#ifndef _EDIT_H
#define _EDIT_H

#include "Action.h"
#include "..\Components\Connection.h"
class EditLabel:public Action
{
	string oldlabel;
	string newlabel;
	Component* pc;
private:
public:
	EditLabel(ApplicationManager *pApp);
	virtual ~EditLabel(void);

	//Reads parameters required for action to execute
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();


};







#endif
