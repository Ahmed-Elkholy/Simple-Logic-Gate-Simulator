#ifndef _BUFF_H
#define _BUFF_H

/*
Class BUFFER
-----------
represent the BUFFER gate
*/

#include "Gate.h"

class BUFF :public Gate
{
public:
	BUFF(const GraphicsInfo &r_GfxInfo, int r_FanOut);
	BUFF(int r_FanOut);
	virtual void Operate();	//Delays signal
	virtual void Draw(Output* pOut);	//Draws BUFFER gate

	virtual int GetOutPinStatus();	//returns status of outputpin if LED, return -1
	virtual int GetInputPinStatus(int n);	//returns status of Inputpin # n if SWITCH, return -1

	virtual void setInputPinStatus(int n, STATUS s);	//set status of Inputpin # n, to be used by connection class.


	virtual InputPin* getinpin(int n) { return m_InputPins + n - 1; }
	virtual OutputPin*  getoutpin() { return &m_OutputPin; }
	virtual bool CheckIfInpin(int &x, int &y, int&);
	virtual void GetinputPinCoordinates(int inputnum, int &x, int &y);
	//virtual GraphicsInfo getgrap() { return m_GfxInfo; }
	virtual void Save(ofstream&);
	virtual Component* Copy();
};

#endif

