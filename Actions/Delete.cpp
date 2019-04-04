
#include "Delete.h"
#include "Move.h"
#include "..\ApplicationManager.h"
#include"..\Components\LED.h"
#include"..\Components\SWITCH.h"
Delete::Delete(ApplicationManager *pApp) :Action(pApp)
{
}

Delete::~Delete(void)
{
}

void Delete::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//Print Action Message
	pOut->PrintMsg("Delete Selected components");

	//Wait for User Input
	//pIn->GetPointClicked(Cx, Cy);

	//Clear Status Bar
	pOut->ClearStatusBar();

}

void Delete::Execute()
{
	//Get Center point of the Gate
	ReadActionParameters();
	//Component* pc = pManager->GetFromSelectedList(Cx, Cy);
	int count;
	Component** c = pManager->getsortlist(count);
	delcnt = count;
	del = new Component*[count];
	for (int i = 0; i < count; i++)
	{
		del[i] = c[i]->Copy();
		if (dynamic_cast<Connection*> (c[i]) == NULL)
			del[i]->SetGraphics(c[i]->getgrap().x1 + 25, c[i]->getgrap().y1 + 25, true);

	}
	if (c == NULL || count == 0) return;
	for (int i = 0; i < count; i++)
	{
		if (dynamic_cast<Connection*>(c[i]) == NULL) {
			InputPin* in1;
			InputPin * in2;
			InputPin* in3;
			OutputPin* out;
			if (dynamic_cast<SWITCH*>(c[i]))
			{
				in1 = NULL; in2 = NULL; in3 = NULL;
				out = c[i]->getoutpin();
			}

			else if (dynamic_cast<LED*>(c[i])) {
				out = NULL;
				in1 = c[i]->getinpin(1);
				in2 = c[i]->getinpin(2);
				in3 = c[i]->getinpin(3);
			}
			else if (dynamic_cast<Gate*>(c[i]))
			{
				out = c[i]->getoutpin();
				in1 = c[i]->getinpin(1);
				in2 = c[i]->getinpin(2);
				in3 = c[i]->getinpin(3);
			}
			pManager->deletegate(in1, in2, in3, out, c[i]);
			//out->Deletecon();
			pManager->GetOutput()->ClearDrawingArea();
			pManager->UpdateInterface();
			pManager->decselcted();
		}
		else {
			pManager->deletecon(((Connection*)(c[i])));
			pManager->GetOutput()->ClearDrawingArea();
			pManager->UpdateInterface();
			pManager->decselcted();
		}
	}
}

void Delete::Undo()
{
	for (int i = 0; i < delcnt; i++)
	{
		pManager->AddComponent(del[i]);
	}
}

void Delete::Redo()
{}



