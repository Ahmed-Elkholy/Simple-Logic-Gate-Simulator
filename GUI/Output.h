#pragma once
#include "..\Defs.h"
#include "Input.h"

class Output	//The application manager should have a pointer to this class
{
private:
	window* pWind;	//Pointer to the Graphics Window
public:
	Output(); // Performs the Window Initialization
	Input* CreateInput() const; //creates a pointer to the Input object
	void ChangeTitle(string Title) const;

	void CreateDesignToolBar() const;	//Tool bar of the design mode
	void CreateSimulationToolBar() const;//Tool bar of the simulation mode
	void CreateStatusBar() const;	//Create Status bar
	color getpixelcol(int x, int y);
	void ClearStatusBar() const;		//Clears the status bar
	void ClearDrawingArea() const;	//Clears the drawing area
	void ClearDesignToolBar() const;
	void ClearString(int x, int y)const;
	window* CreateWind(int wd, int h, int x, int y) const; //Creates user interface window

	
	// Draws 2-input AND gate
	void DrawAND2(GraphicsInfo r_GfxInfo, bool selected = false) const;
	void DrawAND3(GraphicsInfo r_GfxInfo, bool selected = false) const;
	void DrawOR2(GraphicsInfo r_GfxInfo, bool selected = false) const;
	void DrawXOR2(GraphicsInfo r_GfxInfo, bool selected = false) const;
	void DrawXOR3(GraphicsInfo r_GfxInfo, bool selected = false) const;
	void DrawNOT1(GraphicsInfo r_GfxInfo, bool selected = false) const;
	void DrawBUF1(GraphicsInfo r_GfxInfo, bool selected = false) const;
	void DrawNAND2(GraphicsInfo r_GfxInfo, bool selected = false) const;
	void DrawXNOR2(GraphicsInfo r_GfxInfo, bool selected = false) const;
	void DrawNOR2(GraphicsInfo r_GfxInfo, bool selected = false) const;
	void DrawNOR3(GraphicsInfo r_GfxInfo, bool selected = false) const;
	///TODO: Make similar functions for drawing all other gates, switch, and LED, .. etc
	void DrawSwitchClosed(GraphicsInfo r_GfxInfo, bool selected = false) const;
	void DrawSwitchOpened(GraphicsInfo r_GfxInfo, bool selected = false) const;
	void DrawLED0(GraphicsInfo r_GfxInfo, bool selected = false) const;
	void DrawLED1(GraphicsInfo r_GfxInfo, bool selected = false) const;
	// Draws Connection
	void DrawConnection(GraphicsInfo r_GfxInfo, bool selected = false) const;
	void DeleteConnection(GraphicsInfo r_GfxInfo, bool selected = false) const; //To be used by Edit Connection (can be removed after wael work)
	void PrintMsg(string msg) const;	//Print a message on Status bar
	void PrintMsg(string msg, GraphicsInfo gfx) const;
	void drawrect(int x1, int y1, int x2, int y2)
	{
		//pWind->SetBuffering(false);
		pWind->SetPen(0.0, 0.0, 1.0);
		pWind->DrawRectangle(x1, y1, x2, y2, FRAME);
		pWind->UpdateBuffer();
	}
	void UpdateBuffer();
	~Output();
};
