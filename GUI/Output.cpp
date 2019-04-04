#include "Output.h"

Output::Output()
{
	//Initialize user interface parameters

	UI.AppMode = DESIGN;	//Design Mode is the startup mode

	//Initilaize interface colors
	UI.DrawColor = BLACK;
	UI.SelectColor = BLUE;
	UI.ConnColor = RED;
	UI.MsgColor = BLUE;
	UI.BkGrndColor = WHITE;
	
	//Create the drawing window
	pWind = CreateWind(UI.width, UI.height, UI.wx, UI.wy);	
	ChangeTitle("Programming Techniques Project");
	pWind->SetBuffering(true);
	CreateDesignToolBar();	//Create the desgin toolbar
	CreateStatusBar();		//Create Status bar
	pWind->UpdateBuffer();

}

Input* Output::CreateInput() const
{
	//Create an Input Object & assign it to the Same Window
	Input* pIn = new Input(pWind);
	return pIn;
}


//======================================================================================//
//								Interface Functions										//
//======================================================================================//

window* Output::CreateWind(int wd, int h, int x, int y) const
{
	return new window(wd, h, x, y);
}
//////////////////////////////////////////////////////////////////////////////////
void Output::ChangeTitle(string Title) const
{
	pWind->ChangeTitle(Title);
}
//////////////////////////////////////////////////////////////////////////////////
void Output::CreateStatusBar() const
{
	pWind->SetPen(RED,3);
	pWind->DrawLine(0, UI.height-UI.StatusBarHeight, UI.width, UI.height-UI.StatusBarHeight);
}
//////////////////////////////////////////////////////////////////////////////////
void Output::PrintMsg(string msg) const
{
	ClearStatusBar();	//Clear Status bar to print message on it
	// Set the Message offset from the Status Bar
	int MsgX = 25;
	int MsgY = UI.StatusBarHeight - 10;

	// Print the Message
    pWind->SetFont(20, BOLD | ITALICIZED, BY_NAME, "Arial"); 
	pWind->SetPen(UI.MsgColor); 
	pWind->DrawString(MsgX, UI.height - MsgY, msg);
	pWind->UpdateBuffer();
}

