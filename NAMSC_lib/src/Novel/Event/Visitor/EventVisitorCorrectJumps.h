#pragma once
#include "Global.h"

#include "Novel/Event/EventsAll.h"

///CorrectsJump
class EventVisitorCorrectJumps final : public EventVisitor
{
public:
	EventVisitorChangeID(int sceneID, int oldID, int newID) : sceneID(sceneID), oldID(oldID), newID(newID) {};

	virtual void visitEventChoice(EventChoice *e) override		{ changeID(e); }
	virtual void visitEventInput(EventInput *e) override		{ changeID(e); }
	virtual void visitEventJump(EventJump *e) override			{ changeID(e); }

private:
	///Changes IDs
	void changeID(Event* event)			
	{ 
		
	}

	///The ID to be replaced, if an Event has this executionOrder
	int oldID;

	int newID;
};