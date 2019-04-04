#include "Input.h"/////////////////////////////kant comment ha;
#include "Output.h"

Input::Input(window* pW)
{
	pWind = pW; //point to the passed window
}

void Input::GetPointClicked(int &x, int &y)
{
	pWind->FlushMouseQueue();
	pWind->WaitMouseClick(x, y);	//Wait for mouse click
}

string Input::GetString(Output *pOut)
{
		///TODO: Implement this Function
	pWind->FlushKeyQueue();
		string s;
		char c;
		int count = 0;
		pWind->WaitKeyPress(c);
		while (c != '\r')  //Enter character
		{
			if (c != '\b') //Backspace
			{
				s.push_back(c);
				count++;
			}
			else if (count != 0)
			{
				s.pop_back();
				count--;
			}
			if (c == '\x1') //Escape character
			{
				return std::string();
			}
			pOut->PrintMsg(s);
			pWind->WaitKeyPress(c);
		}
		//Read a complete string from the user until the user presses "ENTER".
		//If the user presses "ESCAPE". This function should return an empty string.
		//"BACKSPACE" should be also supported
		//User should see what he is typing at the status bar
		return s;
}

//This function reads the position where the user clicks to determine the desired action
ActionType Input::GetUserAction() const
{	
	int x,y;
	pWind->WaitMouseClick(x, y);	//Get the coordinates of the user click

	if(UI.AppMode == DESIGN )	//application is in design mode
	{
		//[1] If user clicks on the Toolbar
		if ( y >= 0 && y < UI.ToolBarHeight/2)
		{	
			//Check whick Menu item was clicked
			//==> This assumes that menu items are lined up horizontally <==
			int ClickedItemOrder = (x / UI.ToolItemWidth);
			//Divide x coord of the point clicked by the menu item width (int division)
			//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

			switch (ClickedItemOrder)
			{
			case ITM_AND2: return ADD_AND_GATE_2;
			case ITM_OR2: return ADD_OR_GATE_2;
			case ITM_XOR2: return ADD_XOR_GATE_2;
			case ITM_NOT: return ADD_INV;
			case ITM_BUF: return ADD_Buff;
			case ITM_NAND2: return ADD_NAND_GATE_2;
			case ITM_XNOR2: return ADD_XNOR_GATE_2;
			case ITM_NOR2: return ADD_NOR_GATE_2;
			case ITM_AND3: return ADD_AND_GATE_3;
			case ITM_XOR3: return ADD_XOR_GATE_3;
			case ITM_NOR3: return ADD_NOR_GATE_3;
			case ITM_SWITCH_OPENED: return ADD_Switch;
			case ITM_LED: return ADD_LED;
			case ITM_UNDO: return UNDO;


			default: return DSN_TOOL;	//A click on empty place in desgin toolbar
			}
		}
		if (y >=UI.ToolBarHeight / 2 && y<UI.ToolBarHeight)
		{
			//Check whick Menu item was clicked
			//==> This assumes that menu items are lined up horizontally <==
			int ClickedItemOrder = (x / UI.ToolItemWidth)+14;
			//Divide x coord of the point clicked by the menu item width (int division)
			//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

			switch (ClickedItemOrder)
			{
			case ITM_REDO: return REDO;
			case ITM_CONN: return ADD_CONNECTION;
			case ITM_LABEL: return ADD_Label;
			case ITM_DELETE: return DEL;
			case ITM_SAVE: return SAVE;
			case ITM_EDITLABEL:return EDIT_Label;
			case ITM_EDITCONN:return EDIT_CONN;
			case ITM_LOAD: return LOAD;
			case ITM_COPY: return COPY;
			case ITM_CUT: return CUT;
			case ITM_PASTE: return PASTE;
			case ITM_SIMU: return SIM_MODE;
			case ITM_MOVE: return MOVE;
			case ITM_EXIT: return EXIT;
			default: return DSN_TOOL;	//A click on empty place in desgin toolbar
			}
		}
	
		//[2] User clicks on the drawing area
		if ( y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
		{
			return SELECT;	//user want to select/unselect a statement in the flowchart
		}
		
		//[3] User clicks on the status bar
		return STATUS_BAR;
	}
	else	//Application is in Simulation mode
	{
		if (y >= 0 && y < UI.ToolBarHeight)
		{
			//Check whick Menu item was clicked
			//==> This assumes that menu items are lined up horizontally <==
			int ClickedItemOrder = (x / UI.ToolItemWidth);
			//Divide x coord of the point clicked by the menu item width (int division)
			//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on
		switch (ClickedItemOrder)
		{
		case ITM_VAL: return Check_Validate;
		case ITM_SIM: return Simulate;
		case ITM_TRUTH: return Create_TruthTable;
		case ITM_PROBE: return ProbeTool;
		case ITM_DESIGN: return DSN_MODE;
		case ITM_EXITSIM: return EXIT;
		default: return SIM_TOOL;	//A click on empty place in desgin toolbar

		}
	}
		else if (y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
		{
			//return SELECT;	//user want to select/unselect a statement in the flowchart
		}

		//[3] User clicks on the status bar
		return STATUS_BAR;//This should be changed after creating the compelete simulation bar 
    }
		return SIM_MODE;	//This should be changed after creating the compelete simulation bar 
}
void Input::CheckCoordinates(int &x, int &y, Output * pOut, int type)
{
	if (type==0) {
		if (y<UI.ToolBarHeight+3 || y + UI.AND2_Height>UI.height - UI.StatusBarHeight) //component check=0
		{
			pOut->PrintMsg("Error! Draw only in the design area , Click anywhere");
			//GetPointClicked(x, y);
		}
		pOut->PrintMsg("Valid , Click anywhere");
	}
	else if (type==1){                                                                                  //String check=1
		if (y<UI.ToolBarHeight+3 || y + 20>UI.height - UI.StatusBarHeight)
		{
			pOut->PrintMsg("Error! Draw only in the design area , Click anywhere");
			//GetPointClicked(x, y);
		}
		pOut->PrintMsg("Valid , Click anywhere");

	}

	else {                                                                                  //connection check=2
		if (y<UI.ToolBarHeight + 3 || y >UI.height - UI.StatusBarHeight-3)    
		{
			pOut->PrintMsg("Error! Draw only in the design area , Click anywhere");
			//GetPointClicked(x, y);
		}
		pOut->PrintMsg("Valid , Click anywhere");

	}
}
string Input::EditString(Output*pOut, string s)
{
	///TODO: Implement this Function
	pWind->FlushKeyQueue();
	char c;
	int count = s.size();
	pOut->PrintMsg(s);
	pWind->WaitKeyPress(c);
	while (c != '\r')  //Enter character
	{
		if (c != '\b') //Backspace
		{
			s.push_back(c);
			count++;
		}
		else if (count != 0)
		{
			s.pop_back();
			count--;
		}
		if (c == '\x1') //Escape character
		{
			return std::string();
		}
		pOut->PrintMsg(s);
		pWind->WaitKeyPress(c);
	}
	//Read a complete string from the user until the user presses "ENTER".
	//If the user presses "ESCAPE". This function should return an empty string.
	//"BACKSPACE" should be also supported
	//User should see what he is typing at the status bar
	return s;

}

clicktype Input::GetMouseType(int &x, int &y)
{

	return pWind->GetMouseClick(x, y);
}
void Input::GetCurrentClick(int &x, int &y)
{

	pWind->GetMouseCoord(x, y);
}
Input::~Input()
{
}
