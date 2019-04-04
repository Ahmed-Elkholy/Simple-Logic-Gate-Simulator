#ifndef _MOVE_H
#define _MOVE_H
#include "Action.h"
#include"..\Components\Component.h"
class Move :public Action
{
private:

	int Cx, Cy;	//Center point of the gate
	int originx, originy;//, lastx, lasty;
	Component** sel;
	int selcnt;
	int * cdif;
	int* coldx;
	int* coldy;
	int* newx;
	int * newy;
public:
	Move(ApplicationManager *pApp);
	virtual ~Move(void);
	void setundo(Component** c, int * dif, int cnt, int * oldx, int* oldy);
	//Reads parameters required for action to execute
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();
	void Movegate(Component*, int, int);
};
#endif
