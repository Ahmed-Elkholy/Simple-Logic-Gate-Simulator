#include "Load.h"
#include "..\ApplicationManager.h"
#include<iostream>
#include<fstream>
Load1::Load1(ApplicationManager *pApp):Action(pApp)
{
}

Load1::~Load1(void)
{
}

void Load1::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	Inputfile.open("halfadder.txt");
	//Print Action Message
	

	//Clear Status Bar
	pOut->ClearStatusBar();
	
}

void Load1::Execute()
{
	//Get Center point of the Gate
	ReadActionParameters();
	pManager->Load(Inputfile);

}

void Load1::Undo()
{}

void Load1::Redo()
{}

