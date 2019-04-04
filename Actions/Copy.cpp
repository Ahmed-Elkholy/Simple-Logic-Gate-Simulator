#include "Copy.h"
#include "Move.h"
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

Copy::Copy(ApplicationManager *pApp) :Action(pApp)
{
}

Copy::~Copy(void)
{
}

void Copy::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//Print Action Message
	pOut->PrintMsg("Click to Copy a component");

	//Wait for User Input
	pIn->GetPointClicked(Cx, Cy);

	//Clear Status Bar
	pOut->ClearStatusBar();

}

void Copy::Execute()
{
	GraphicsInfo GInfo;
	//Get Center point of the Gate
	ReadActionParameters();
	ToCopy = pManager->GetSelectedComponent();
	Copied = NULL;
	if (pManager->getCopied() != NULL)
	{
		pManager->DeleteCopy();
	}

	if (ToCopy != NULL && pManager->getCopied()==NULL)
	{
		Copied = ToCopy->Copy();
		Copied->SetLabel(ToCopy->GetLabel());
	}
	

	pManager->setCopied(Copied);
	pManager->SetClipBoardStatus(true);
	
}

void Copy::Undo()
{
	//delete Copied;
	Copied = NULL;
	pManager->setCopied(Copied);
}

void Copy::Redo()
{
	if (ToCopy != NULL)
	{
		Copied = ToCopy->Copy();
		Copied->SetLabel(ToCopy->GetLabel());
	}
	pManager->setCopied(Copied);
	pManager->SetClipBoardStatus(true);
}


