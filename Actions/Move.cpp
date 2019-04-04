#include "Move.h"
#include "..\ApplicationManager.h"
#include"..\Components\LED.h"

Move::Move(ApplicationManager *pApp) :Action(pApp)
{
}

Move::~Move(void) //delete dif w kda
{
	delete[] sel;
	delete[] cdif;
	delete[] coldx;
	delete[] coldy;
	delete[]newx;
	delete[]newy;
}

void Move::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//Print Action Message
	pOut->PrintMsg("Click to move a component");

	//Wait for User Input
	pIn->GetPointClicked(Cx, Cy);

	//Clear Status Bar
	pOut->ClearStatusBar();

}
void Move::Execute()
{
	Input*pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();
	ReadActionParameters();
	int x1, y1;
	int count;
	Component** c = pManager->Sortsel(x1, y1, count);
	if (c == NULL || count == 0) return;
	originx = c[0]->getgrap().x1;  originy = c[0]->getgrap().y1;
	int maxx = c[0]->getgrap().x2; int maxy = c[0]->getgrap().y2; int miny = c[0]->getgrap().y1;
	int imaxx = 0, imaxy = 0, iminy = 0;
	for (int i = 1; i < count; i++)
	{
		if (maxx < c[i]->getgrap().x2)
		{
			maxx = c[i]->getgrap().x2;
			imaxx = i;
		}
		if (maxy < c[i]->getgrap().y2)
		{
			maxy = c[i]->getgrap().y2;
			imaxy = i;
		}
		if (miny > c[i]->getgrap().y1)
		{
			miny = c[i]->getgrap().y1;
			iminy = i;
		}
	}
	int* dif = new int[2 * count - 2];
	//int * dify = new int[count - 1];
	int j = 1;
	for (int i = 0; i < 2 * count - 2; i++)     //2*count
	{
		dif[i] = c[j]->getgrap().x1 - x1;
		dif[i + 1] = c[j]->getgrap().y1 - y1;
		i++;
		j++;
	}

	//	int dif[4] = { c[1]->getgrap().x1 - x1,c[1]->getgrap().y1 - y1,c[2]->getgrap().x1 - x1,c[2]->getgrap().y1 - y1 };
	j = 1;
	int * oldx = new int[count];
	int * oldy = new int[count];
	newx = new int[count];
	newy = new int[count];
	setundo(c, dif, count, oldx, oldy);
	int temp = 1;
	while (pIn->GetMouseType(x1, y1) == 0)
	{
		for (int i = 0; i < count; i++)
		{
			if (temp == 1)
			{
				newx[i] = c[i]->getgrap().x1;
				newy[i] = c[i]->getgrap().y1;
			}
			oldx[i] = c[i]->getgrap().x1;
			oldy[i] = c[i]->getgrap().y1;
		}
		temp++;
		pIn->GetCurrentClick(x1, y1);
		if (iminy == 0 && y1 - 25 < UI.ToolBarHeight) y1 = UI.ToolBarHeight + 26;
		if (y1 + dif[2 * iminy - 1] - 25 < UI.ToolBarHeight&& iminy != 0) y1 = UI.ToolBarHeight + 26 - dif[2 * iminy - 1];
		if (imaxy == 0 && c[imaxy]->GetLabel() != "" && y1 + 47 > UI.height - UI.StatusBarHeight)
		{
			y1 = UI.height - UI.StatusBarHeight - 49;
		}
		if (y1 + dif[2 * imaxy - 1] + 47 > UI.height - UI.StatusBarHeight&& imaxy != 0 && c[imaxy]->GetLabel() != "")
		{
			y1 = UI.height - UI.StatusBarHeight - 49 - dif[2 * imaxy - 1];
		}
		if (imaxy == 0 && c[imaxy]->GetLabel() == "" && (y1 + 25 >UI.height - UI.StatusBarHeight))
		{
			y1 = UI.height - UI.StatusBarHeight - 27;
		}
		if (y1 + dif[2 * imaxy - 1] + 25 > UI.height - UI.StatusBarHeight&& imaxy != 0 && c[imaxy]->GetLabel() == "")
		{
			y1 = UI.height - UI.StatusBarHeight - 27 - dif[2 * imaxy - 1];
		}
		if (x1 < 24)
		{

			x1 = 28;
		}

		if (x1 + dif[2 * imaxx - 2] + 25 >= UI.width && imaxx != 0)
		{
			x1 = UI.width - 25 - dif[2 * imaxx - 2];

		}
		if (imaxx == 0 && x1 + 25>UI.width) x1 = UI.width - 25;
		c[0]->SetGraphics(x1, y1);
		for (int i = 0; i < 2 * count - 2; i++)
		{
			int x = x1 + dif[i];
			int y = y1 + dif[i + 1];
			c[j]->SetGraphics(x, y);
			i++;
			j++;
		}
		j = 1;
		for (int i = 0; i < count; i++)
		{
			Movegate(c[i], oldx[i], oldy[i]);
		}
		pOut->ClearDrawingArea();
		pManager->UpdateInterface();
		/*for (int i = 0; i < count; i++)
		{
		newx[i] = c[i]->getgrap().x1;
		newy[i] = c[i]->getgrap().y1;
		}*/
		Cx = x1; Cy = y1;
	}

	/*delete[] dif;
	delete[] oldx; delete[] oldy;
	dif = NULL;
	oldx = NULL; oldy = NULL;*/
}

