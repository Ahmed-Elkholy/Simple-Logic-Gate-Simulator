#include "BUFF.h"

BUFF::BUFF(const GraphicsInfo &r_GfxInfo, int r_FanOut) :Gate(1, r_FanOut)
{
	m_GfxInfo.x1 = r_GfxInfo.x1;
	m_GfxInfo.y1 = r_GfxInfo.y1;
	m_GfxInfo.x2 = r_GfxInfo.x2;
	m_GfxInfo.y2 = r_GfxInfo.y2;
}

BUFF::BUFF(int r_FanOut) :Gate(2, r_FanOut)
{
}


void BUFF::Operate()
{
	//returns input signal

	if (GetInputPinStatus(1) == HIGH)
		m_OutputPin.setStatus(HIGH);
	else
	{
		m_OutputPin.setStatus(LOW);
	}
}


// Function Draw
// Draws BUFFER gate
void BUFF::Draw(Output* pOut)
{
	//Call output class and pass gate drawing info to it.
	pOut->DrawBUF1(m_GfxInfo,m_selected);
	GraphicsInfo gfx = m_GfxInfo;
	gfx.y1 = gfx.y2 + 5;
	pOut->PrintMsg(GetLabel(), gfx);
}

void BUFF::GetinputPinCoordinates(int inputnum,int &x,int &y)
{
	if (inputnum == 1)
	{
		x = m_GfxInfo.x1;
	    y = m_GfxInfo.y1 + 12;
	}
}


//returns status of outputpin
int BUFF::GetOutPinStatus()

{
	//Operate();
	return m_OutputPin.getStatus();
}


//returns status of Inputpin #n
int BUFF::GetInputPinStatus(int n)
{
	return m_InputPins[n - 1].getStatus();	//n starts from 1 but array index starts from 0.
}

//Set status of an input pin ot HIGH or LOW
void BUFF::setInputPinStatus(int n, STATUS s)
{
	m_InputPins[n - 1].setStatus(s);
}
bool BUFF::CheckIfInpin(int &x, int &y, int &inputnum) //REVISE DI
{
	if (Gate::CheckIfInputpin(x, y, 23))
	{
		inputnum = 1;
		return true;
	}
	return false;
}

void BUFF::Save(ofstream& Output)
{
	Output << "BUFF" << "  " << ID << " " << GetLabel() << " ";
	Output << m_GfxInfo.x1 << "  " << m_GfxInfo.y1;
	Output << endl;
}

Component* BUFF::Copy()
{
	GraphicsInfo temp;
	temp.x1 = temp.x2 = temp.y1 = temp.y2 = 0;
	Component*Copied = new BUFF(temp, AND2_FANOUT);
	return Copied;
}