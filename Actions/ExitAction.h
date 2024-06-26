#ifndef _EXIT_H
#define _EXIT_H
#include "Action.h"

class Exit : public Action
{
public :
	Exit(ApplicationManager* pApp);
	virtual void RedoAction();
	virtual void ReadActionParameters();
	virtual void Execute();
	virtual void UndoAction();
};

#endif // !_EXIT_H

