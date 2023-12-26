#ifndef _SWITCH_TO_DRAW_MODE_H
#define _SWITCH_TO_DRAW_MODE_H
#include "../Actions/Action.h"

class SwitchToDrawMode : public Action
{
public:
	SwitchToDrawMode(ApplicationManager* pApp);

	virtual void UndoAction();
	virtual void ReadActionParameters();

	virtual void RedoAction();
	virtual void Execute();

};


#endif // !_SWITCH_TO_DRAW_MODE_H
