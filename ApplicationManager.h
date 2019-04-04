#ifndef APPLICATION_MANAGER_H
#define APPLICATION_MANAGER_H

#include "Defs.h"
#include "GUI\Output.h"
#include "GUI\Input.h"
#include "Actions\Action.h"
#include "Components\Component.h"
#include"Actions\AddConnection.h"
#include<iostream>
#include<stack>
using namespace std;
//Main class that manages everything in the application.
class ApplicationManager
{

	enum { MaxCompCount = 200 };	//Max no of Components	

private:
	int CompCount;		//Actual number of Components
	int selCompCount;
	Component* CompList[MaxCompCount];	//List of all Components (Array of pointers)
	Component* SelectList[MaxCompCount]; //Array of selected Components
	Component* SimList[MaxCompCount];
	Output* OutputInterface; //pointer to the Output Clase Interface
	Input* InputInterface; //pointer to the Input Clase Interface
	MODE M;
	bool validated;
	Component* CopiedComponent;
	bool CutOrCopy;    //true copy false cut
	stack <Action*> UndoList;
	stack <Action*> RedoList;
public:	
	ApplicationManager(); //constructor

	//Reads the required action from the user and returns the corresponding action type
	ActionType GetUserAction();
	Action* getUndoTop();
	Action* getRedoTop();
	stack<Action*>* getUndoList();
	stack<Action*>* getRedoList();
	//Creates an action and executes it
	void ExecuteAction(ActionType);
	void DeleteGate(Component*);
	void RemoveGate(Component*);
	void UpdateInterface();	//Redraws all the drawing window
	void DeleteAll();

	//Gets a pointer to Input / Output Object
	Output* GetOutput();
	Input* GetInput();

	//Adds a new component to the list of components
	void AddComponent(Component* pComp);

	Component* GetCompOfOutputPin(int &x, int &y);
	Component* GetCompOfInputPin(int &x, int &y, int &input_num);
	Component * GetSelectedComponent(int x, int y);
	Component * GetComponent(int x, int y);
	Component * GetSelectedComponent();
	Component * GetFromSelectedList(int x, int y);
	Component * GetComp(OutputPin * pOut);
	Component * GetFromSelectedList(int count);
	Component* Getconnection(Pin * p);
	Component** GetSwitches(int &count);
    Component** GetLEDS(int &count);
	void SetLevels(Component* pc, int level);
	void SetLevels(Component* pc);
	void SetVisitedFalse();
	void DeleteSelected(Component *);
	void Load(ifstream& Input);
	void Save(ofstream& Output);
	bool GetClipBoardStatus();
	void SetClipBoardStatus(bool flag);
	int getcount(){ return CompCount; } //here too
	int getSelectcount() { return selCompCount; }
	bool CheckPins();
	bool SortLevels();
	void SetValidation(bool flag);
	bool GetValidation() const;
	void OperateAll();
	//void Undo();
	void SetSimulation(MODE _M);
	Component *findComponent(int ID);
	void setCopied(Component*);
	Component* getCopied();
	void DeleteCopy();
	void RemoveGate(InputPin* in1, InputPin* in2, InputPin* in3, OutputPin* out, Component* pc);
	void deletegate(InputPin* in1, InputPin* in2, InputPin* in3, OutputPin* out, Component* pc);
	void deletecon(Connection * pc)
	{
		for (int i = 0; i < CompCount; i++)
		{
			if (CompList[i] == pc) {
				pc->getinpin(1)->setStatus(LOW);
				pc->getinpin(1)->SetConnectionStat(false);
				CompList[i]->getoutpin()->DeleteConnection((Connection*)(CompList[i]));
				delete CompList[i];
				CompList[i] = CompList[CompCount - 1];
				CompList[CompCount--] = NULL;
			}
		}
	}
	void decselcted();
	void GetSelComponent(int x1, int y1, int x2, int y2);
	Component**getsortlist(int & count);
	Component** Sortsel(int &x1, int &y1, int &count);// true for move false for delete;
	~ApplicationManager();
};

#endif