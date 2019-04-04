#pragma once
#include "component.h"
#include "InputPin.h"
#include "OutputPin.h"
#include <vector>
using namespace std;
class Connection :	public Component
{
	//Component*	SrcCmpnt;	//Connection source component
	//Component*	DstCmpnt;	//Connection Destination component
	int	DstPinNum;		//The Input pin to which this connection is linked
	OutputPin* SrcPin;	//The Source pin of this connection (an output pin of certain Component)
	InputPin* DstPin;	//The Destination pin of this connection (an input pin of certain Component)
	vector<GraphicsInfo> Lines;
public:
	//static int count;
	//Connection(const GraphicsInfo &r_GfxInfo, Component *pS=NULL,Component *pD=NULL, int Pin=0);
	Connection(const GraphicsInfo &r_GfxInfo, OutputPin *pSrcPin,InputPin *pDstPin);

	virtual void Operate() ;	//Calculates the output according to the inputs
	virtual void Draw(Output* pOut);	//for each component to Draw itself

	
	void setSourcePin(OutputPin *pSrcPin);
	void setDestPin(InputPin *pDstPin);
	OutputPin* getSourcePin();
	InputPin* getDestPin();
	virtual bool CheckIfOutpin(int &x, int &y);
	virtual bool CheckIfInpin(int &x, int & y, int &inputnum);
	bool CheckPins();
	virtual int GetOutPinStatus();	//returns status of outputpin if LED, return -1
	virtual int GetInputPinStatus(int n);	//returns status of Inputpin # n if SWITCH, return -1


	void load(ifstream& Inputfile);
	virtual void setInputPinStatus(int n, STATUS s);	//set status of Inputpin # n, to be used by connection class.
	virtual InputPin* getinpin(int n) {  return getDestPin(); } //mlhash lazma hna
	virtual OutputPin*  getoutpin() { return getSourcePin(); }
	virtual GraphicsInfo getgrap() { return m_GfxInfo; }
	virtual void SetGraphics(int x, int y, bool type = false);
	virtual void SetGraphics(GraphicsInfo gfx);
	bool CheckIfselected(int x, int y, bool& selected);
	void SetInputNum(int n);
	int GetInputNum() const;
	void Save(ofstream & Outputfile);
	virtual void GetinputPinCoordinates(int inputnum,int &x,int &y);
	virtual int GetID() const;
	virtual void SetID(int r_ID);
	virtual Component* Copy();

};
