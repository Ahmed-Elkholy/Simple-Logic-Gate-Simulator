#include "Connection.h"
Connection::Connection(const GraphicsInfo &r_GfxInfo, OutputPin *pSrcPin,InputPin *pDstPin):Component(r_GfxInfo)	
{
	SrcPin = pSrcPin;
	DstPin = pDstPin;
	GraphicsInfo gfx;
	gfx.x1 = r_GfxInfo.x1;
	gfx.y1 = r_GfxInfo.y1;
	gfx.x2 = (r_GfxInfo.x1+r_GfxInfo.x2)/2;
	gfx.y2 = r_GfxInfo.y1;
	Lines.push_back(gfx);
	gfx.x1 = (r_GfxInfo.x1 + r_GfxInfo.x2) / 2;
	gfx.y1 = r_GfxInfo.y1;
	gfx.x2 = (r_GfxInfo.x1 + r_GfxInfo.x2) / 2;
	gfx.y2 = r_GfxInfo.y2;
	Lines.push_back(gfx);
	gfx.x1 = (r_GfxInfo.x1 + r_GfxInfo.x2) / 2;
	gfx.y1 = r_GfxInfo.y2;
	gfx.x2 = r_GfxInfo.x2;
	gfx.y2 = r_GfxInfo.y2;
	Lines.push_back(gfx);
	m_selected = false;
}
void Connection::setSourcePin(OutputPin *pSrcPin)
{	SrcPin = pSrcPin;	}

OutputPin* Connection::getSourcePin()
{	return SrcPin;	}


void Connection::setDestPin(InputPin *pDstPin)
{	DstPin = pDstPin;	}

InputPin* Connection::getDestPin()
{	return DstPin;	}


void Connection::Operate()
{
	//Status of connection destination pin = status of connection source pin
	DstPin->setStatus((STATUS)SrcPin->getStatus());
}

void Connection::Draw(Output* pOut)
{
	pOut->DrawConnection(m_GfxInfo,m_selected);
	GraphicsInfo gfx = m_GfxInfo;
	gfx.x1 = (gfx.x2 + gfx.x1) / 2 + 10;
	pOut->PrintMsg(GetLabel(), gfx);
}

int Connection::GetOutPinStatus()	//returns status of outputpin if LED, return -1
{
	//Operate();
	return DstPin->getStatus();
}


int Connection::GetInputPinStatus(int n)	//returns status of Inputpin # n if SWITCH, return -1
{
	
	return SrcPin->getStatus();	//n is ignored as connection has only one input pin (src pin)	
}

void Connection::setInputPinStatus(int n, STATUS s) 
{
	SrcPin->setStatus(s);
}
void Connection::SetGraphics(int x, int y, bool type)
{
	if (type == true) {
		m_GfxInfo.x1 = x; m_GfxInfo.y1 = y;
	}

	if (type == false) {
		m_GfxInfo.x2 = x; m_GfxInfo.y2 = y;
	}
}
void Connection::SetGraphics(GraphicsInfo gfx)
{
	m_GfxInfo = gfx;
}

bool Connection::CheckIfselected(int x, int y, bool &selected)
{
	GraphicsInfo gfx;
		gfx=Lines.at(0);
		if (y >gfx.y2-6 &&y<gfx.y2+6 && (x >= gfx.x1 && x<gfx.x2 || x >= gfx.x2 && x<gfx.x1))
		{
			selected = m_selected;
			return true;
		}
		gfx = Lines.at(1);
		if (x >gfx.x2 - 6 && x<gfx.x2 + 6 && (y >gfx.y2 && y<gfx.y1 || y >gfx.y1 && y<gfx.y2))
		{
			selected = m_selected;
			return true;
		}
		gfx = Lines.at(2);
		if (x >= gfx.x1 &&x<gfx.x2 && y >gfx.y2 - 6 && y<gfx.y2 + 6)
		{
			selected = m_selected;
			return true;
		}
	selected = false;
	return false;
}
/*
bool Connection::CheckIfselected(int x, int y,bool &selected)
{
	int mid = (m_GfxInfo.x1 + m_GfxInfo.x2)/2	;
	if (m_GfxInfo.y1 > m_GfxInfo.y2)
	{
		if (x >= m_GfxInfo.x1 && x < mid && y >= m_GfxInfo.y2 && y < m_GfxInfo.y1) //first horizontal line
		{
			selected = m_selected;
			return true;
		}
		if (x == mid && y >= m_GfxInfo.y2 && y < m_GfxInfo.y1) // vertical line
		{
			selected = m_selected;
			return true;
		}
		if (x >= mid && x < m_GfxInfo.x2 && y == m_GfxInfo.y2) //second horizontal line
		{
			selected = m_selected;
			return true;
		}
	}
	else
	{
		if (x >= m_GfxInfo.x1 && x < mid && y >= m_GfxInfo.y1 && y < m_GfxInfo.y2) //first horizontal line
		{
			selected = m_selected;
			return true;
		}
		if (x == mid && y >= m_GfxInfo.y1 && y < m_GfxInfo.y2) // vertical line
		{
			selected = m_selected;
			return true;
		}
		if (x >= mid && x < m_GfxInfo.x2 && y == m_GfxInfo.y2) //second horizontal line
		{
			selected = m_selected;
			return true;
		}

	}
	selected = false;
	return false;
}
*/
bool Connection::CheckPins()
{
	return true;
}
void Connection::SetInputNum(int n)
{
	DstPinNum = n;
}


void Connection::load(ifstream& Inputfile)
{

}

bool Connection::CheckIfOutpin(int &x, int &y)
{
	return false;
}


bool Connection::CheckIfInpin(int &x, int & y, int& inputnum)
{
	return false;
}

void Connection::Save(ofstream & Outputfile)
{
	int rID= SrcPin->GetCompID();
	int rID2 = DstPin->GetCompID();
	Outputfile << rID << "  " << rID2<< " ";
	Outputfile << DstPinNum << endl;

}


void Connection::GetinputPinCoordinates(int inputnum,int &x,int &y)
{

}

int Connection::GetID() const
{
	return -1;
}

void Connection::SetID(int r_ID) 
{

}

int Connection::GetInputNum() const
{
	return DstPinNum;
}



Component* Connection::Copy()
{
	return NULL;
}