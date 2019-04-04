#include "AddLabel.h"
#include "..\ApplicationManager.h"
AddLabel::AddLabel(ApplicationManager *pApp) :Action(pApp)
{
}

AddLabel::~AddLabel(void)
{

}

void AddLabel::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	//Print Action Message
	pOut->PrintMsg("Please type a string");
	newlabel=pIn->GetString(pOut);

	//Wait for User Input

	//Clear Status Bar
	pOut->ClearStatusBar();

}

void AddLabel::Execute()
{
	//Get string from user
	ReadActionParameters();
	Output* pOut = pManager->GetOutput();
	pc = pManager->GetSelectedComponent();
	if (pc == NULL)
	{
		pOut->PrintMsg("Please select only one component");
		return;
	}
	if ((pc->GetLabel()).size() > 0)
	{
		pOut->PrintMsg("Already labelled");
		return;
	}
		oldlabel = pc->GetLabel();
	    pc->SetLabel(newlabel);
}
void AddLabel::Undo()
{
	Output* pOut = pManager->GetOutput();
	if (pc == NULL) return;
	pc->SetLabel(oldlabel);
	pOut->ClearDrawingArea();
}
void AddLabel::Redo()
{
	Output* pOut = pManager->GetOutput();
	if (pc == NULL) return;
	pc->SetLabel(newlabel);
	pOut->ClearDrawingArea();
}



