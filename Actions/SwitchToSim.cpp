#include "SwitchToSim.h"
#include "..\ApplicationManager.h"
SwitchToSim::SwitchToSim(ApplicationManager *pApp) :Action(pApp)
{
}

SwitchToSim::~SwitchToSim(void)
{

}

void SwitchToSim::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	//Print Action Message


	//Wait for User Input

	//Clear Status Bar

}

void SwitchToSim::Execute()
{
	Output *Pout = pManager->GetOutput();
	if (!pManager->CheckPins()) return;
	if (!pManager->SortLevels())
	{
		Pout->PrintMsg("There is a feedback in the circuit!");
		pManager->SetValidation(false);
		return;
	}
	Pout->ClearDesignToolBar();
	Pout->CreateSimulationToolBar();
}

bool SwitchToSim::getStatus() const
{
   return validate;
}
void SwitchToSim::Undo()
{}
void SwitchToSim::Redo()
{}



