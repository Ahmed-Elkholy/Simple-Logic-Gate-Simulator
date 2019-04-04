#include "TruthTable.h"
#include "..\ApplicationManager.h"
#include"..\Components\LED.h"
#include"..\Components\SWITCH.h"
#include<iostream>
#include<cmath>
using namespace std;
TruthTable::TruthTable(ApplicationManager *pApp):Action(pApp)
{
}

TruthTable::~TruthTable(void)
{
}

void TruthTable::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	Outputfile.open("TruthTable.txt");
	//Print Action Message
	pOut->PrintMsg("Generating TruthTable");

	//Wait for User Input
	//pIn->GetPointClicked(Cx, Cy);

	//Clear Status Bar
	pOut->ClearStatusBar();
	
}

void TruthTable::Execute()
{
	//Get Center point of the Gate
	ReadActionParameters();
	Output* pOut = pManager->GetOutput();

	int SwitchCount;
	int LEDCount;
	Component ** Switches=pManager->GetSwitches(SwitchCount);
	Component ** LEDS=pManager->GetLEDS(LEDCount);
	int n = SwitchCount;
	int** arrOfTB = new int*[n];
	for (int i = 0; i < n; i++)
	{
		arrOfTB[i] = new int[(int)pow(2,n)];
	}
	for (int i = 0; i < n; i++)
	{
		int j = 0;
		while (j != pow(2,n))
		{
			for (int k = 0; k < pow(2,i); k++)
			{
				arrOfTB[i][j] = 0;
				j++;
			}
			for (int k = 0; k < pow(2, i); k++)
			{
				arrOfTB[i][j] = 1;
				j++;
			}
		}
	}
	window *wind=pOut->CreateWind(1000, 2000, 1, 1);
	wind->SetFont(20, BOLD | ITALICIZED, BY_NAME, "Arial");
	wind->SetPen(UI.MsgColor);
	int y = 20;
	int x = 1;
	for (int i = 0; i < pow(2, n); i++)
	{
		x = 1;
		for (int j = 0; j < SwitchCount; j++)
		{
			((SWITCH*)Switches[j])->SetStatus(!arrOfTB[n-j-1][i]);
			Outputfile << arrOfTB[n-j-1][i] << "\t";
			wind->DrawInteger(x, y, arrOfTB[n - j - 1][i]);
			x = x + 30;
		}
		pManager->OperateAll();
		for (int i = 0; i < LEDCount; i++)
		{
			Outputfile << "\t\t";
			Outputfile << ((LED*)LEDS[i])->GetStatus()<<"\t";
			wind->DrawInteger(x, y, LEDS[i]->GetInputPinStatus(1));
			x = x + 30;
		}
		Outputfile << "\n";
		y += 20;
	}
	wind->WaitMouseClick(x,y);
	delete wind;
	for (int j = 0; j < SwitchCount; j++)
	{
		((SWITCH*)Switches[j])->SetStatus(true);
	}
	Outputfile.close();
}

void TruthTable::Undo()
{}

void TruthTable::Redo()
{}

