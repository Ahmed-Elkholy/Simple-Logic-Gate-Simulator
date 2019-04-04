#ifndef _VALIDATE_H
#define _VALIDATE_H

#include "Action.h"
#include "..\Components\Connection.h"
class Validate:public Action
{
	bool validate;
public:
	Validate(ApplicationManager *pApp);
	virtual ~Validate(void);

	//Reads parameters required for action to execute
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();
	bool getStatus() const;
	virtual void Undo();
	virtual void Redo();


};







#endif
