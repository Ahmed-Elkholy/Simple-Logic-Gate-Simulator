#include "SwitchToDSN.h"
#include "..\ApplicationManager.h"
SwitchToDSN::SwitchToDSN(ApplicationManager *pApp) :Action(pApp)
{
}

SwitchToDSN::~SwitchToDSN(void)
{

}

void SwitchToDSN::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	//Print Action Message


	//Wait for User Input

	//Clear Status Bar

}

void SwitchToDSN::Execute()
{
	Output *Pout = pManager->GetOutput();
	if (!pManager->GetValidation()) return;
	Pout->ClearDesignToolBar();
	Pout->CreateDesignToolBar();
}

bool SwitchToDSN::getStatus() const
{
   return validate;
}
void SwitchToDSN::Undo()
{}
void SwitchToDSN::Redo()
{}



