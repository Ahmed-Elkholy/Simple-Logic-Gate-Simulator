#include "Select.h"
#include "..\ApplicationManager.h"
Select::Select(ApplicationManager *pApp) :Action(pApp)
{
}

Select::~Select(void)
{
}

void Select::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	/*Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//Print Action Message
	pOut->PrintMsg("Click to select a component");

	//Wait for User Input
	pIn->GetPointClicked(Cx, Cy);

	//Clear Status Bar
	pOut->ClearStatusBar();*/

	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//Print Action Message
	pOut->PrintMsg("Click to select a component");
	//Wait for User Input
	pIn->GetPointClicked(Cx, Cy);
	color c = pOut->getpixelcol(Cx, Cy);
	if (c.ucBlue == 255 && c.ucGreen == 255 && c.ucRed == 255) type = true;
	else type = false;
	if (type)
	{
		if (Cy < UI.ToolBarHeight) Cy = UI.ToolBarHeight + 2;
		if (Cy > UI.height - UI.StatusBarHeight) Cy = UI.height - UI.StatusBarHeight - 2;
		bool first = true;
		int x, y, xt = Cx, yt = Cy;
		while (pIn->GetMouseType(Cx, Cy) == 0)
		{
			pIn->GetCurrentClick(Cx, Cy);
			if (Cy < UI.ToolBarHeight) Cy = UI.ToolBarHeight + 2;
			if (Cy > UI.height - UI.StatusBarHeight) Cy = UI.height - UI.StatusBarHeight - 2;
			if (first) { x = Cx; y = Cy; }

			pOut->drawrect(Cx, Cy, x, y);
			if (Cx != xt || Cy != yt)
			{
				pOut->ClearDrawingArea();
				pManager->UpdateInterface();
			}
			xt = Cx; yt = Cy;
			first = false;

		}
		this->x = x;
		this->y = y;
	}
	pOut->ClearDrawingArea();
	pManager->UpdateInterface();


	pOut->ClearStatusBar();
}

void Select::Execute()
{
	//Get Center point of the Gate
	ReadActionParameters();
	if (type)
	{

		if (x<Cx && y < Cy)
			pManager->GetSelComponent(x, y, Cx, Cy);
		else if (x<Cx && y> Cy)
			pManager->GetSelComponent(x, Cy, Cx, y);
		else if (x > Cx && y < Cy)
			pManager->GetSelComponent(Cx, y, x, Cy);
		else if (x > Cx && y>Cy)
			pManager->GetSelComponent(Cx, Cy, x, y);
		if (x == Cx && y == Cy)
			pManager->GetSelComponent(0, 0, 0, 0);
	}
	else {
		Component* pc = pManager->GetSelectedComponent(Cx, Cy);
		if (pc == NULL) return;
		if (!pc->GetSelectedstat())
			pc->SetSelectionStat(true);  //select
		else
			pc->SetSelectionStat(false); //deselect
	}

}

void Select::Undo()
{}

void Select::Redo()
{}

