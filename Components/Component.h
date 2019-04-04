#ifndef _COMPONENT_H
#define _COMPONENT_H

#include "..\Defs.h"
#include "..\GUI\Output.h"
#include"InputPin.h"
#include"OutputPin.h"
#include<fstream>
using namespace std;
#include <vector>
//Base class for classes Gate, Switch, and LED.
class Component
{
private:
	string m_Label;
protected:
	GraphicsInfo m_GfxInfo;	//The parameters required to draw a component
	bool m_selected;
	vector<Component*>nextComp;
	int countNextComp;
	int level;
	ComponentType type;
	static int count;
	bool visited;
public:
	Component(const GraphicsInfo &r_GfxInfo);
	virtual void Operate() = 0;	//Calculates the output according to the inputs
	virtual void Draw(Output* pOut) = 0;	//for each component to Draw itself
	virtual void Save(ofstream &)=0;
	
	virtual int GetOutPinStatus()=0;	//returns status of outputpin if LED, return -1
	virtual int GetInputPinStatus(int n)=0;	//returns status of Inputpin # n if SWITCH, return -1
	virtual bool CheckPins()=0;
	virtual void setInputPinStatus(int n, STATUS s)=0;	//set status of Inputpin # n, to be used by connection class.
	virtual InputPin* getinpin(int n) = 0;
	virtual OutputPin*  getoutpin() = 0;
	virtual GraphicsInfo getgrap() = 0;
	virtual void SetGraphics(int x, int y, bool type = false);
	void SetSelectionStat(bool selected);
	bool GetSelectedstat();
	void SetLabel(string s);
	virtual bool CheckIfselected(int x, int y, bool& selected) = 0;
	string GetLabel() const;
	void SetVisited(bool m_visited);
	bool GetVisited() const;
	int GetLevel() const;
	void SetLevel(int L);
	void SetNextComp(Component *);
	Component * GetNextComp(int count);
	void DeleteNextComp(Component* pc);
	virtual int GetID() const=0;
	virtual void SetID(int r_ID) = 0;
	virtual bool CheckIfOutpin(int &x, int &y) = 0;
	virtual bool CheckIfInpin(int &x,int & y,int &inputnum) = 0;
	virtual void GetinputPinCoordinates(int inputnum,int &x,int &y)=0;
	virtual void load(ifstream& input) = 0;
	virtual Component* Copy()=0;
	Component();	
	//Destructor must be virtual
	virtual ~Component();
};

#endif
