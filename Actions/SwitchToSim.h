#ifndef _SWITCHTOSIM_H
#define _SWITCHTOSIM_H

#include "Action.h"
#include "..\Components\Connection.h"
class SwitchToSim:public Action
{
	bool validate;
public:
	SwitchToSim(ApplicationManager *pApp);
	virtual ~SwitchToSim(void);

	//Reads parameters required for action to execute
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();
	bool getStatus() const;
	virtual void Undo();
	virtual void Redo();


};







#endif
