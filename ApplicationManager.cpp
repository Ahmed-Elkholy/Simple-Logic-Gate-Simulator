#include "ApplicationManager.h"
#include "Actions\AddANDgate2.h"
#include"Actions\AddLed.h"
#include"Actions\AddConnection.h"
#include"Actions\EditConnection.h"
#include "Actions\AddANDgate3.h"
#include "Actions\AddBUFFgate.h"
#include "Actions\AddNANDgate2.h"
#include "Actions\AddNORgate2.h"
#include "Actions\AddNORgate3.h"
#include "Actions\AddNOTgate.h"
#include "Actions\AddORgate2.h"
#include "Actions\AddXNORgate2.h"
#include "Actions\AddXORgate2.h"
#include "Actions\AddXORgate3.h"
#include "Actions\AddSWITCH.h"
#include "Actions\Validate.h"
#include"Actions\Select.h"
#include"Actions\Move.h"
#include"Actions\Delete.h"
#include"Actions\Copy.h"
#include"Actions\Cut.h"
#include"Actions\Paste.h"
#include"Actions\AddLabel.h"
#include"Actions\EditLabel.h"
#include"Components\LED.h"
#include"Components\SWITCH.h"
#include "Actions\Simulate.h"
#include "Actions\SwitchToSim.h"
#include "Actions\SwitchToDSN.h"
#include"Actions\Probe.h"
#include"Actions\TruthTable.h"
#include"Actions\Save.h"
#include"Actions\Load.h"
#include "Actions\Undo.h"
#include "Actions\Redo.h"
#include<fstream>
using namespace std;

ApplicationManager::ApplicationManager()
{
	CompCount = 0;
	selCompCount = 0;
	for(int i=0; i<MaxCompCount; i++)
		CompList[i] = NULL;

	//Creates the Input / Output Objects & Initialize the GUI
	OutputInterface = new Output();
	InputInterface = OutputInterface->CreateInput();
	M = DESIGN;
	CopiedComponent = NULL;


}
////////////////////////////////////////////////////////////////////
void ApplicationManager::AddComponent(Component* pComp)
{
	CompList[CompCount++] = pComp;		
}
////////////////////////////////////////////////////////////////////

ActionType ApplicationManager::GetUserAction()
{
	//Call input to get what action is reuired from the user
	return InputInterface->GetUserAction(); 	
}
////////////////////////////////////////////////////////////////////

void ApplicationManager::ExecuteAction(ActionType ActType)
{
	Action* pAct = NULL;
	switch (ActType)
	{
		case ADD_AND_GATE_2:
			pAct= new AddANDgate2(this);
			break;

		case ADD_LED:
			pAct = new AddLed(this);
			break;
		case ADD_Switch:
			pAct = new AddSWITCH(this);
			break;
		case ADD_CONNECTION:
			pAct = new AddConnection(this);
			  
			break;
		case ADD_AND_GATE_3:
			pAct = new AddANDgate3(this);
			break;
		case ADD_Buff:
			pAct = new AddBUFFgate(this);
			break;
		case ADD_INV:
			pAct = new AddNOTgate(this);
			break;
		case ADD_NAND_GATE_2:
			pAct = new AddNANDgate2(this);
			break;
		case ADD_NOR_GATE_2:
			pAct = new AddNORgate2(this);
			break;
		case ADD_NOR_GATE_3:
			pAct = new AddNORgate3(this);
			break;
		case ADD_OR_GATE_2:
			pAct = new AddORgate2(this);
			break;
		case ADD_XNOR_GATE_2:
			pAct = new AddXNORgate2(this);
			break;
		case ADD_XOR_GATE_2:
			pAct = new AddXORgate2(this);
			break;
		case ADD_XOR_GATE_3:
			pAct = new AddXORgate3(this);
			break;

		case SELECT:
			pAct = new Select(this);
			break;

		case ADD_Label:
			pAct = new AddLabel(this);
			break;
		case EDIT_Label:
			pAct = new EditLabel(this);
			break;
		case EDIT_CONN:
			pAct = new EditConnection(this);
			break;
		case MOVE:
			pAct = new Move(this);
			break;
		case DEL:
			pAct = new Delete(this);
			break;
		case COPY:
			pAct = new Copy(this);
			break;
		case CUT:
			pAct = new Cut(this);
			break;
		case PASTE:
			pAct = new Paste(this);
			break;
		case ProbeTool:
			pAct = new Probe(this);
			break;
		case SIM_MODE:
			pAct = new SwitchToSim(this);
			break;
		case Simulate:
			pAct = new Simulate1(this);
			break;
		case SAVE:
			pAct = new Save1(this);
			break;
		case LOAD:
			pAct = new Load1(this);
			break;
		case DSN_MODE:
			pAct = new SwitchToDSN(this);
			break;
		case Create_TruthTable:
			pAct = new TruthTable(this);
			break;
		case UNDO:
			pAct=new Undo(this);
			break;
		case REDO:
			pAct = new Redo(this);
			break;
		case EXIT:
			///TODO: create ExitAction here
			for (int i = 0; i < CompCount; i++)
			{
				delete CompList[i];
			}
			break;
	}
	if(pAct)
	{
		pAct->Execute();
		Action *Check = dynamic_cast<Undo*>(pAct);
		Action *Check2 = dynamic_cast<Redo*>(pAct);
		if(Check==NULL &&Check2==NULL)
		UndoList.push(pAct);
		if (!(ActType == UNDO || ActType == REDO|| ActType == SELECT))
		{
			while(RedoList.size()!=0)
			RedoList.pop();
		}
		//delete pAct;
		pAct = NULL;
	}
}
////////////////////////////////////////////////////////////////////

