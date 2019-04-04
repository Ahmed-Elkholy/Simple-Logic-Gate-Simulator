#include "AddLed.h"
#include "..\ApplicationManager.h"
#include "..\Components\LED.h"
AddLed::AddLed(ApplicationManager *pApp) :Action(pApp)
{
}

AddLed::~AddLed(void)
{
}

void AddLed::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//Print Action Message
	pOut->PrintMsg("Add Led: Click to add the gate");

	//Wait for User Input
	pIn->GetPointClicked(Cx, Cy);

	//Clear Status Bar
	pOut->ClearStatusBar();

}

void AddLed::Execute()
{
	//Get Center point of the Gate
	ReadActionParameters();
	if (!CheckCoordinates(Cx, Cy)) return;
	//Calculate the rectangle Corners
	int Len = UI.AND2_Width;
	int Wdth = UI.AND2_Height;

	GraphicsInfo GInfo; //Gfx info to be used to construct the AND2 gate

	GInfo.x1 = Cx - Len / 2;
	GInfo.x2 = Cx + Len / 2;
	GInfo.y1 = Cy - Wdth / 2;
	GInfo.y2 = Cy + Wdth / 2;
	AssLED = new LED(GInfo, AND2_FANOUT);
	pManager->AddComponent(AssLED);
}

void AddLed::Undo()
{
	pManager->DeleteGate(AssLED);
	Output* pOut = pManager->GetOutput();
	pOut->ClearDrawingArea();

}

void AddLed::Redo()
{
	GraphicsInfo GInfo;
	int Len = UI.AND2_Width;
	int Wdth = UI.AND2_Height;
	GInfo.x1 = Cx - Len / 2;
	GInfo.x2 = Cx + Len / 2;
	GInfo.y1 = Cy - Wdth / 2;
	GInfo.y2 = Cy + Wdth / 2;
	AssLED = new LED(GInfo, AND2_FANOUT);
	pManager->AddComponent(AssLED);
}




