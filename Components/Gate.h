#ifndef _GATE_H
#define _GATE_H

/*
  Class Gate
  -----------
  - Base class for all types of gates
  - Each gate has n inputs pins and one output pin
*/


#include "InputPin.h"
#include "OutputPin.h"
#include "Component.h"
class Gate:public Component
{
protected:
	InputPin* m_InputPins;	//Array of input pins of the Gate
	OutputPin m_OutputPin;	//The Gate output pin
	int m_Inputs;   //No. of input pins of that Gate.
	virtual bool CheckIfInputpin(int &x, int &y,int delta);
	int ID;
public:
	Gate(int r_Inputs, int r_FanOut);
	virtual InputPin* getinpin(int n) = 0;
	virtual OutputPin*  getoutpin() = 0;
	virtual bool CheckIfOutpin(int &x, int &y);
	virtual bool CheckIfInpin(int &x, int &y, int &inputnum)=0;
	virtual bool CheckPins();
	virtual GraphicsInfo getgrap() { return m_GfxInfo; }
	bool CheckIfselected(int x,int y,bool& selected);
	virtual void load(ifstream& input);
	virtual void SetID(int r_ID);
	void Save(ofstream &OutPut)=0;
	int GetID() const;
	virtual Component* Copy()=0;
};

#endif
