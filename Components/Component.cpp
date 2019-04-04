#include "Component.h"
using namespace std;
int Component::count = 0;
Component::Component(const GraphicsInfo &r_GfxInfo)
{
	m_GfxInfo = r_GfxInfo;	
	countNextComp = 0;
	m_selected = false;
}
void Component::SetSelectionStat(bool selected)
{
	m_selected = selected;
}
bool Component::GetSelectedstat()
{
	return m_selected;
}
void Component::SetLabel(string s)
{
	m_Label = s;
}

string Component::GetLabel() const
{
	return m_Label;
}

void Component::SetGraphics(int x, int y, bool type)    //ttktb fe kol component w teb2a virtual
{
	int Len = UI.AND2_Width;
	int Wdth = UI.AND2_Height;
	GraphicsInfo GInfo; //Gfx info to be used to construct the AND2 gate

	GInfo.x1 = x - Len / 2;
	GInfo.x2 = x + Len / 2;
	GInfo.y1 = y - Wdth / 2;
	GInfo.y2 = y + Wdth / 2;
	m_GfxInfo = GInfo;
}

void Component::SetNextComp(Component * c)
{
	nextComp.push_back(c);
	countNextComp++;
}
Component* Component::GetNextComp(int count)
{
	if (count + 1 > countNextComp) return NULL;
	return nextComp.at(count);
}
void Component::DeleteNextComp(Component* pc)
{
	for (int i = 0; i < countNextComp; i++)
	{
		if (nextComp.at(i) == pc)
		{
			nextComp[i] = nextComp[countNextComp - 1];
			nextComp[countNextComp - 1] = NULL;
			countNextComp--;
		}
	}
}
int Component::GetLevel() const
{
	return level;
}

void Component::SetVisited(bool m_visited)
{
	visited = m_visited;
}

bool Component::GetVisited() const
{
	return visited;
}




void Component::SetLevel(int L)
{
	if (L>level) //assuming level is intially -1
	level = L;
}


Component::Component()
{}

Component::~Component()
{}

