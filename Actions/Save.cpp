#include "Save.h"
#include "..\ApplicationManager.h"
#include<iostream>

using namespace std;
Save1::Save1(ApplicationManager *pApp):Action(pApp)
{
}

Save1::~Save1(void)
{
}

void Save1::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	Outputfile.open("Save.txt");
	//Print Action Message
	//pOut->PrintMsg("2-Input AND Gate: Click to add the gate");

	//Wait for User Input
	//pIn->GetPointClicked(Cx, Cy);

	//Clear Status Bar
	pOut->ClearStatusBar();
	
}

void Save1::Execute()
{
	//Get Center point of the Gate
	ReadActionParameters();
	pManager->Save(Outputfile);
}

void Save1::Undo()
{}

void Save1::Redo()
{}

