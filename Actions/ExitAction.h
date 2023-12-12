#ifndef _EXIT_H
#define _EXIT_H
#include "../Actions/Action.h"

class Exit : public Action
{
public :
	Exit(ApplicationManager* pApp);
	virtual void ReadActionParameters();
	virtual void Execute();
	virtual void UndoAction();
};

#endif // !_EXIT_H