void ApplicationManager::UpdateInterface()
{
		for (int i = 0; i < CompCount; i++)
		{
			CompList[i]->Draw(OutputInterface);
		}
	OutputInterface->UpdateBuffer();
}

////////////////////////////////////////////////////////////////////
Input* ApplicationManager::GetInput()
{
	return InputInterface;
}

////////////////////////////////////////////////////////////////////
Output* ApplicationManager::GetOutput()
{
	return OutputInterface;
}

////////////////////////////////////////////////////////////////////

Component* ApplicationManager::GetCompOfOutputPin(int &x,int &y)
{
	for (int i = 0; i < CompCount; i++)
	{
			bool found = CompList[i]->CheckIfOutpin(x, y);
			if (found)
			{
				return CompList[i];
			}
	}
	return NULL; //if not found
}
Component* ApplicationManager::GetCompOfInputPin(int &x, int &y,int &input_num)
{
	for (int i = 0; i < CompCount; i++)
	{
		    int inputnum;
			bool found = CompList[i]->CheckIfInpin(x,y,inputnum);
			if (found)
			{
				input_num = inputnum;
				return CompList[i];
			}
	}
	return NULL; //if not found
}

Component * ApplicationManager::GetSelectedComponent(int x, int y)
{
	if (selCompCount != 0)
	{
		for (int i = 0; i < selCompCount; i++)
		{

			if (SelectList[i] != NULL) SelectList[i]->SetSelectionStat(false);
			SelectList[i] = NULL;
		}
	}
	selCompCount = 0;
	for (int i = 0; i < CompCount; i++)
	{
		bool selected;
		bool found = CompList[i]->CheckIfselected(x, y, selected);
		if (selected)
		{
			DeleteSelected(CompList[i]);
			selCompCount--;
			return CompList[i];
		}
		if (found)
		{
			SelectList[selCompCount] = CompList[i];
			selCompCount++;
			return CompList[i];
		}
		/*if (dynamic_cast<Connection*>(CompList[i]))  //only for test (check if selected should be pure virtual in component class)
		{
		bool found = ((Connection*)CompList[i])->CheckIfSelected(x, y);
		if (found)
		{
		SelectList[selCompCount] = CompList[i];
		selCompCount++;
		return CompList[i];
		}
		}
		*/
	}
	for (int i = 0; i < selCompCount; i++)
	{
		SelectList[i]->SetSelectionStat(false);
		SelectList[i] = NULL;
	}
	selCompCount = 0;
	return NULL;
}
Component * ApplicationManager::GetComponent(int x, int y)
{
	for (int i = 0; i < CompCount; i++)
	{
		bool selected;
		bool found = (CompList[i])->CheckIfselected(x, y, selected);
		if (found)
		{
			return CompList[i];
		}
	}
	return NULL;
}
Component * ApplicationManager::GetFromSelectedList(int count)
{
	return SelectList[count];
}
Component* ApplicationManager::Getconnection(Pin * p) 
{

	for (int i = 0; i < CompCount; i++)
	{
		if (dynamic_cast<Connection*>(CompList[i]))
		{
			if ((CompList[i]->getinpin(1) == p))  return CompList[i];
		}
	}

	return NULL;
}
Component * ApplicationManager::GetSelectedComponent()
{
	if (selCompCount == 0 || selCompCount > 1)
	{
		return NULL;
	}
	return SelectList[0];
}
void ApplicationManager::DeleteSelected(Component *pc)
{
	int i = 0;
	while (SelectList[i] != pc && i < selCompCount)
	{
		i++;
	}
	SelectList[i] = SelectList[selCompCount - 1];
	SelectList[selCompCount - 1] = NULL;
	selCompCount--;
}


