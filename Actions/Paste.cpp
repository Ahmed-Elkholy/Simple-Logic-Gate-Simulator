#include "Copy.h"
#include "Paste.h"
#include "..\Components\AND2.h"
#include "..\ApplicationManager.h"
#include "..\Components\AND3.h"
#include "..\Components\BUFF.h"
#include "..\Components\Connection.h"
#include "..\Components\OR2.h"
#include "..\Components\LED.h"
#include "..\Components\NAND2.h"
#include "..\Components\NOR2.h"
#include "..\Components\NOR3.h"
#include "..\Components\NOT.h"
#include "..\Components\SWITCH.h"
#include "..\Components\XNOR2.h"
#include "..\Components\XOR2.h"
#include "..\Components\XOR3.h"
#include "AddANDgate2.h"
#include "AddANDgate3.h"
#include "AddBUFFgate.h"
#include "AddLabel.h"
#include "AddLed.h"
#include "AddNANDgate2.h"
#include "AddNORgate2.h"
#include "AddNORgate3.h"
#include "AddNOTgate.h"
#include "AddORgate2.h"
#include "AddSWITCH.h"
#include "AddXNORgate2.h"
#include "AddNORgate3.h"
#include "AddXORgate3.h"
#include "AddXORgate2.h"

Paste::Paste(ApplicationManager* pActionpp):Action(pActionpp)
{
}

Paste::~Paste(void)
{
}

void Paste::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//Print Action Message
	pOut->PrintMsg("Click to Paste a component");

	//Wait for User Input
	pIn->GetPointClicked(Cx, Cy);

	//Clear Status Bar
	pOut->ClearStatusBar();

}

void Paste::Execute()
{

	//Get Center point of the Gate
	ReadActionParameters();
	if (!CheckCoordinates(Cx, Cy)) return;
	ToPaste = pManager->getCopied();
	if (ToPaste == NULL) 
		return;

	ToPaste->SetGraphics(Cx, Cy);
	pManager->AddComponent(ToPaste);
	Pasted = ToPaste;
	if (!pManager->GetClipBoardStatus())
	{
		ToPaste = NULL;
		pManager->setCopied(NULL);
		return;
	}
	ToPaste = ToPaste->Copy();
	pManager->setCopied(ToPaste);
	ToPaste->SetLabel(pManager->getCopied()->GetLabel());
}

void Paste::Undo()
{
	//delete ToPaste;
	//ToPaste = NULL
	if (!CheckCoordinates(Cx, Cy)) return;
	pManager->RemoveGate(Pasted);
	Output* pOut = pManager->GetOutput();
	pOut->ClearDrawingArea();
}

void Paste::Redo()
{
	if (!CheckCoordinates(Cx, Cy)) return;
	if (ToPaste == NULL)
		return;
	ToPaste->SetGraphics(Cx, Cy);
	pManager->AddComponent(ToPaste);
	Pasted = ToPaste;
	if (!pManager->GetClipBoardStatus())
	{
		ToPaste = NULL;
		pManager->setCopied(NULL);
		return;
	}
	ToPaste = ToPaste->Copy();
	ToPaste->SetLabel(pManager->getCopied()->GetLabel());
}

void Paste::setCopied(Component*Copied)
{
	ToPaste = Copied;
}