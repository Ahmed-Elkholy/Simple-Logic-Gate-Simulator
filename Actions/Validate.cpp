#include "Validate.h"
#include "..\ApplicationManager.h"
Validate::Validate(ApplicationManager *pApp) :Action(pApp)
{
}

Validate::~Validate(void)
{

}

void Validate::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	//Print Action Message


	//Wait for User Input

	//Clear Status Bar

}

void Validate::Execute()
{
	Output *Pout = pManager->GetOutput();
	if (pManager->CheckPins())
	{
		if (!pManager->SortLevels())
		{
			Pout->PrintMsg("There is a feedback in the circuit!");
			pManager->SetValidation(false);
			return;
		}
		pManager->SetValidation(true);
		pManager->SetSimulation(SIMULATION);
		Pout->PrintMsg("The circuit is fully connected");
	}
	else
	{
		pManager->SetValidation(false);
		Pout->PrintMsg("The circuit is not fully connected!");
	}
}

bool Validate::getStatus() const
{
   return validate;
}
void Validate::Undo()
{}
void Validate::Redo()
{}



