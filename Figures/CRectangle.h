#ifndef CRECT_H
#define CRECT_H

#include "CFigure.h"

class CRectangle : public CFigure
{
private:
	Point pointForResizing;
	Point Corner1;	
	Point Corner2;
	static int Count; // number of figures of this type
	int Difference;
public:
	CRectangle(Point , Point, GfxInfo FigureGfxInfo );
	virtual Point GetFigureCenter();
	virtual void Draw(Output* pOut) const;
	virtual void Move(Point Pm);
	virtual bool CheckSelection(int x, int y);
	virtual void Save(ofstream& OutFile);    //done in all with same implemation


	virtual void ResizeByDragging(Point& P);

	static int GetCount();
	static void SetCount(int i);
	~CRectangle();
};

#endif