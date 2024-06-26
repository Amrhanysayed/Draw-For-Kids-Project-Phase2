#include "CRectangle.h"
#include <cmath>
#include <iostream>
using namespace std;
//mohamed
int CRectangle::Count = 0;
CRectangle::CRectangle(Point P1, Point P2, GfxInfo FigureGfxInfo):CFigure(FigureGfxInfo)
{
	pointForResizing.x = 0;
	pointForResizing.y = 0;
	Type = "rectangle";

	Corner1 = P1;
	Corner2 = P2;

	CRectangle::Count++;
}

Point CRectangle::GetFigureCenter()
{
	Point p;
	p.x = (Corner1.x + Corner2.x) / 2;
	p.y = (Corner1.y + Corner2.y) / 2;
	return p;
}
	
void CRectangle::ResizeByDragging(Point& P1)
{
	if(P1.x < 0 || P1.y < 0 || P1.x > UI.width || P1.y > UI.height)
		return;
	Point RectangleCenter = Corner2;
	int DifferenceX = (P1.x - RectangleCenter.x);
	int DifferenceY = (P1.y - RectangleCenter.y);
	pointForResizing.x = DifferenceX;
	pointForResizing.y = DifferenceY;
	Corner2 = Corner2 + pointForResizing;
	RefineShape();
}

void CRectangle::PrintInfo(Output* pOut)
{
	string s = "Rectangle ID: " + to_string(ID) + ", Fill Color: " + pOut->GetColorName(FigGfxInfo.FillClr) + ", Draw Color: " + pOut->GetColorName(FigGfxInfo.DrawClr) + ", Corner1: (" + to_string(Corner1.x) + "," + to_string(Corner1.y) + "), Corner2: (" + to_string(Corner2.x) + "," + to_string(Corner2.y) + ")";
	pOut->PrintMessage(s);
}

void CRectangle::Draw(Output* pOut) const
{
	//Call Output::DrawRect to draw a rectangle on the screen
	pOut->DrawRect(Corner1, Corner2, FigGfxInfo, Selected);
}
void CRectangle::RefineShape()
{
	int toolBarH = UI.ToolBarHeight + 3;
	int statusBarH = UI.height - UI.StatusBarHeight - 3;
	if (Corner2.x < 0)
	{
		Corner2.x = 0;
	}
	if (Corner2.y < toolBarH)
	{
		Corner2.y = toolBarH;
	}
	if (Corner2.x > UI.width)
	{
		Corner2.x = UI.width;
	}
	if (Corner2.y > statusBarH)
	{
		Corner2.y = statusBarH;
	}
}
void CRectangle::Move(Point Pm)
{
	Point P1n, P2n;
	P2n.x = Pm.x + (abs(Corner2.x - Corner1.x) / 2.0);
	P1n.x = Pm.x - (abs(Corner2.x - Corner1.x) / 2.0);
	P2n.y = Pm.y + (abs(Corner2.y - Corner1.y) / 2.0);
	P1n.y = Pm.y - (abs(Corner2.y - Corner1.y) / 2.0);
	double xDiff = P2n.x - P1n.x;
	double yDiff = P2n.y - P1n.y;
	if (P1n.y <= UI.ToolBarHeight)
	{
		P1n.y = UI.ToolBarHeight + 1;
		P2n.y = P1n.y + yDiff;
	}
	if (P2n.y >= (UI.height - UI.StatusBarHeight))
	{
		P2n.y = UI.height - UI.StatusBarHeight - 1;
		P1n.y = P2n.y - yDiff;
	}
	if (P1n.x < 0)
	{
		P1n.x = 1;
		P2n.x = P1n.x + xDiff;
	}
	if (P2n.x > UI.width)
	{
		P2n.x = UI.width - 1;
		P1n.x = P2n.x - xDiff;
	}
	Corner1 = P1n;
	Corner2 = P2n;
}

bool CRectangle::CheckSelection(int x, int y)
{
	int xmin = min(Corner1.x, Corner2.x);
	int xmax = max(Corner1.x, Corner2.x);

	int ymin = min(Corner1.y, Corner2.y);
	int ymax = max(Corner1.y, Corner2.y);

	return (x >= xmin && x <= xmax && y >= ymin && y <= ymax);
}
void CRectangle::Save(ofstream& OutFile)
{
	string fcname = Output::GetColorName(FigGfxInfo.FillClr); // Fill color
	string dcname = Output::GetColorName(FigGfxInfo.DrawClr); // Draw color

	OutFile << "RECT" << "\t" << ID << "\t" << Corner1.x << "\t" << Corner1.y << "\t" << Corner2.x << "\t" << Corner2.y << "\t" << dcname << "\t" << fcname << endl;
}

int CRectangle::GetCount()
{
	return CRectangle::Count;
}

void CRectangle::DecreaseCount() {

	Count--;

}

void CRectangle::IncreaseCount()
{
	Count++;
}
