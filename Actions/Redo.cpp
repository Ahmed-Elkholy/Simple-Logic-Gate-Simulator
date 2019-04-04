#include "Redo.h"
#include "../ApplicationManager.h"

Redo::Redo(ApplicationManager *pApp) :Action(pApp)
{
}

Redo::~Redo(void)
{
}

void Redo::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//Clear Status Bar
	pOut->ClearStatusBar();

}

void Redo::Execute()
{
	stack<Action*>* PRedo = pManager->getRedoList(); //ana 7ases eno ama beye3mel pop w push mesh beyghayar el count aw haga
	if (PRedo->size() == 0) return;
	Action *pA = PRedo->top();
	pA->Redo();
	stack<Action*>* PUndo = pManager->getUndoList();
	PUndo->push(pA);
	PRedo->pop();

}



