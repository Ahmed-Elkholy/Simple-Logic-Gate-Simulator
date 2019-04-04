#include "AddConnection.h"
#include "..\ApplicationManager.h"
AddConnection::AddConnection(ApplicationManager *pApp) :Action(pApp)
{
	pSource = NULL;
	pDest = NULL;
}

AddConnection::~AddConnection(void)
{
}

void AddConnection::ReadActionParameters() //under construction
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//Print Action Message
	pOut->PrintMsg("Add connection: Click to add connection");
	//Wait for User Input
		pIn->GetPointClicked(x1, y1);
	    pSource = pManager->GetCompOfOutputPin(x1,y1);
		if (pSource == NULL) return;
	//moving check coordinates?
		pOut->PrintMsg("Click on the second pin");
		pIn->GetPointClicked(x2, y2);
		pDest = pManager->GetCompOfInputPin(x2,y2,inputnum);
		if (pDest == NULL) return;
		outputPtr = pSource->getoutpin();
		inputPtr = pDest->getinpin(inputnum);
	//Clear Status Bar
	pOut->ClearStatusBar();

}
void AddConnection::Execute() //under construction
{
	ReadActionParameters();
	GInfo; //Gfx info to be used to construct the connection
	if (pSource == NULL || pDest == NULL) return;
	GInfo.x1 = x1;
	GInfo.x2 = x2;
	GInfo.y1 = y1;
	GInfo.y2 = y2;

	pC = new Connection(GInfo, outputPtr, inputPtr);
	if (inputPtr->GetConnectionStat()) return;
	inputPtr->SetConnectionStat(true);
	bool connected=outputPtr->ConnectTo(pC);
	if (!connected) return;
	inputPtr->SetConnection(pC);
	pSource->SetNextComp(pC);
	pC->SetNextComp(pDest);
	((Connection*)pC)->SetInputNum(inputnum);
	//pSource->SetNextComp(pDest);
	pManager->AddComponent(pC);
}
/*
Wael's function(to be edited)
void AddConnection::Execute()
{
	//Get Center point of the Gate
	ReadActionParameters();

	//Calculate the rectangle Corners
	int Len = UI.AND2_Width;
	int Wdth = UI.AND2_Height;

	GraphicsInfo GInfo; //Gfx info to be used to construct the AND2 gate

	GInfo.x1 = x1;
	GInfo.x2 = x2;
	GInfo.y1 = y1;
	GInfo.y2 = y2;
	int compn = pManager->getcount();
	Component** c= pManager->getlist();
	//if (count == 0)
	//{   
		/////////pA = new Connection(GInfo, c[0]->getoutpin(), c[0]->getinpin(1));
	Connection*pA = new Connection(GInfo, NULL, NULL);
	for (int i = 0; i <compn; i++)
	{
		if (dynamic_cast<Connection *> (c[i])==NULL)
		{
			if (dynamic_cast<AND2 *> (c[i])!=NULL)
			{
				if (x1 >= c[i]->getgrap().x1 + Len / 2 && x1 <= c[i]->getgrap().x1 + Len && y1 >= c[i]->getgrap().y1 && y1 <= c[i]->getgrap().y1 + Wdth)
				{
					pA->setSourcePin(c[i]->getoutpin());
					STATUS s = (c[i]->GetOutPinStatus() == 1 ? HIGH : LOW);
					pA->setInputPinStatus(1, s);
				}

				if (x2 >= c[i]->getgrap().x1  && x2 <= c[i]->getgrap().x1 + Len / 2 && y2 >= c[i]->getgrap().y1 && y2 <= c[i]->getgrap().y1 + Wdth / 2)
				{
					pA->setDestPin(c[i]->getinpin(1));
					//pA->setInputPinStatus(1, HIGH);
					if (pA->getSourcePin() == NULL) c[i]->setInputPinStatus(1, HIGH);
				else {
					STATUS s = (pA->GetOutPinStatus() == 1 ? HIGH : LOW);
					c[i]->setInputPinStatus(1, s);
				}
				}

				else if (x2 >= c[i]->getgrap().x1  && x2 <= c[i]->getgrap().x1 + Len / 2 && y2 >= c[i]->getgrap().y1+Wdth/2 && y2 <= c[i]->getgrap().y1 + Wdth)
				{
					pA->setDestPin(c[i]->getinpin(2));
					//pA->setInputPinStatus(1, HIGH);
					if (pA->getSourcePin() == NULL) c[i]->setInputPinStatus(2, HIGH);
					else {
						STATUS s = (pA->GetOutPinStatus() == 1 ? HIGH : LOW);
						c[i]->setInputPinStatus(2, s);
					}
				}
			}
			else if (dynamic_cast<LED*> (c[i])!=NULL)
			{
				if (x2 >= c[i]->getgrap().x1  && x2 <= c[i]->getgrap().x1 + Len  && y2 >= c[i]->getgrap().y1 && y2 <= c[i]->getgrap().y1 + Wdth)
				{
					pA->setDestPin(c[i]->getinpin(1));
					//pA->setInputPinStatus(1, HIGH);
					if (pA->getSourcePin() == NULL) c[i]->setInputPinStatus(1, HIGH);
					else
					{
						STATUS s = (pA->GetOutPinStatus() == 1 ? HIGH : LOW);
						c[i]->setInputPinStatus(1, s);
					}
				}
			}
		}
	}
	pManager->AddComponent(pA);
}
*/
void AddConnection::Undo()
{
	Output* pOut = pManager->GetOutput();
	if (pSource == NULL || pDest == NULL) return;
	inputPtr->SetConnectionStat(false);
	outputPtr->DeleteConnection(pC);
	inputPtr->SetConnection(NULL);
	pSource->DeleteNextComp(pC);
	pC->SetNextComp(pDest);
	pManager->deletecon(pC);
	pOut->ClearDrawingArea();
}

void AddConnection::Redo()
{
	if (pSource == NULL || pDest == NULL) return;
	pC = new Connection(GInfo, outputPtr, inputPtr);
	if (inputPtr->GetConnectionStat()) return;
	inputPtr->SetConnectionStat(true);
	bool connected = outputPtr->ConnectTo(pC);
	if (!connected) return;
	inputPtr->SetConnection(pC);
	pSource->SetNextComp(pC);
	pC->SetNextComp(pDest);
	((Connection*)pC)->SetInputNum(inputnum);
	//pSource->SetNextComp(pDest);
	pManager->AddComponent(pC);


}




