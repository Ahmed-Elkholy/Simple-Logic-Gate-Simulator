#include "NOR2.h"

NOR2::NOR2(const GraphicsInfo &r_GfxInfo, int r_FanOut) :Gate(2, r_FanOut)
{
	m_GfxInfo.x1 = r_GfxInfo.x1;
	m_GfxInfo.y1 = r_GfxInfo.y1;
	m_GfxInfo.x2 = r_GfxInfo.x2;
	m_GfxInfo.y2 = r_GfxInfo.y2;
}

NOR2::NOR2(int r_FanOut) :Gate(2, r_FanOut)
{
}
void NOR2::Operate()
{
	//caclulate the output status as the NORing of the two input pins
	if (GetInputPinStatus(1) == HIGH || GetInputPinStatus(2) == HIGH)
		m_OutputPin.setStatus(LOW);
	else
	{
		m_OutputPin.setStatus(HIGH);
	}
}


// Function Draw
// Draws 2-input NOR gate
void NOR2::Draw(Output* pOut)
{
	//Call output class and pass gate drawing info to it.
	pOut->DrawNOR2(m_GfxInfo,m_selected);
	GraphicsInfo gfx = m_GfxInfo;
	gfx.y1 = gfx.y2 + 5;
	pOut->PrintMsg(GetLabel(), gfx);
}

//returns status of outputpin
int NOR2::GetOutPinStatus()
{
	return m_OutputPin.getStatus();
}


//returns status of Inputpin #n
int NOR2::GetInputPinStatus(int n)
{
	return m_InputPins[n - 1].getStatus();	//n starts from 1 but array index starts from 0.
}

//Set status of an input pin ot HIGH or LOW
void NOR2::setInputPinStatus(int n, STATUS s)
{
	m_InputPins[n - 1].setStatus(s);
}

bool NOR2::CheckIfInpin(int &x, int &y, int &inputnum)
{
	if (Gate::CheckIfInputpin(x, y, 12))
	{
		inputnum = 1;
		return true;
	}
	if (Gate::CheckIfInputpin(x, y, 36))
	{
		inputnum = 2;
		return true;
	}
	return false;
}

void NOR2::GetinputPinCoordinates(int inputnum, int &x, int &y)
{
	if (inputnum == 1)
	{
		x = m_GfxInfo.x1;
		y = m_GfxInfo.y1 + 12;
	}
	if (inputnum == 2)
	{
		x = m_GfxInfo.x1;
		y = m_GfxInfo.y1 + 36;
	}
}

void NOR2::Save(ofstream& Output)
{
	Output << "NOR2" << "  " << ID << " " << GetLabel() << " ";
	Output << m_GfxInfo.x1 << "  " << m_GfxInfo.y1;
	Output << endl;
}

Component* NOR2::Copy()
{
	GraphicsInfo temp;
	temp.x1 = temp.x2 = temp.y1 = temp.y2 = 0;
	Component*Copied = new NOR2(temp, AND2_FANOUT);
	return Copied;
}