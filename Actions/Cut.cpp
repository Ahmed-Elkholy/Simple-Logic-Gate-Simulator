#include "Cut.h"
#include "Copy.h"
#include "Delete.h"
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

Cut::Cut(ApplicationManager *pApp) :Action(pApp)
{
}

Cut::~Cut(void)
{
	delete ToCut;
}

void Cut::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//Print Action Message
	pOut->PrintMsg("Click to Cut a component");

	//Wait for User Input
	pIn->GetPointClicked(Cx, Cy);

	//Clear Status Bar
	pOut->ClearStatusBar();

}

void Cut::Execute()
{
	ReadActionParameters();
	Output* pOut = pManager->GetOutput();
	ToCut = pManager->GetSelectedComponent();
	if (ToCut == NULL) return;
	if (pManager->getCopied() != NULL)
	{
		pManager->DeleteCopy();
	}
	Cutt = ToCut->Copy();
	pManager->setCopied(Cutt);
	InputPin* in1 = ToCut->getinpin(1);
	InputPin * in2 = ToCut->getinpin(2);
	InputPin* in3 = ToCut->getinpin(3);
	OutputPin* out = ToCut->getoutpin();
	pManager->RemoveGate(ToCut);

	pManager->RemoveGate(in1, in2, in3, out, ToCut);

	pManager->DeleteSelected(ToCut);

	//out->Deletecon();
	//pManager->DeleteGate(ToCut);
	pManager->SetClipBoardStatus(false);
	pOut->ClearDrawingArea();
}

void Cut::Undo()
{

	pManager->setCopied(NULL);
	Cutt->SetGraphics(Cx, Cy);
	pManager->AddComponent(Cutt);
}

void Cut::Redo()
{
	Output* pOut = pManager->GetOutput();
	ToCut = Cutt;
	Cutt = ToCut->Copy();
	pManager->setCopied(Cutt);
	pManager->SetClipBoardStatus(false);
	InputPin* in1 = ToCut->getinpin(1);
	InputPin * in2 = ToCut->getinpin(2);
	InputPin* in3 = ToCut->getinpin(3);
	OutputPin* out = ToCut->getoutpin();
	pManager->RemoveGate(ToCut);

	pManager->RemoveGate(in1, in2, in3, out, ToCut);
	pOut->ClearDrawingArea();
}