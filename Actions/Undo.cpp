#include "Undo.h"
#include "Move.h"
#include "../ApplicationManager.h"

Undo::Undo(ApplicationManager *pApp) :Action(pApp)
{
}

Undo::~Undo(void)
{
}

void Undo::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//Clear Status Bar
	pOut->ClearStatusBar();

}

void Undo::Execute()
{
	stack<Action*>* PUndo = pManager->getUndoList();
	if (PUndo->size() == 0) return;
	Action *pA = PUndo->top();
	pA->Undo();
	stack<Action*>* PRedo = pManager->getRedoList();
	PRedo->push(pA);
	PUndo->pop();

}





