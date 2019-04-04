#ifndef _NOT_H
#define _NOT_H

/*
Class NOT
-----------
represent the NOT gate
*/

#include "Gate.h"

class NOT :public Gate
{
public:
	NOT(const GraphicsInfo &r_GfxInfo, int r_FanOut);
	NOT(int r_FanOut);
	virtual void Operate();	//Calculates the output of the NOT gate
	virtual void Draw(Output* pOut);	//Draws NOT gate

	virtual int GetOutPinStatus();	//returns status of outputpin if LED, return -1
	virtual int GetInputPinStatus(int n);	//returns status of Inputpin # n if SWITCH, return -1

	virtual void setInputPinStatus(int n, STATUS s);	//set status of Inputpin # n, to be used by connection class.


	virtual InputPin* getinpin(int n) { return m_InputPins + n - 1; }
	virtual OutputPin*  getoutpin() { return &m_OutputPin; }
	virtual bool CheckIfInpin(int &x, int &y, int&);
	//virtual GraphicsInfo getgrap() { return m_GfxInfo; }
	virtual void GetinputPinCoordinates(int inputnum, int &x, int &y);
	virtual void Save(ofstream&);

	virtual Component* Copy();
};

#endif
