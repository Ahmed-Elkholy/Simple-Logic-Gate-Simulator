#include "NOT.h"

NOT::NOT(const GraphicsInfo &r_GfxInfo, int r_FanOut) :Gate(1, r_FanOut)
{
	m_GfxInfo.x1 = r_GfxInfo.x1;
	m_GfxInfo.y1 = r_GfxInfo.y1;
	m_GfxInfo.x2 = r_GfxInfo.x2;
	m_GfxInfo.y2 = r_GfxInfo.y2;
}
NOT::NOT(int r_FanOut) :Gate(2, r_FanOut)
{
}

void NOT::Operate()
{
	//caclulate the output status as the inverting of the input

	if (GetInputPinStatus(1) == HIGH)
		m_OutputPin.setStatus(LOW);
	else
	{
		m_OutputPin.setStatus(HIGH);
	}
}


// Function Draw
// Draws NOT gate
void NOT::Draw(Output* pOut)
{
	//Call output class and pass gate drawing info to it.
	pOut->DrawNOT1(m_GfxInfo,m_selected);
	GraphicsInfo gfx = m_GfxInfo;
	gfx.y1 = gfx.y2 + 5;
	pOut->PrintMsg(GetLabel(), gfx);
}

//returns status of outputpin
int NOT::GetOutPinStatus()

{
	//Operate();
	return m_OutputPin.getStatus();
}


//returns status of Inputpin #n
int NOT::GetInputPinStatus(int n)
{
	return m_InputPins[n - 1].getStatus();	//n starts from 1 but array index starts from 0.
}

//Set status of an input pin ot HIGH or LOW
void NOT::setInputPinStatus(int n, STATUS s)
{
	m_InputPins[n - 1].setStatus(s);
}

bool NOT::CheckIfInpin(int &x, int &y, int &inputnum)
{
	if (Gate::CheckIfInputpin(x, y, 24))
	{
		inputnum = 1;
		return true;
	}
	return false;
}


void NOT::GetinputPinCoordinates(int inputnum,int &x,int &y)
{
	if (inputnum == 1)
	{
		x = m_GfxInfo.x1;
		y = m_GfxInfo.y1 + 24;
	}
}

void NOT::Save(ofstream& Output)
{
	Output << "NOT" << "  " << " " << GetLabel() << " ";
	Output << m_GfxInfo.x1 << "  " << m_GfxInfo.y1;
	Output << endl;
}

Component* NOT::Copy()
{
	GraphicsInfo temp;
	temp.x1 = temp.x2 = temp.y1 = temp.y2 = 0;
	Component*Copied = new NOT(temp, AND2_FANOUT);
	return Copied;
}