void Output::PrintMsg(string msg, GraphicsInfo gfx) const
{	//Clear Status bar to print message on it
						// Set the Message offset from the Status Bar
	

	// Print the Message
	pWind->SetFont(20, BOLD | ITALICIZED, BY_NAME, "Arial");
	pWind->SetPen(UI.MsgColor);
	pWind->DrawString(gfx.x1, gfx.y1, msg);
	return;
}
//////////////////////////////////////////////////////////////////////////////////
void Output::ClearStatusBar()const
{
	// Set the Message offset from the Status Bar
	int MsgX = 25;
	int MsgY = UI.StatusBarHeight - 10;

	//Overwrite using bachground color to erase the message
	pWind->SetPen(UI.BkGrndColor);
	pWind->SetBrush(UI.BkGrndColor);
	pWind->DrawRectangle(MsgX, UI.height - MsgY, UI.width, UI.height);
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::ClearString(int x,int y)const
{
	// Set the Message offset from the Status Bar
	int MsgX = x;
	int MsgY = y;

	//Overwrite using bachground color to erase the message
	pWind->SetPen(UI.BkGrndColor);
	pWind->SetBrush(UI.BkGrndColor);
	pWind->DrawRectangle(MsgX,MsgY,UI.width,MsgY+20);
}
///////////////////////////////////////////////////////////////////////////////////
//Clears the drawing (degin) area
void Output::ClearDrawingArea() const
{
	pWind->SetPen(RED, 1);
	pWind->SetBrush(WHITE);
	pWind->DrawRectangle(0, UI.ToolBarHeight, UI.width, UI.height - UI.StatusBarHeight);
	
}
/////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//Draws the menu (toolbar) in the Design mode
void Output::CreateDesignToolBar() const
{
	UI.AppMode = DESIGN;	//Design Mode

							//You can draw the tool bar icons in any way you want.

							//First prepare List of images for each menu item
	string MenuItemImages[ITM_DSN_CNT];
	MenuItemImages[ITM_AND2] = "images\\Menu\\Menu_AND2.jpg";
	MenuItemImages[ITM_AND3] = "images\\Menu\\Menu_AND3.jpg";
	MenuItemImages[ITM_OR2] = "images\\Menu\\Menu_OR2.jpg";
	MenuItemImages[ITM_NOT] = "images\\Menu\\Menu_NOT.jpg";
	MenuItemImages[ITM_BUF] = "images\\Menu\\Menu_BUF.jpg";
	MenuItemImages[ITM_XOR2] = "images\\Menu\\Menu_XOR2.jpg";
	MenuItemImages[ITM_XOR3] = "images\\Menu\\Menu_XOR3.jpg";
	MenuItemImages[ITM_NAND2] = "images\\Menu\\Menu_NAND2.jpg";
	MenuItemImages[ITM_XNOR2] = "images\\Menu\\Menu_XNOR2.jpg";
	MenuItemImages[ITM_NOR2] = "images\\Menu\\Menu_NOR2.jpg";
	MenuItemImages[ITM_NOR3] = "images\\Menu\\Menu_NOR3.jpg";
	MenuItemImages[ITM_SWITCH_OPENED] = "images\\Menu\\switch_opened.jpg";
	MenuItemImages[ITM_LED] = "images\\Menu\\LED.jpg";
	MenuItemImages[ITM_UNDO] = "images\\Menu\\UNDO.jpg";
	MenuItemImages[ITM_REDO] = "images\\Menu\\REDO.jpg";
	MenuItemImages[ITM_CONN] = "images\\Menu\\Connection.jpg";
	MenuItemImages[ITM_LABEL] = "images\\Menu\\LABEL.jpg";
	MenuItemImages[ITM_DELETE] = "images\\Menu\\DELETE.jpg";
	MenuItemImages[ITM_SAVE] = "images\\Menu\\save_1.jpg";
	MenuItemImages[ITM_EDITLABEL] = "images\\Menu\\edit_label.jpg";
	MenuItemImages[ITM_EDITCONN] = "images\\Menu\\edit_conn.jpg";
	MenuItemImages[ITM_LOAD] = "images\\Menu\\LOAD.jpg";
	MenuItemImages[ITM_COPY] = "images\\Menu\\copy_1.jpg";
	MenuItemImages[ITM_CUT] = "images\\Menu\\cut_1.jpg";
	MenuItemImages[ITM_PASTE] = "images\\Menu\\paste_1.jpg";
	MenuItemImages[ITM_SIMU] = "images\\Menu\\SIMULATE.jpg";
	MenuItemImages[ITM_MOVE] = "images\\Menu\\move_1.jpg";
	MenuItemImages[ITM_EXIT] = "images\\Menu\\Menu_Exit.jpg";
	//TODO: Prepare image for each menu item and add it to the list

	//Draw menu item one image at a time
	int count = 0;
	for (int i = 0; i <ITM_REDO; i++) //ITM_SWITCH_CLOSED
		pWind->DrawImage(MenuItemImages[i], i*UI.ToolItemWidth, 0, UI.ToolItemWidth, UI.ToolBarHeight / 2);
	for (int i = ITM_REDO; i < ITM_DSN_CNT; i++) //same
	{
		pWind->DrawImage(MenuItemImages[i], count*UI.ToolItemWidth, UI.ToolBarHeight / 2, UI.ToolItemWidth, UI.ToolBarHeight / 2);
		count++;
	}


	//Draw a line under the toolbar
	pWind->SetPen(RED, 3);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);

}
void Output::ClearDesignToolBar() const
{
	pWind->SetPen(WHITE, 1);
	pWind->SetBrush(WHITE);
	pWind->DrawRectangle(0, 0, UI.width, UI.ToolBarHeight+2);//UI.ToolBarHeight+70
}
//////////////////////////////////////////////////////////////////////////////////////////
//Draws the menu (toolbar) in the simulation mode
void Output::CreateSimulationToolBar() const
{
	UI.AppMode = SIMULATION;	//Simulation Mode

	string MenuItemImages[ITM_SIM_CNT];
	MenuItemImages[ITM_VAL] = "images\\Menu\\checktouse.jpg";
	MenuItemImages[ITM_SIM] = "images\\Menu\\SimulateSIM.jpg";
	MenuItemImages[ITM_TRUTH] = "images\\Menu\\TRUTH.jpg";//cant find any sort of image
	MenuItemImages[ITM_PROBE] = "images\\Menu\\Probe.jpg";
	MenuItemImages[ITM_DESIGN] = "images\\Menu\\Design.jpg";
	MenuItemImages[ITM_EXITSIM]= "images\\Menu\\Menu_ExitSIM.jpg";

	//TODO: Prepare image for each menu item and add it to the list

	//Draw menu item one image at a time
	for (int i = 0; i<ITM_SIM_CNT; i++)
		pWind->DrawImage(MenuItemImages[i], i*UI.ToolItemWidth, 0, UI.ToolItemWidth, 30+UI.ToolBarHeight/(2));

	//Draw a line under the toolbar
	pWind->SetPen(GREEN, 3);
	pWind->DrawLine(0, 30 + UI.ToolBarHeight / (2), UI.width, 30+UI.ToolBarHeight/(2));





}