bool ApplicationManager::CheckPins()
{
	for (int i = 0; i < CompCount; i++)
	{
		if (CompList[i]->CheckPins() == false)
		{
			return false;
		}
	}
	return true;
}

void ApplicationManager::OperateAll()
{
	for (int i = 0; i < CompCount; i++)
	{
		CompList[i]->Operate();
	}
}

Component **ApplicationManager::GetSwitches(int &count)
{
    count = 0;
	Component **arrOfSwitch = new Component*[10];
	for (int i = 0; i < CompCount; i++)
	{
		if (dynamic_cast<SWITCH*>(CompList[i]))
		{
			arrOfSwitch[count] = CompList[i];
			count++;
		}

	}
	return arrOfSwitch;
}
Component **ApplicationManager::GetLEDS(int &count)
{
	count = 0;
	Component **arrOfLED=new Component*[10];
	for (int i = 0; i < CompCount; i++)
	{
		if (dynamic_cast<LED*>(CompList[i]))
		{
			arrOfLED[count] = CompList[i];
			count++;
		}
	}
	return arrOfLED;
}
bool ApplicationManager::SortLevels()
{
	for (int i = 0; i < CompCount; i++)
	{
		if (dynamic_cast<SWITCH*>(CompList[i]))   //check switch first(level 0)
		{
			SetVisitedFalse();
			SetLevels(CompList[i], 0);
		}
	}
	//now sorting according to level
	for (int i = 0; i < CompCount-1; i++)    //selection sort
	{
		int minloc = i;
		for (int j = i+1; j < CompCount; j++)
		{
			if (CompList[j]->GetLevel() < CompList[minloc]->GetLevel())
			{
				minloc = j;
			}
		}
		swap(CompList[minloc], CompList[i]);
	}
	return true;
}
void ApplicationManager::SetLevels(Component* pc,int level)  //recursive algorithm
{
	if (pc == NULL) return; //base case
	int j = 0;
	pc->SetLevel(level);
	while (pc->GetNextComp(j) != NULL)
	{
		SetLevels(pc->GetNextComp(j), pc->GetLevel()+1);
		j++;
	}
}

void ApplicationManager::SetVisitedFalse()  
{
	for (int i = 0; i < CompCount; i++)
	{
		CompList[i]->SetVisited(false);
	}
}

Component * ApplicationManager::GetComp(OutputPin * pOut)
{
	for (int i = 0; i < CompCount; i++)
	{
		if (CompList[i]->getoutpin() == pOut)
		{
			return CompList[i];
		}
	}
	return NULL; //in case if not found(rare case)
}



