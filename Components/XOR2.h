#ifndef _XOR2_H
#define _XOR2_H

/*
Class XOR2
-----------
represent the 2-input XOR gate
*/

#include "Gate.h"

class XOR2 :public Gate
{
public:
	XOR2(int r_FanOut);
	XOR2(const GraphicsInfo &r_GfxInfo, int r_FanOut);
	virtual void Operate();	//Calculates the output of the XOR gate
	virtual void Draw(Output* pOut);	//Draws 2-input gate

	virtual int GetOutPinStatus();	//returns status of outputpin if LED, return -1
	virtual int GetInputPinStatus(int n);	//returns status of Inputpin # n if SWITCH, return -1

	virtual void setInputPinStatus(int n, STATUS s);	//set status of Inputpin # n, to be used by connection class.

	virtual InputPin* getinpin(int n) { return m_InputPins + n - 1; }
	virtual OutputPin*  getoutpin() { return &m_OutputPin; }
	virtual bool CheckIfInpin(int &x, int &y, int&);
	virtual void GetinputPinCoordinates(int inputnum, int &x, int &y);
	virtual void Save(ofstream&);

	virtual Component* Copy();
};

#endif
