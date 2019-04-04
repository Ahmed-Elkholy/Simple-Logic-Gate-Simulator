#pragma once
#include "Gate.h"
class SWITCH :public Component
{
	bool Opened;
	OutputPin m_OutputPin;
	int ID;
public:

	SWITCH(const GraphicsInfo &r_GfxInfo, int r_FanOut);
	SWITCH(int r_FanOut);
	virtual void Operate();	//Calculates the output of the switch
	virtual void Draw(Output* pOut);	//Draws switch

	virtual int GetOutPinStatus();	//returns status of outputpin if LED, return -1
	virtual int GetInputPinStatus(int n);	//returns status of Inputpin # n if SWITCH, return -1

	virtual void setInputPinStatus(int n, STATUS s);	//set status of Inputpin # n, to be used by connection class.
	void SetStatus(bool m_Opened);
	bool GetStatus();  //true if opened
	virtual bool CheckIfOutpin(int &x, int &y);
	virtual bool CheckIfInpin(int& x, int & y, int &inputnum);
	bool CheckIfselected(int x, int y, bool& selected);
	virtual InputPin* getinpin(int n) { return NULL; }
	virtual OutputPin*  getoutpin() { return &m_OutputPin; }
	virtual GraphicsInfo getgrap() { return m_GfxInfo; }
	virtual bool CheckPins();
	virtual void GetinputPinCoordinates(int inputnum, int &x, int &y);
	void SetID(int r_ID);
	void load(ifstream& Inputfile);
	int GetID() const;
	virtual void Save(ofstream&);
	virtual Component* Copy();
};


