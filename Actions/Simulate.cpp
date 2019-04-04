#include "Simulate.h"
#include "..\ApplicationManager.h"
#include"..\Components\SWITCH.h"
Simulate1::Simulate1(ApplicationManager *pApp) :Action(pApp)
{
}

Simulate1::~Simulate1(void)
{

}

void Simulate1::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//Print Action Message
	pOut->PrintMsg("Click to select a switch");

	//Wait for User Input
	pIn->GetPointClicked(Cx, Cy);

	//Clear Status Bar
	pOut->ClearStatusBar();

}

void Simulate1::Execute()
{
		//Get Center point of the Gate
		ReadActionParameters();
		Component* pc = pManager->GetSelectedComponent(Cx, Cy);
		if (pc == NULL || !dynamic_cast<SWITCH*>(pc)) return;
		if (!((SWITCH*)pc)->GetStatus())
			((SWITCH*)pc)->SetStatus(true);  //ON
		else
			((SWITCH*)pc)->SetStatus(false); //OFF
		pManager->OperateAll();
}
void Simulate1::Undo()
{}
void Simulate1::Redo()
{}