//======================================================================================//
//								Components Drawing Functions							//
//======================================================================================//

void Output::DrawAND2(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if(selected)	//use image in the highlighted case
		GateImage="Images\\Gates\\Gate_AND2_Hi.jpg"; //HI
	else  
		GateImage = "Images\\Gates\\Gate_AND2.jpg";

	//Draw AND2 Gate at Gfx_Info (1st corner)
	//Set the Image Width & Height by AND2 Image Parameter in UI_Info
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.AND2_Width, UI.AND2_Height);
}

void Output::DrawAND3(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)	
		GateImage = "Images\\Gates\\Gate_AND3_Hi.jpg"; //HI
	else
		GateImage = "Images\\Gates\\Gate_AND3.jpg";
   pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.AND2_Width, UI.AND2_Height);
}

void Output::DrawOR2(GraphicsInfo r_GfxInfo, bool selected) const //ana
{
	string GateImage;
	if (selected)
		GateImage = "Images\\Gates\\Gate_OR2_HI.jpg";
	else GateImage = "Images\\Gates\\Gate_OR2.jpg";
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.AND2_Width, UI.AND2_Height);
}

void Output::DrawXOR2(GraphicsInfo r_GfxInfo, bool selected) const //ana
{
	string GateImage;
	if (selected)
		GateImage = "Images\\Gates\\Gate_XOR2_HI.jpg";
	else GateImage = "Images\\Gates\\Gate_XOR2.jpg";
		pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.AND2_Width, UI.AND2_Height);
}

void Output::DrawXOR3(GraphicsInfo r_GfxInfo, bool selected) const //ana
{
	string GateImage;
	if (selected)
		GateImage = "Images\\Gates\\Gate_XOR3_HI.jpg";
	else GateImage = "Images\\Gates\\Gate_XOR3.jpg";
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.AND2_Width, UI.AND2_Height);
}

//TODO: Add similar functions to draw all components
void Output::DrawNOT1(GraphicsInfo r_GfxInfo, bool selected ) const
{
	string GateImage;
	if (selected)
		GateImage = "Images\\Gates\\Gate_NOT_HI.jpg";
	else GateImage = "Images\\Gates\\Gate_NOT.jpg";
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.AND2_Width, UI.AND2_Height);
}

void Output::DrawBUF1(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)
		GateImage = "Images\\Gates\\Gate_BUF_HI.jpg";
	else GateImage = "Images\\Gates\\Gate_BUF.jpg";
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.AND2_Width, UI.AND2_Height);
}

void Output::DrawNAND2(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)
		GateImage = "Images\\Gates\\Gate_NAND2_HI.jpg";
	else GateImage = "Images\\Gates\\Gate_NAND2.jpg";
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.AND2_Width, UI.AND2_Height);
}

void Output::DrawXNOR2(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)
		GateImage = "Images\\Gates\\Gate_XNOR2_HI.jpg";
	else GateImage = "Images\\Gates\\Gate_XNOR2.jpg";
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.AND2_Width, UI.AND2_Height);
}

void Output::DrawNOR2(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)
		GateImage = "Images\\Gates\\Gate_NOR2_HI.jpg";
	else GateImage = "Images\\Gates\\Gate_NOR2.jpg";
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.AND2_Width, UI.AND2_Height);
}

void Output::DrawNOR3(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)
		GateImage = "Images\\Gates\\Gate_NOR3_HI.jpg";
	else GateImage = "Images\\Gates\\Gate_NOR3.jpg";
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.AND2_Width, UI.AND2_Height);
}

