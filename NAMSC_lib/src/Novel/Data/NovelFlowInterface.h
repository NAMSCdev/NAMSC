#pragma once
#include "Global.h"

///A Novel element, which is tied to the flow of the Novel and needs to be managed properly
class NovelFlowInterface
{
public:
	///The destructor needs to be virtual, so the proper destructor will always be called when destroying an NovelFlowInterface pointer
	virtual ~NovelFlowInterface() = 0;

	///Execution of the NovelFlowInterface
	virtual void run()            = 0;

	///Some NovelFlowInterfaces are designed to update things and should be called frequently until the end of the Event
	virtual void update()         = 0;

	///Some NovelFlowInterfaces need to access the data, that is a part of the Save
	///Must be called after the Save is loaded
	virtual void syncWithSave()   = 0;

	///Checks if the NovelFlowInterface doesn't have any errors, which would halt the Novel execution
	virtual bool checkForErrors() = 0;

	///Cleanup of the NovelFlowInterface
	virtual void end()            = 0;
};