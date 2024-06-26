#include "AddCircleAction.h"


AddCircleAction::AddCircleAction(ApplicationManager* pApp):Action(pApp)
{
	voice = "Sound\\Circle.wav ";

}
void AddCircleAction::PlayRecordingFunc()
{
	int radius = int(sqrt(double((P1.x - P2.x) * (P1.x - P2.x) + (P1.y - P2.y) * (P1.y - P2.y))));
	copyLastDrawnCircle = new CCircle(P1, radius, CircleGfxInfo);
	CCircle::DecreaseCount();

	pManager->AddPlayRecordingFigure(copyLastDrawnCircle);
}
void AddCircleAction::RedoAction()
{
	if (!copyLastDrawnCircle)
	{
		LastDrawnCircle->showFigure(true);
		LastDrawnCircle->SetDelete(false);
		pManager->RedoProcessDeletedFigures(LastDrawnCircle);
		pManager->AddFigure(LastDrawnCircle);
	}
	else
	{
		copyLastDrawnCircle->showFigure(true);
		copyLastDrawnCircle->SetDelete(false);
		pManager->RedoProcessDeletedFigures(copyLastDrawnCircle);
		pManager->AddPlayRecordingFigure(copyLastDrawnCircle);
	}
}
void AddCircleAction::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	copyLastDrawnCircle = NULL;

	pOut->PrintMessage("New Circle: Click at first point, right-click to cancel operation");

	//Read 1st point and store in point P1
	clicktype cType;
	cType = pIn->GetPointForDrawing(P1.x, P1.y, pOut);
	if (cType == RIGHT_CLICK)
	{
		isCanceled = true;
		return;
	}
	pOut->PrintMessage("New Circle: Click at second poin, right-click to cancel operation");

	//Read 2nd point and store in point P2
	cType = pIn->GetPointForDrawing(P2.x, P2.y, pOut);
	if (cType == RIGHT_CLICK)
	{
		isCanceled = true;
		return;
	}
	CircleGfxInfo.isFilled = UI.FillColor != UI.DefaultFillColor;	//default is not filled
	//get drawing, filling colors and pen width from the interface
	CircleGfxInfo.DrawClr = pOut->getCrntDrawColor();
	CircleGfxInfo.FillClr = pOut->getCrntFillColor();

	pOut->ClearStatusBar();

}

void AddCircleAction::Execute()
{
	ReadActionParameters();
	Output* pOut = pManager->GetOutput();
	if (isCanceled) {
		pOut->PrintMessage("Successfully canceled the operation.");
		return;
	}
		
	//Create a circle with the parameters read from the user
	int radius = int(sqrt(double((P1.x - P2.x) * (P1.x - P2.x) + (P1.y - P2.y) * (P1.y - P2.y))));
	LastDrawnCircle = new CCircle(P1, radius, CircleGfxInfo);

	CCircle* ptr=nullptr;
	//	copyLastDrawnCircle = ptr->SaveCopyOfFigure();
	//Add the rectangle to the list of figures
	pManager->AddFigure(LastDrawnCircle);

}
void AddCircleAction::UndoAction()
{
	LastDrawnCircle->showFigure(false);
	LastDrawnCircle->SetDelete(true);
	if (copyLastDrawnCircle)
	{
		copyLastDrawnCircle->showFigure(false);
		copyLastDrawnCircle->SetDelete(true);
	}
	pManager->ProcessDeletedFigures();
}