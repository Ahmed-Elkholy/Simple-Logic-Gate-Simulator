#include "Probe.h"
#include "..\ApplicationManager.h"
Probe::Probe(ApplicationManager *pApp) :Action(pApp)
{
}

Probe::~Probe(void)
{
}

void Probe::ReadActionParameters() //under construction
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//Print Action Message
	pOut->PrintMsg("Probing tool: Click to select a connection or pin");
	//Wait for User Input
	pIn->GetPointClicked(Cx,Cy);
	//Clear Status Bar
	pOut->ClearStatusBar();

}
void Probe::Execute() //under construction
{
	ReadActionParameters();
	int inputnum;
	Output* pOut = pManager->GetOutput();
	int S;
	Component *pc = pManager->GetCompOfOutputPin(Cx, Cy);
	if (pc != NULL)
		S = pc->GetOutPinStatus();
	if (pc = NULL)
	{
		if (pc == NULL)
			pc = pManager->GetCompOfInputPin(Cx, Cy, inputnum);
		if (pc != NULL)
			S = pc->GetInputPinStatus(inputnum);
	}
	if (pc == NULL)
	{
		pc = pManager->GetComponent(Cx, Cy);
		if (!dynamic_cast<Connection*>(pc)) return;
		S=pc->GetInputPinStatus(1);
	}
	if (pc == NULL) return;
	if (S == 0)
	{
		pOut->PrintMsg("The value is zero");
	}
	else
	{
		pOut->PrintMsg("The value is one");
	}
}

void Probe::Undo()
{}

void Probe::Redo()
{}




