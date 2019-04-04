#ifndef _SwitchToDSN_H
#define _SwitchToDSN_H

#include "Action.h"
#include "..\Components\Connection.h"
class SwitchToDSN :public Action
{
	bool validate;
public:
	SwitchToDSN(ApplicationManager *pApp);
	virtual ~SwitchToDSN(void);

	//Reads parameters required for action to execute
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();
	bool getStatus() const;
	virtual void Undo();
	virtual void Redo();


};







#endif
