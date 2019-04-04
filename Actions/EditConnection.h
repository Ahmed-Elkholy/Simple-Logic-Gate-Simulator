#ifndef _EDIT_Connection_H
#define _EDIT_Connection_H

#include "Action.h"
#include "..\Components\Connection.h"
class EditConnection :public Action
{
	
	private:
		//Parameters for rectangular area to be occupied by the gate
		//int Cx, Cy;	//Center point of the gate
		int x1, y1, x2, y2;	//Two corners of the rectangluar area
		OutputPin* outputPtr;
		InputPin *inputPtr;
		Component *pSource;
		Component *pDest;
		Connection *pC;
		Component *OrigOutputcomp;
		OutputPin *OriginalOutput;
		InputPin *OriginalInput;
		GraphicsInfo OrigGInfo;
		int newinputnum;
		int oldinputnum;
	public:
		EditConnection(ApplicationManager *pApp);
		virtual ~EditConnection(void);

		//Reads parameters required for action to execute
		virtual void ReadActionParameters();
		//Execute action (code depends on action type)
		virtual void Execute();

		virtual void Undo();
		virtual void Redo();


};
#endif

