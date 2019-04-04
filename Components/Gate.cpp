#include "Gate.h"
#include<fstream>
using namespace std;
//Gate Constructor
//Parameters:
//r_Inputs: no. of gate's input pins
//r_FanOut: Fan out of the gate's output pin
Gate::Gate(int r_Inputs, int r_FanOut):m_OutputPin(r_FanOut),ID(count+1)
{
	//Allocate number of input pins (equals r_Inputs)
	count++;
	m_InputPins = new InputPin[r_Inputs];
	m_Inputs = r_Inputs;	//set no. of inputs of that gate
	m_selected = false;
	countNextComp=0;
	level=-1;
	//Associate all input pins to this gate
	for(int i=0; i<m_Inputs; i++)
		m_InputPins[i].setComponent(this);
	m_OutputPin.SetCompID(ID);
}
bool Gate::CheckIfOutpin(int &x, int &y)
{
	int xOut = m_GfxInfo.x1 + UI.AND2_Width - 3;
	int yOut = m_GfxInfo.y1 + 24;
	int diffx = x - xOut;
	if (diffx < 0) diffx = -diffx;
	int diffy = y - yOut;
	if (diffx < 0) diffy = -diffy;
	if (diffx < 5 && diffy < 5)
	{
		x = xOut;
		y = yOut;
		return true;
	}
	return false;
}
bool Gate::CheckIfInputpin(int &x, int &y,int deltay)
{
	int xIn1 = m_GfxInfo.x1;
	int yIn1 = m_GfxInfo.y1 + deltay;
	int diffx = x - xIn1;
	if (diffx < 0) diffx = -diffx;
	int diffy = y - yIn1;
	if (diffy < 0) diffy = -diffy;
	if (diffx <5 && diffy<5)
	{
		 x=xIn1;
		 y=yIn1;
		return true;
	}
	return false;
}
bool Gate::CheckIfselected(int x,int y, bool& selected)
{
	if (x > m_GfxInfo.x1 && x<m_GfxInfo.x2 && y>m_GfxInfo.y1 && y<m_GfxInfo.y2)
	{
		selected = m_selected;
		return true;
	}
	selected = false;
	return false;
}

bool Gate::CheckPins()
{
	for (int i = 0; i < m_Inputs; i++)
	{
		if (!m_InputPins[i].GetConnectionStat())
		{
			return false;
		}
	}
	return m_OutputPin.GetConnectionStat();

}

void Gate::load(ifstream& Inputfile)
{
	int ID;
	string label;
	int Cx;
	int Cy;
	Inputfile >> ID;
	Inputfile >> label;
	Inputfile >> Cx;
	Inputfile >> Cy;
	m_GfxInfo.x1 = Cx - UI.AND2_Height / 2;
	m_GfxInfo.x2 = Cx + UI.AND2_Height / 2;
	m_GfxInfo.y1 = Cy - UI.AND2_Width / 2;
	m_GfxInfo.y2 = Cy + UI.AND2_Width / 2;
	SetLabel(label);
	this->ID = ID;
}



int Gate::GetID() const
{
	return ID;
}

void Gate::SetID(int r_ID) 
{
	ID = r_ID;
}