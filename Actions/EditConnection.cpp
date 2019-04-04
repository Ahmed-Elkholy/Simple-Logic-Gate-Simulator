#include "EditConnection.h"
#include "..\ApplicationManager.h"
EditConnection::EditConnection(ApplicationManager *pApp) :Action(pApp)
{
}

EditConnection::~EditConnection(void)
{
}

void EditConnection::ReadActionParameters() //under construction
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//Print Action Message
	pOut->PrintMsg("Edit connection: Click to edit connection");
	//Wait for User Input
	Component *pcomp = pManager->GetSelectedComponent();
	if (pcomp == NULL || !dynamic_cast<Connection*>(pcomp))
	{
		pOut->PrintMsg("Please select exactly one connection");
		pC = NULL;
		return;
	}
	pC = (Connection*)pcomp;
	oldinputnum=pC->GetInputNum();
	pOut->PrintMsg("Click on an Output Pin");
		pIn->GetPointClicked(x1, y1);
		pIn->CheckCoordinates(x1, y1, pOut, 2);
		pSource = pManager->GetCompOfOutputPin(x1, y1);
		if (pSource == NULL) return;
	//moving check coordinates?
		pOut->PrintMsg("Click on the second pin");
		pIn->GetPointClicked(x2, y2);
		pIn->CheckCoordinates(x2, y2, pOut, 2);
		pDest = pManager->GetCompOfInputPin(x2, y2, newinputnum);
		if (pDest == NULL) return;
		outputPtr = pSource->getoutpin();
		inputPtr = pDest->getinpin(newinputnum);
	//Clear Status Bar
	pOut->ClearStatusBar();

}
void EditConnection::Execute() //under construction(urgent change -->simulation)
{
	ReadActionParameters();
	Output* pOut = pManager->GetOutput();
	GraphicsInfo GInfo; //Gfx info to be used to construct the connection
	if (outputPtr == NULL || inputPtr == NULL || pC==NULL) return;
	GInfo.x1 = x1;
	GInfo.x2 = x2;
	GInfo.y1 = y1;
	GInfo.y2 = y2;
	OriginalOutput = pC->getSourcePin();
	OriginalInput = pC->getDestPin();


	if (inputPtr->GetConnectionStat() && inputPtr != OriginalInput) return;

	OrigOutputcomp = pManager->GetComp(OriginalOutput);
	OrigOutputcomp->DeleteNextComp(pC);
	inputPtr->SetConnectionStat(true);
	inputPtr->SetConnection(pC);
	if (outputPtr != OriginalOutput)
	{
		bool connected = outputPtr->ConnectTo(pC);
		if (!connected) return;
		OriginalInput->SetConnectionStat(false);
		OriginalInput->SetConnection(NULL);
		OriginalOutput->DeleteConnection(pC);
		//we must make Orig comp point to NULL
		pSource->DeleteNextComp(pC);
		pSource->SetNextComp(pC);
		pC->SetNextComp(pDest);
		((Connection*)pC)->SetInputNum(newinputnum);
	}
	OrigGInfo = pC->getgrap();
	pOut->DeleteConnection(OrigGInfo);
	pC->SetGraphics(GInfo);
}

void EditConnection::Undo()
{
	if (pSource == NULL || pDest == NULL) return;
	Output* pOut = pManager->GetOutput();
	GraphicsInfo GInfo; //Gfx info to be used to construct the connection
	if (outputPtr == NULL || inputPtr == NULL || pC == NULL) return;
	GInfo.x1 = x1;
	GInfo.x2 = x2;
	GInfo.y1 = y1;
	GInfo.y2 = y2;

	//if (inputPtr->GetConnectionStat() && inputPtr != OriginalInput) return;

	OrigOutputcomp = pManager->GetComp(OriginalOutput);
	

	
	if (outputPtr != OriginalOutput)
	{
		//setting original source
		OriginalOutput->ConnectTo(pC);
		OrigOutputcomp->SetNextComp(pC);
		//deleting current source
		outputPtr->DeleteConnection(pC);
		pSource->DeleteNextComp(pC);
		//setting orignial dest
		OriginalInput->SetConnectionStat(true);
		OriginalInput->SetConnection(pC);
		pC->SetNextComp(pDest);
		((Connection*)pC)->SetInputNum(oldinputnum);
		//deleting current dest
		pC->DeleteNextComp(pDest);
		inputPtr->SetConnectionStat(false);
		inputPtr->SetConnection(NULL);
	}
	pC->SetGraphics(OrigGInfo);
	pOut->ClearDrawingArea();

}

void EditConnection::Redo()
{
	Output* pOut = pManager->GetOutput();
	GraphicsInfo GInfo; //Gfx info to be used to construct the connection
	if (outputPtr == NULL || inputPtr == NULL || pC == NULL) return;
	GInfo.x1 = x1;
	GInfo.x2 = x2;
	GInfo.y1 = y1;
	GInfo.y2 = y2;
	OriginalOutput = pC->getSourcePin();
	OriginalInput = pC->getDestPin();


	if (inputPtr->GetConnectionStat() && inputPtr != OriginalInput) return;

	OrigOutputcomp = pManager->GetComp(OriginalOutput);
	OrigOutputcomp->DeleteNextComp(pC);
	inputPtr->SetConnectionStat(true);
	inputPtr->SetConnection(pC);
	if (outputPtr != OriginalOutput)
	{
		bool connected = outputPtr->ConnectTo(pC);
		if (!connected) return;
		OriginalInput->SetConnectionStat(false);
		OriginalInput->SetConnection(NULL);
		OriginalOutput->DeleteConnection(pC);
		//we must make Orig comp point to NULL
		pSource->DeleteNextComp(pC);
		pSource->SetNextComp(pC);
		pC->SetNextComp(pDest);
		((Connection*)pC)->SetInputNum(newinputnum);
	}
	OrigGInfo = pC->getgrap();
	pOut->DeleteConnection(OrigGInfo);
	pC->SetGraphics(GInfo);


}




