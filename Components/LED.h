#pragma once
#include "Component.h"
class LED :public Component
{
	InputPin m_InputPin;
	bool Status;
	int ID;
public:
	
	LED(const GraphicsInfo &r_GfxInfo, int r_FanOut);
	LED(int r_FanOut);
	virtual void Operate();	//Calculates the output of the led gate
	virtual void Draw(Output* pOut);	//Draws led

	virtual int GetOutPinStatus();	//returns status of outputpin if LED, return -1
	virtual int GetInputPinStatus(int n);	//returns status of Inputpin # n if SWITCH, return -1

	virtual void setInputPinStatus(int n, STATUS s);
	virtual InputPin* getinpin(int n);
	virtual OutputPin*  getoutpin();
	virtual bool CheckPins();
	bool CheckIfselected(int x, int y, bool& selected);
	int GetStatus() const;
	virtual GraphicsInfo getgrap();	//set status of Inputpin # n, to be used by connection class.
	int GetID() const;
	virtual void GetinputPinCoordinates(int inputnum, int &x, int &y);
	virtual void Save(ofstream&);
	virtual bool CheckIfOutpin(int &x, int &y);
	virtual bool CheckIfInpin(int &x, int & y, int &inputnum);
	void load(ifstream& Inputfile);
	void SetID(int r_ID);
	virtual Component* Copy();
	~LED();
};