void ApplicationManager::Save(ofstream & Outputfile)
{
	int count = 0;
	for (int i = 0; i < CompCount; i++)
	{
		if (!dynamic_cast<Connection*>(CompList[i]))
		{
			count++;
		}
	}
	Outputfile << count<<endl;
	for (int i = 0; i < CompCount; i++)
	{
		if (!dynamic_cast<Connection*>(CompList[i]))
		{
			CompList[i]->Save(Outputfile);
		}
	}
	Outputfile << "Connections:" << endl;
	for(int i = 0; i < CompCount; i++)
	{
		if (dynamic_cast<Connection*>(CompList[i]))
		{
			CompList[i]->Save(Outputfile);
		}
	}
	Outputfile << "-1";
	Outputfile.close();
}
void ApplicationManager::Load(ifstream & Inputfile)
{
	DeleteAll();
	CompCount = 0;
	int count = 0;
	Inputfile >> count;
	for (int i = 0; i < count; i++)
	{
		string type;
		Inputfile >> type;
		Component *pc;
		if (type== "AND2")
			pc = new AND2(AND2_FANOUT);
		else if(type == "LED")
			pc = new LED(AND2_FANOUT);
		else if (type == "SWITCH")
			pc = new SWITCH(AND2_FANOUT);
		else if (type == "AND3")
			pc = new AND3(AND2_FANOUT);
		else if (type == "BUFF")
		    pc = new BUFF(AND2_FANOUT);
		else if (type == "NOT")
			pc = new NOT(AND2_FANOUT);
		else if (type == "NAND2")
			pc = new NAND2(AND2_FANOUT);
		else if (type == "OR2")
			pc = new OR2(AND2_FANOUT);
		else if (type == "NOR2")
			pc = new NOR2(AND2_FANOUT);
		else if (type == "NOR3")
			pc = new NOR3(AND2_FANOUT);
		else if (type == "XNOR2")
			pc = new XNOR2(AND2_FANOUT);
		else if (type == "XOR2")
			pc = new XOR2(AND2_FANOUT);
		else if (type == "XOR3")
			pc = new XOR3(AND2_FANOUT);
		pc->load(Inputfile);
		AddComponent(pc);
	}
	string ff;
	Inputfile >> ff;
	int SourceID;
	int DestID;
	int inputnum;
	Inputfile >> SourceID;
	Inputfile >> DestID;
	Inputfile >> inputnum;

	while (SourceID!=-1)
	{
		GraphicsInfo gfxConn;
		Component * pSource = findComponent(SourceID);
		GraphicsInfo gfxSource = pSource->getgrap();
        gfxConn.x1 = gfxSource.x1 + UI.AND2_Width - 3;
		gfxConn.y1 = gfxSource.y1 + 24;
		Component * pDst = findComponent(DestID);
		int xdest, ydest;
		pDst->GetinputPinCoordinates(inputnum,xdest,ydest);
		gfxConn.x2 = xdest;
		gfxConn.y2 = ydest;


		OutputPin *pinSource = pSource->getoutpin();
		InputPin *pinDest = pDst->getinpin(inputnum);
		Connection *pconn = new Connection(gfxConn, pinSource, pinDest);
		pinDest->SetConnection(pconn);
		pinDest->SetConnectionStat(true);
		pinSource->ConnectTo(pconn);
		pSource->SetNextComp(pconn);
		pconn->SetNextComp(pDst);
		AddComponent(pconn);
		Inputfile >> SourceID;
		Inputfile >> DestID;
		Inputfile >> inputnum;
	}
}

Component *ApplicationManager::findComponent(int ID)
{
	for (int i = 0; i < CompCount; i++)
	{
		if (CompList[i]->GetID() == ID)
			return CompList[i];
	}
	return NULL;
}

void ApplicationManager::DeleteAll()
{
	for (int i = 0; i < CompCount; i++)
		delete CompList[i];

}



void ApplicationManager::SetValidation(bool flag)
{
	validated = flag;
}

bool ApplicationManager::GetValidation() const
{
	return validated;
}

void  ApplicationManager::SetSimulation(MODE _M)
{
	M = _M;
}

void ApplicationManager::setCopied(Component* Cop)
{
	CopiedComponent = Cop;

}
Component* ApplicationManager::getCopied()
{
	return CopiedComponent;
}

void ApplicationManager::DeleteCopy()
{
	delete CopiedComponent;
	CopiedComponent = NULL;
}


