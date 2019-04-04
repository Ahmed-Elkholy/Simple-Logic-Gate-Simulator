#include "SWITCH.h"



SWITCH::SWITCH(const GraphicsInfo &r_GfxInfo, int r_FanOut) :m_OutputPin(r_FanOut)
{
	count++;
	ID = count;
	m_selected = false;
	countNextComp = 0;
	level = -1;
	m_GfxInfo.x1 = r_GfxInfo.x1;
	m_GfxInfo.y1 = r_GfxInfo.y1;
	m_GfxInfo.x2 = r_GfxInfo.x2;
	m_GfxInfo.y2 = r_GfxInfo.y2;
	m_OutputPin.SetCompID(ID);
}
SWITCH::SWITCH(int r_FanOut) :m_OutputPin(r_FanOut)
{
	count++;
	ID = count;
	m_selected = false;
	countNextComp = 0;
	level = -1;
	m_selected = false;
	m_OutputPin.SetCompID(ID);
}
bool SWITCH::CheckIfOutpin(int &x, int &y)//TABA3AK DOL
{
	int xOut = m_GfxInfo.x1 + UI.AND2_Width - 5;
	int yOut = m_GfxInfo.y1 + 23;
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
bool SWITCH::CheckIfselected(int x, int y, bool& selected)
{
	if (x > m_GfxInfo.x1 && x<m_GfxInfo.x2 && y>m_GfxInfo.y1 && y<m_GfxInfo.y2)
	{
		selected = m_selected;
		return true;
	}
	selected = false;
	return false;
}
void SWITCH::Operate()
{
	if (Opened)
	{
		m_OutputPin.setStatus(LOW);
	}
	else
	{
		m_OutputPin.setStatus(HIGH);
	}
}


void SWITCH::load(ifstream& Inputfile)
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


// Function Draw
// Draws SWITCH gate
void SWITCH::Draw(Output* pOut)
{
	//Call output class and pass gate drawing info to it.
	if (Opened)
	{
		pOut->DrawSwitchOpened(m_GfxInfo,m_selected);
	}
	else
	{
		pOut->DrawSwitchClosed(m_GfxInfo);
	}
	GraphicsInfo gfx = m_GfxInfo;
	gfx.y1 = gfx.y2 + 5;
	pOut->PrintMsg(GetLabel(), gfx);
		
}

//returns status of outputpin
int SWITCH::GetOutPinStatus()
{
	return m_OutputPin.getStatus();
}


//returns status of Inputpin #n
int SWITCH::GetInputPinStatus(int n)
{
	return -1;	//n starts from 1 but array index starts from 0
}

//Set status of an input pin ot HIGH or LOW
void SWITCH::setInputPinStatus(int n, STATUS s)
{
	return;
}
void SWITCH::SetStatus(bool m_Opened)
{
	Opened = m_Opened;
}
bool SWITCH::GetStatus()
{
	return Opened;
}

int SWITCH::GetID() const
{
	return ID;
}

bool SWITCH::CheckPins()
{
	return m_OutputPin.GetConnectionStat();
}


void SWITCH::GetinputPinCoordinates(int inputnum,int &x,int &y)
{
}

void SWITCH::SetID(int r_ID)
{
	ID = r_ID;
}

void SWITCH::Save(ofstream& Output)
{
	Output << "SWITCH" << "  " << ID <<" "<<GetLabel() << " ";
	Output << m_GfxInfo.x1 << "  " << m_GfxInfo.y1;
	Output << endl;
}

bool SWITCH::CheckIfInpin(int &x, int &y, int &inputnum)
{
	return false;
}

Component* SWITCH::Copy()
{
	GraphicsInfo temp;
	temp.x1 = temp.x2 = temp.y1 = temp.y2 = 0;
	Component*Copied = new SWITCH(temp, AND2_FANOUT);
	return Copied;
}