//Draw functions for switch and LED
void Output::DrawSwitchClosed(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)
		GateImage = "Images\\Gates\\switch1_HI.jpg";
	else GateImage = "Images\\Gates\\switch1.jpg";
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.AND2_Width, UI.AND2_Height);
}
void Output::DrawSwitchOpened(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)
		GateImage = "Images\\Gates\\switch0_HI.jpg";
	else GateImage = "Images\\Gates\\switch0.jpg";
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.AND2_Width, UI.AND2_Height);
}
//To be changed in phase 2
void Output::DrawLED0(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)
		GateImage = "Images\\Gates\\LED0_Hi.jpg";
	else GateImage = "Images\\Gates\\LED0.jpg";
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.AND2_Width, UI.AND2_Height);
}

void Output::DrawLED1(GraphicsInfo r_GfxInfo, bool selected) const
{
	string GateImage;
	if (selected)
		GateImage = "Images\\Gates\\LED1_Hi.jpg";
	else GateImage = "Images\\Gates\\LED1.jpg";
	pWind->DrawImage(GateImage, r_GfxInfo.x1, r_GfxInfo.y1, UI.AND2_Width, UI.AND2_Height);
}

void Output::DrawConnection(GraphicsInfo r_GfxInfo, bool selected) const
{
	//TODO: Add code to draw connection
	//pWind->GetMouseCoord; is this what we should use?
	if (selected) {
		//pWind->SetPen(0.0, 0.2, 1.0, 3);
		pWind->SetPen(UI.SelectColor, 3);
		int mid = (r_GfxInfo.x1 + r_GfxInfo.x2) / 2;
		pWind->DrawLine(r_GfxInfo.x1, r_GfxInfo.y1,mid, r_GfxInfo.y1);
		pWind->DrawLine(mid, r_GfxInfo.y1, mid, r_GfxInfo.y2);
		pWind->DrawLine(mid, r_GfxInfo.y2, r_GfxInfo.x2, r_GfxInfo.y2);
	}
	else
	{
		//pWind->SetPen(0.0, 0.0, 0.0, 2);
		pWind->SetPen(UI.ConnColor, 3);
		//int diff = r_GfxInfo.y2 - r_GfxInfo.y1;
		
		//r_GfxInfo.y2 = (diff <= 1 || diff>= -1 ? r_GfxInfo.y1 : r_GfxInfo.y2);
		int mid = (r_GfxInfo.x1 + r_GfxInfo.x2) / 2;
		pWind->DrawLine(r_GfxInfo.x1, r_GfxInfo.y1, mid, r_GfxInfo.y1);
		pWind->DrawLine(mid, r_GfxInfo.y1, mid, r_GfxInfo.y2);
		pWind->DrawLine(mid, r_GfxInfo.y2, r_GfxInfo.x2, r_GfxInfo.y2);
	}
}

void Output::DeleteConnection(GraphicsInfo r_GfxInfo, bool selected) const
{
	//TODO: Add code to draw connection
	//pWind->GetMouseCoord; is this what we should use?
	if (selected) {
		//pWind->SetPen(0.0, 0.2, 1.0, 3);
		pWind->SetPen(UI.SelectColor, 3);
		int mid = (r_GfxInfo.x1 + r_GfxInfo.x2) / 2;
		pWind->DrawLine(r_GfxInfo.x1, r_GfxInfo.y1, mid, r_GfxInfo.y1);
		pWind->DrawLine(mid, r_GfxInfo.y1, mid, r_GfxInfo.y2);
		pWind->DrawLine(mid, r_GfxInfo.y2, r_GfxInfo.x2, r_GfxInfo.y2);
	}
	else
	{
		//pWind->SetPen(0.0, 0.0, 0.0, 2);
		pWind->SetPen(1.0,1.0,1.0,3);
		//int diff = r_GfxInfo.y2 - r_GfxInfo.y1;

		//r_GfxInfo.y2 = (diff <= 1 || diff>= -1 ? r_GfxInfo.y1 : r_GfxInfo.y2);
		int mid = (r_GfxInfo.x1 + r_GfxInfo.x2) / 2;
		pWind->DrawLine(r_GfxInfo.x1, r_GfxInfo.y1, mid, r_GfxInfo.y1);
		pWind->DrawLine(mid, r_GfxInfo.y1, mid, r_GfxInfo.y2);
		pWind->DrawLine(mid, r_GfxInfo.y2, r_GfxInfo.x2, r_GfxInfo.y2);
	}
}

color Output::getpixelcol(int x, int y)
{
	return pWind->GetColor(x, y);
}

void Output::UpdateBuffer()
{
	pWind->UpdateBuffer();
}

Output::~Output()
{
	delete pWind;
}