ApplicationManager::~ApplicationManager()
{
	for(int i=0; i<CompCount; i++)
		delete CompList[i];
	delete OutputInterface;
	delete InputInterface;
	
}

/*void ApplicationManager::Undo()
{
		Action *pA=UndoList.top();
		pA->Undo();
		RedoList.push(pA);
		UndoList.pop();
}*/

Action* ApplicationManager::getUndoTop()
{
	Action* pA = UndoList.top(); //law fady hay return eh?
	return pA;
}
stack<Action*>* ApplicationManager::getUndoList()
{
	stack<Action*>* PUndo = &UndoList;
	return PUndo;
}
stack<Action*>* ApplicationManager::getRedoList()
{
	stack<Action*>* PRedo = &RedoList;
	return PRedo;
}

Action* ApplicationManager::getRedoTop()
{
	Action* pA = RedoList.top();
	return pA;
}
void ApplicationManager::decselcted() {
	selCompCount--;
}

Component** ApplicationManager::Sortsel(int &x1, int &y1, int &count)
{
	if (selCompCount == 0) return NULL;
	count = selCompCount;
	int cnt = 0;
	//int concnt = 0;
	for (int i = 0; i < count; i++)
	{
		for (int j = i + 1; j < count; j++)

		{
			if (SelectList[i]->getgrap().x1 > SelectList[j]->getgrap().x1)
			{
				Component* t = SelectList[i];
				SelectList[i] = SelectList[j];
				SelectList[j] = t;
			}
		}
	}

	for (int i = 0; i < count; i++)
	{
		for (int j = i + 1; j < count; j++)
		{
			if (dynamic_cast<Connection*>(SelectList[i]) != NULL)
			{
				Component* t = SelectList[i];
				SelectList[i] = SelectList[j];
				SelectList[j] = t;
			}
		}
	}

	for (int i = 0; i < count; i++)
	{
		if (dynamic_cast<Connection*> (SelectList[i]) == NULL)
		{
			cnt++;
		}
		//else concnt++;
	}
	x1 = SelectList[0]->getgrap().x1;
	y1 = SelectList[0]->getgrap().y1;
	//if(type)
	count = cnt;
	//else count = concnt;
	Component** c = new Component*[cnt];
	for (int i = 0; i < cnt; i++)
	{
		c[i] = SelectList[i];
	}
	return  c;
}


void ApplicationManager::deletegate(InputPin* in1, InputPin* in2, InputPin* in3, OutputPin* out, Component* pc)
{
		for (int i = 0; i < CompCount; i++)
		{
			if (dynamic_cast <Connection* >(CompList[i]))
			{
				if (CompList[i]->getinpin(1) == in1 || CompList[i]->getinpin(1) == in2 || CompList[i]->getinpin(1) == in3)
				{
					CompList[i]->getinpin(1)->setStatus(LOW);   //to be removed (has no meaning)
					CompList[i]->getoutpin()->DeleteConnection((Connection*)CompList[i]);
					CompList[i]->getinpin(1)->SetConnectionStat(false);
					delete CompList[i];
					CompList[i] = CompList[CompCount - 1];
					CompList[CompCount--] = NULL;
					i--;
				}
				else if (CompList[i]->getoutpin() == out)
				{
					delete CompList[i];
					CompList[i] = CompList[CompCount - 1];
					CompList[i]->getinpin(1)->SetConnectionStat(false);
					CompList[--CompCount] = NULL;
					i--;
				}
			}
			else {
				if (CompList[i] == pc)
				{
					delete CompList[i];
					CompList[i] = CompList[CompCount - 1];
					CompList[--CompCount] = NULL;
					i--;
				}
			}
		}
}


