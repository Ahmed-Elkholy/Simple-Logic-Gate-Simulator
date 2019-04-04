#include "Action.h"
#include "..\ApplicationManager.h"

bool Action::CheckCoordinates(int &x, int &y, int type)
{
	Output * pOut = pManager->GetOutput();
	if (type == 0) {
		if (y<UI.ToolBarHeight +23 || y + UI.AND2_Height>UI.height - UI.StatusBarHeight) //component check=0
		{
			pOut->PrintMsg("Error! Draw only in the design area , Click anywhere");
			//GetPointClicked(x, y);
			return false;
		}
		pOut->PrintMsg("Valid , Click anywhere");
	}
	else if (type == 1) {                                                                                  //String check=1
		if (y<UI.ToolBarHeight + 3 || y + 20>UI.height - UI.StatusBarHeight)
		{
			pOut->PrintMsg("Error! Draw only in the design area , Click anywhere");
			//GetPointClicked(x, y);
			return false;
		}
		pOut->PrintMsg("Valid , Click anywhere");
	}

	else {                                                                                  //connection check=2
		if (y<UI.ToolBarHeight + 3 || y >UI.height - UI.StatusBarHeight - 3)
		{
			pOut->PrintMsg("Error! Draw only in the design area , Click anywhere");
			//GetPointClicked(x, y);
			return false;
		}
		pOut->PrintMsg("Valid , Click anywhere");

	}
	return true;
}

