#include "XOR3.h"

XOR3::XOR3(const GraphicsInfo &r_GfxInfo, int r_FanOut) :Gate(3, r_FanOut)
{
	m_GfxInfo.x1 = r_GfxInfo.x1;
	m_GfxInfo.y1 = r_GfxInfo.y1;
	m_GfxInfo.x2 = r_GfxInfo.x2;
	m_GfxInfo.y2 = r_GfxInfo.y2;
}
XOR3::XOR3(int r_FanOut) :Gate(2, r_FanOut)
{
}

void XOR3::Operate()
{
	//caclulate the output status as the XORing of the three input pins
	if (GetInputPinStatus(1) == LOW && GetInputPinStatus(2) == LOW && GetInputPinStatus(3)== HIGH)
		m_OutputPin.setStatus(HIGH);
	else if (GetInputPinStatus(1) == LOW && GetInputPinStatus(2) == HIGH && GetInputPinStatus(3) == LOW)
		m_OutputPin.setStatus(HIGH);
	else if (GetInputPinStatus(1) == HIGH && GetInputPinStatus(2) == LOW && GetInputPinStatus(3) == LOW)
		m_OutputPin.setStatus(HIGH);
	else if (GetInputPinStatus(1) == HIGH && GetInputPinStatus(2) == HIGH && GetInputPinStatus(3) == HIGH)
		m_OutputPin.setStatus(HIGH);
	else
		m_OutputPin.setStatus(LOW);
}


// Function Draw
// Draws 3-input XOR gate
void XOR3::Draw(Output* pOut)
{
	//Call output class and pass gate drawing info to it.
	pOut->DrawXOR3(m_GfxInfo,m_selected);
	GraphicsInfo gfx = m_GfxInfo;
	gfx.y1 = gfx.y2 + 5;
	pOut->PrintMsg(GetLabel(), gfx);
}

//returns status of outputpin
int XOR3::GetOutPinStatus()
{
	return m_OutputPin.getStatus();
}


//returns status of Inputpin #n
int XOR3::GetInputPinStatus(int n)
{
	return m_InputPins[n - 1].getStatus();	//n starts from 1 but array index starts from 0.
}

//Set status of an input pin ot HIGH or LOW
void XOR3::setInputPinStatus(int n, STATUS s)
{
	m_InputPins[n - 1].setStatus(s);
}
bool XOR3::CheckIfInpin(int &x, int &y, int &inputnum)
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
	if (Gate::CheckIfInputpin(x, y, 24))
	{
		inputnum = 3;
		return true;
	}
	return false;
}


void XOR3::GetinputPinCoordinates(int inputnum,int &x,int &y)
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

	if (inputnum == 3)
	{
		x= m_GfxInfo.x1;
		y = m_GfxInfo.y1 + 24;
	}
}

void XOR3::Save(ofstream& Output)
{
	Output << "XOR3" << "  " << ID << " " << GetLabel() << " ";
	Output << m_GfxInfo.x1 << "  " << m_GfxInfo.y1;
	Output << endl;
}
Component* XOR3::Copy()
{
	GraphicsInfo temp;
	temp.x1 = temp.x2 = temp.y1 = temp.y2 = 0;
	Component*Copied = new XOR3(temp, AND2_FANOUT);
	return Copied;
}