#include "EditLabel.h"
#include "..\ApplicationManager.h"
EditLabel::EditLabel(ApplicationManager *pApp) :Action(pApp)
{
}

EditLabel::~EditLabel(void)
{

}

void EditLabel::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	//Print Action Message
	newlabel=pIn->EditString(pOut,newlabel);

	//Wait for User Input

	//Clear Status Bar
	pOut->ClearStatusBar();

}

void EditLabel::Execute()
{
	//Get string from user
	Output* pOut = pManager->GetOutput();
	pc = pManager->GetSelectedComponent();
	if (pc == NULL)
	{
		pOut->PrintMsg("Please select only one component");
		return;
	}
	newlabel = pc->GetLabel();
	/*if (label.size() == 0)
	{
		pOut->PrintMsg("No label to Edit");
		return;
	}
	*/
	oldlabel = pc->GetLabel();
	ReadActionParameters();
	pOut->ClearDrawingArea();
	pc->SetLabel(newlabel);
}

void EditLabel::Undo()
{
	Output* pOut = pManager->GetOutput();
	if (pc == NULL) return;
	pc->SetLabel(oldlabel);
	pOut->ClearDrawingArea();
}

void EditLabel::Redo()
{
	Output* pOut = pManager->GetOutput();
	if (pc == NULL) return;
	pc->SetLabel(newlabel);
	pOut->ClearDrawingArea();

}