void Move::Undo()
{
	if (sel[0] == NULL) return;
	sel[0]->SetGraphics(originx + 25, originy + 25);
	int j = 1;
	for (int i = 0; i < 2 * selcnt - 2; i++)
	{
		int x = originx + 25 + cdif[i];
		int y = originy + 25 + cdif[i + 1];
		sel[j]->SetGraphics(x, y);
		i++;
		j++;
	}
	for (int i = 0; i < selcnt; i++)
	{
		Movegate(sel[i], coldx[i], coldy[i]);
	}

	pManager->GetOutput()->ClearDrawingArea();
}

void Move::Redo()
{
	if (sel[0] == NULL) return;
	sel[0]->SetGraphics(Cx + 25, Cy + 25);
	int j = 1;
	for (int i = 0; i < 2 * selcnt - 2; i++)
	{
		int x = Cx + 25 + cdif[i];
		int y = Cy + 25 + cdif[i + 1];
		sel[j]->SetGraphics(x, y);
		i++;
		j++;
	}
	for (int i = 0; i < selcnt; i++)
	{
		Movegate(sel[i], newx[i], newy[i]);
		//coldx[i] = newx[i];
		//coldy[i] = newy[i];
	}
	for (int i = 0; i < selcnt; i++)
	{

		coldx[i] = sel[i]->getgrap().x1;
		coldy[i] = sel[i]->getgrap().y1;
	}

	pManager->GetOutput()->ClearDrawingArea();
}

void Move::Movegate(Component* c, int oldx, int oldy)
{
	//Get Center point of the Gate
	Input* pIn = pManager->GetInput();

	Output*pOut = pManager->GetOutput();
	int x = c->getgrap().x1 + 25; int y = c->getgrap().y1 + 25; //+25
	int xt = x; int yt = y;

	InputPin* arrOfInputPin[3];
	for (int i = 0; i < 3; i++)
	{
		arrOfInputPin[i] = c->getinpin(i + 1);
	}
	OutputPin* out = c->getoutpin();
	Connection* InputConn[3];

	for (int i = 0; i < 3; i++)
	{
		InputConn[i] = NULL;
	}

	int cnt = 0;
	for (int i = 0; i < 3; i++)
	{
		InputConn[i] = (Connection*)(pManager->Getconnection(arrOfInputPin[i]));
	}
	Connection** outcon;
	int countOutconn;
	if (dynamic_cast<LED*>(c)) outcon = NULL;
	else outcon = c->getoutpin()->GetConnections(countOutconn);
	int xin[3];
	int yin[3];
	for (int i = 0; i < 3; i++)
	{
		if (InputConn[i])
		{
			xin[i] = InputConn[i]->getgrap().x2 - oldx;
			yin[i] = InputConn[i]->getgrap().y2 - oldy;
		}
	}

	for (int i = 0; i < 3; i++)
	{
		if (InputConn[i])
		{
			if (InputConn[i] != NULL)
				InputConn[i]->SetGraphics((x - 25) + xin[i], (y - 25) + yin[i], false);
		}
	}
	for (int i = 0; i < countOutconn; i++)
	{
		if (outcon[i] != NULL)
			outcon[i]->SetGraphics(x + 21, y, true);
	}


}

void Move::setundo(Component** c, int * dif, int cnt, int* oldx, int * oldy)
{
	sel = c;
	selcnt = cnt;
	this->cdif = dif;
	coldx = oldx;
	coldy = oldy;
}





