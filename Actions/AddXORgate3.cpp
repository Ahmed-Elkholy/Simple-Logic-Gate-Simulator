#include "AddXORgate3.h"
#include "..\ApplicationManager.h"

AddXORgate3::AddXORgate3(ApplicationManager *pApp) :Action(pApp)
{
}

AddXORgate3::~AddXORgate3(void)
{
}

void AddXORgate3::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//Print Action Message
	pOut->PrintMsg("3-Input XOR Gate: Click to add the gate");

	//Wait for User Input
	pIn->GetPointClicked(Cx, Cy);

	//Clear Status Bar
	pOut->ClearStatusBar();

}

void AddXORgate3::Execute()
{
	//Get Center point of the Gate
	ReadActionParameters();
	if (!CheckCoordinates(Cx, Cy)) return;
	//Calculate the rectangle Corners
	int Len = UI.AND2_Width;
	int Wdth = UI.AND2_Height;

	GraphicsInfo GInfo; //Gfx info to be used to construct the XOR3 gate

	GInfo.x1 = Cx - Len / 2;
	GInfo.x2 = Cx + Len / 2;
	GInfo.y1 = Cy - Wdth / 2;
	GInfo.y2 = Cy + Wdth / 2;
	AssGate = new XOR3(GInfo, AND2_FANOUT);
	pManager->AddComponent(AssGate);
}

void AddXORgate3::Undo()
{
	pManager->DeleteGate(AssGate);
	Output* pOut = pManager->GetOutput();
	pOut->ClearDrawingArea();

}

void AddXORgate3::Redo()
{
	GraphicsInfo GInfo;
	int Len = UI.AND2_Width;
	int Wdth = UI.AND2_Height;
	GInfo.x1 = Cx - Len / 2;
	GInfo.x2 = Cx + Len / 2;
	GInfo.y1 = Cy - Wdth / 2;
	GInfo.y2 = Cy + Wdth / 2;
	AssGate = new XOR3(GInfo, AND2_FANOUT);
	pManager->AddComponent(AssGate);
}
