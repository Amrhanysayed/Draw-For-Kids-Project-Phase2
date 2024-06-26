#ifndef ACTION_H
#define ACTION_H

#include "..\DEFS.h"
#include <iostream>
#include<string>
#include "../GUI/UI_Info.h"
#include<windows.h>
#include<mmsystem.h>
#pragma comment (lib,"winmm.lib")
class ApplicationManager; //forward class declaration

//Base class for all possible actions
class Action
{
protected:
	ApplicationManager *pManager;	//Actions needs AppMngr to do their job
	bool isCanceled = false;
	string voice="";
public:
	
	Action(ApplicationManager* pApp) { pManager = pApp;}	//constructor
	bool IsCanceled() const { return isCanceled; }
	virtual void UndoAction() = 0;
	virtual void RedoAction() = 0;
	void PlayActionVoice();
	virtual void PlayRecordingFunc()
	{

	};
	//Reads parameters required for action to execute (code depends on action type)
	virtual void ReadActionParameters() = 0;
	//Execute action (code depends on action type)
	virtual void Execute() = 0;
	virtual ~Action();
};

#endif