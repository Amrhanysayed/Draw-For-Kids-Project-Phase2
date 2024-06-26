#include "CSquare.h"

int CSquare::Count = 0;
CSquare::CSquare(Point C, GfxInfo FigureGfxInfo,int l):CFigure(FigureGfxInfo)
{
	Type = "square";

	center = C;

	L = l;

	RefineShape();
	CSquare::Count++;
}
void CSquare::RefineShape()
{
	int toolBarH = UI.ToolBarHeight + 3;
	int statusBarH = UI.height - UI.StatusBarHeight - 3;

	if (abs(center.y - toolBarH) < L) {
		L = abs(center.y - toolBarH);
	}
	if (abs(statusBarH - center.y) < L) {
		L = abs(statusBarH - center.y);
	}
}

void CSquare::ResizeByDragging(Point& P1)
{
	if (P1.x < 0 || P1.y < 0 || P1.x > UI.width || P1.y > UI.height)
		return;
	Point PSquare = GetFigureCenter();
	int DifferenceX = (P1.x - PSquare.x);
	int DifferenceY = (P1.y - PSquare.y);
	L = sqrt((DifferenceX * DifferenceX) + (DifferenceY * DifferenceY));
	RefineShape();
}

void CSquare::DecreaseCount()
{
	Count--;
}

void CSquare::IncreaseCount()
{
	Count++;
}

Point CSquare::GetFigureCenter()
{
	return center;
}

void CSquare::Draw(Output* pOut) const
{ 
	pOut->DrawSquare(center, L, FigGfxInfo, Selected);
	
}

void CSquare::Move(Point Pm)
{
	if ((Pm.y + L) >= (UI.height - UI.StatusBarHeight))
	{
		Pm.y = UI.height - UI.StatusBarHeight - L - 1;
	}
	if ((Pm.y - L) <= (UI.ToolBarHeight))
	{
		Pm.y = UI.ToolBarHeight + L + 1;
	}
	if ((Pm.x - L) <= (0))
	{
		Pm.x = L + 1;
	}
	if ((Pm.x + L) >= (UI.width))
	{
		Pm.x = UI.width - L - 1;
	}
	center = Pm;
}

bool CSquare::CheckSelection(int x, int y)
{
	return (x >= center.x - L && x <= center.x + L && y >= center.y - L && y <= center.y + L);
}

void CSquare::Save(ofstream& OutFile)
{
	string fcname = Output::GetColorName(FigGfxInfo.FillClr); // Fill color
	string dcname = Output::GetColorName(FigGfxInfo.DrawClr); // Draw color

	OutFile << "SQUARE" << "\t" << ID << "\t" << center.x << "\t" << center.y << "\t"  << L << "\t" << dcname << "\t" << fcname << endl;

}



int CSquare::GetCount()
{
	return CSquare::Count;
}

void CSquare::PrintInfo(Output* pOut)
{
	string s = "Square ID: " + to_string(ID) + ", Fill Color: " + pOut->GetColorName(FigGfxInfo.FillClr) + ", Draw Color: " + pOut->GetColorName(FigGfxInfo.DrawClr) + ", Center: (" + to_string(center.x) + "," + to_string(center.y) + "), Length: " + to_string(L);
	pOut->PrintMessage(s);
}
