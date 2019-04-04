#ifndef _PROBE_H
#define _PROBE_H

#include "Action.h"
#include "..\Components\Connection.h"
class Probe:public Action
{
	
	private:
		//Parameters for rectangular area to be occupied by the gate
		int Cx, Cy;	//Center point of the gate
		Connection *pC;
	public:
		Probe(ApplicationManager *pApp);
		virtual ~Probe(void);

		//Reads parameters required for action to execute
		virtual void ReadActionParameters();
		//Execute action (code depends on action type)
		virtual void Execute();

		virtual void Undo();
		virtual void Redo();


};
#endif