void ApplicationManager::RemoveGate(InputPin* in1, InputPin* in2, InputPin* in3, OutputPin* out, Component* pc)
{
	for (int i = 0; i < CompCount; i++)
	{
		if (dynamic_cast <Connection* >(CompList[i]))
		{
			if (CompList[i]->getinpin(1) == in1 || CompList[i]->getinpin(1) == in2 || CompList[i]->getinpin(1) == in3)
			{
				CompList[i]->getinpin(1)->setStatus(LOW);   //to be removed (has no meaning)
				CompList[i]->getoutpin()->DeleteConnection((Connection*)CompList[i]);
				CompList[i]->getinpin(1)->SetConnectionStat(false);
				delete CompList[i];
				CompList[i] = CompList[CompCount - 1];
				CompList[CompCount--] = NULL;
				i--;
			}
			else if (CompList[i]->getoutpin() == out)
			{
				delete CompList[i];
				CompList[i] = CompList[CompCount - 1];
				CompList[--CompCount] = NULL;
				i--;
			}
		}
		else {
			if (CompList[i] == pc)
			{
				delete CompList[i];
				CompList[i] = CompList[CompCount - 1];
				CompList[--CompCount] = NULL;
				i--;
			}
		}
	}
}

void  ApplicationManager::GetSelComponent(int x1, int y1, int x2, int y2)
{
	int cnt = 0;
	for (int i = 0; i < selCompCount; i++)
	{
		if (SelectList[i] != NULL) SelectList[i]->SetSelectionStat(false);
		SelectList[i] = NULL;

	}
	selCompCount = 0;
	for (int i = 0; i < CompCount; i++)


	{

		int xc1 = CompList[i]->getgrap().x1;
		int xc2 = CompList[i]->getgrap().x2;
		int yc1 = CompList[i]->getgrap().y1;
		int yc2 = CompList[i]->getgrap().y2;
		//if (dynamic_cast<Gate*> (CompList[i]))
		//{
		if (xc1 >= x1&& yc1 >= y1 && xc2 <= x2 && yc2 <= y2)
		{
			SelectList[selCompCount++] = CompList[i];
			CompList[i]->SetSelectionStat(true);
			cnt++;
		}
		//}

	}
	if (cnt == 0)
	{
		for (int i = 0; i < selCompCount; i++)
		{
			if (SelectList[i] != NULL) SelectList[i]->SetSelectionStat(false);
			SelectList[i] = NULL;
		}
		selCompCount = 0;
	}

}


void ApplicationManager::RemoveGate(Component* ToDelete)
{
	for (int i = 0; i < CompCount; i++)
	{
		if (CompList[i] == ToDelete)
		{
			CompList[i] = CompList[CompCount - 1];
			CompList[CompCount - 1] = NULL;
			CompCount--;
			return;
		}
	}
}


void ApplicationManager::DeleteGate(Component* ToDelete)
{
	for (int i = 0; i < CompCount; i++)
	{
		if (CompList[i] == ToDelete)
		{
			delete CompList[i];
			CompList[i] = CompList[CompCount - 1];
			CompList[CompCount - 1] = NULL;
			CompCount--;
			selCompCount = 0;
			return;
		}
	}
}

void ApplicationManager::SetClipBoardStatus(bool flag)
{
	CutOrCopy = flag;
}

bool ApplicationManager::GetClipBoardStatus()
{
	return CutOrCopy;
}

Component** ApplicationManager::getsortlist(int & count)
{
	int gate = 0;
	int con = 0;
	count = selCompCount;
	for (int i = 0; i < count; i++)
	{
		for (int j = i + 1; j < count; j++)

		{
			if (SelectList[i]->getgrap().x1 > SelectList[j]->getgrap().x1)
			{
				Component* t = SelectList[i];
				SelectList[i] = SelectList[j];
				SelectList[j] = t;
			}
		}
	}

	for (int i = 0; i < count; i++)
	{
		for (int j = i + 1; j < count; j++)
		{
			if (dynamic_cast<Connection*>(SelectList[i]) != NULL)
			{
				Component* t = SelectList[i];
				SelectList[i] = SelectList[j];
				SelectList[j] = t;
			}
		}
	}
	for (int i = 0; i < count; i++)
	{
		if (dynamic_cast<Connection*> (SelectList[i]) == NULL)
		{
			gate++;
		}
		else con++;
	}
	if (gate == 0) count = con;
	else {
		count = gate;
		selCompCount -= con;
	}
	return SelectList;
}