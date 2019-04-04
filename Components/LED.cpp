#include "LED.h"



LED::LED(const GraphicsInfo &r_GfxInfo, int r_FanOut):Component(r_GfxInfo)
{
	count++;
	ID = count;
	m_GfxInfo.x1 = r_GfxInfo.x1;
	m_GfxInfo.y1 = r_GfxInfo.y1;
	m_GfxInfo.x2 = r_GfxInfo.x2;
	m_GfxInfo.y2 = r_GfxInfo.y2;
	countNextComp = 0;
	level = -1;
	m_selected = false;
	//Associate all input pins to this gate
	m_InputPin.setComponent(this);
}

LED::LED(int r_FanOut) 
{
	count++;
	ID = count;
	countNextComp = 0;
	level = -1;
	//Associate all input pins to this gate
	m_InputPin.setComponent(this);
	m_selected = false;
}

void LED::Operate()
{
	if (m_InputPin.getStatus()==HIGH)
	{
		Status = true;
	}
	else
	{
		Status = false;
	}
}


// Function Draw
// Draws LED gate
void LED::Draw(Output* pOut)
{
	if (Status==true)
		pOut->DrawLED1(m_GfxInfo, m_selected);
	else
	//Call output class and pass gate drawing info to it.
	pOut->DrawLED0(m_GfxInfo,m_selected);
	GraphicsInfo gfx = m_GfxInfo;
	gfx.y1 = gfx.y2 + 5;
	pOut->PrintMsg(GetLabel(), gfx);
}

//returns status of outputpin
int LED::GetOutPinStatus()
{
	return -1;
}

void LED::SetID(int r_ID)
{
	ID = r_ID;
}

//returns status of Inputpin #n
int LED::GetInputPinStatus(int n)
{
	 return (STATUS)m_InputPin.getStatus();	//n starts from 1 but array index starts from 0.
}

//Set status of an input pin ot HIGH or LOW
void LED::setInputPinStatus(int n, STATUS s)
{
	m_InputPin.setStatus(s);
}

bool LED::CheckIfselected(int x, int y, bool& selected)
{
	if (x > m_GfxInfo.x1 && x<m_GfxInfo.x2 && y>m_GfxInfo.y1 && y<m_GfxInfo.y2)
	{
		selected = m_selected;
		return true;
	}
	selected = false;
	return false;
}
bool LED::CheckIfInpin(int &x, int &y,int &inputnum)
{
	int xIn1 = m_GfxInfo.x1;
	int yIn1 = m_GfxInfo.y1 + 24;
	int diffx = x - xIn1;
	if (diffx < 0) diffx = -diffx;
	int diffy = y - yIn1;
	if (diffy < 0) diffy = -diffy;
	if (diffx <5 && diffy<5)
	{
		inputnum = 1;
		x = xIn1;
		y = yIn1;
		return true;
	}
	return false;
}

bool LED::CheckPins()
{
	return m_InputPin.GetConnectionStat();
}
LED::~LED()
{
}
InputPin* LED::getinpin(int n)
{
	return &m_InputPin;
}
OutputPin* LED::getoutpin()
{
	return NULL;
}
GraphicsInfo LED::getgrap()
{

	return m_GfxInfo;
}

void LED::GetinputPinCoordinates(int inputnum, int &x, int &y)
{
	if (inputnum == 1)
	{
		x = m_GfxInfo.x1;
		y = m_GfxInfo.y1 + 24;
	}
}


void LED::load(ifstream& Inputfile)
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




bool LED::CheckIfOutpin(int &x, int &y)
{
	return false;
}
int LED::GetStatus() const
{
	return Status;
}

int LED::GetID() const
{
	return ID;
}

void LED::Save(ofstream& Output)
{
	Output << "LED" << "  " << ID << " " << GetLabel() << " ";
	Output << m_GfxInfo.x1 << "  " << m_GfxInfo.y1;
	Output << endl;
}

Component* LED::Copy()
{
	GraphicsInfo temp;
	temp.x1 = temp.x2 = temp.y1 = temp.y2 = 0;
	Component*Copied = new LED(temp, AND2_FANOUT);
	return Copied;
}