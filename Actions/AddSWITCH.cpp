#include "AddSWITCH.h"
#include "..\ApplicationManager.h"

AddSWITCH::AddSWITCH(ApplicationManager *pApp) :Action(pApp)
{
}

AddSWITCH::~AddSWITCH(void)
{
}

void AddSWITCH::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//Print Action Message
	pOut->PrintMsg("SWITCH component: Click to add");

	//Wait for User Input
	pIn->GetPointClicked(Cx, Cy);

	//Clear Status Bar
	pOut->ClearStatusBar();

}

void AddSWITCH::Execute()
{
	//Get Center point of the Gate
	ReadActionParameters();
	if (!CheckCoordinates(Cx, Cy)) return;
	//Calculate the rectangle Corners
	int Len = UI.AND2_Width;
	int Wdth = UI.AND2_Height;

	GraphicsInfo GInfo; //Gfx info to be used to construct the SWITCH

	GInfo.x1 = Cx - Len / 2;
	GInfo.x2 = Cx + Len / 2;
	GInfo.y1 = Cy - Wdth / 2;
	GInfo.y2 = Cy + Wdth / 2;
	AssSwitch = new SWITCH(GInfo, AND2_FANOUT);
	pManager->AddComponent(AssSwitch);
}

void AddSWITCH::Undo()
{
	pManager->DeleteGate(AssSwitch);
	Output* pOut = pManager->GetOutput();
	pOut->ClearDrawingArea();

}

void AddSWITCH::Redo()
{
	GraphicsInfo GInfo;
	int Len = UI.AND2_Width;
	int Wdth = UI.AND2_Height;
	GInfo.x1 = Cx - Len / 2;
	GInfo.x2 = Cx + Len / 2;
	GInfo.y1 = Cy - Wdth / 2;
	GInfo.y2 = Cy + Wdth / 2;
	AssSwitch = new SWITCH(GInfo, AND2_FANOUT);
	pManager->AddComponent(AssSwitch);
}

