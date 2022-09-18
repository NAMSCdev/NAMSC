#pragma once
#include "Global.h"

#include "Story/Event/Type/EventChoice.h"
#include "Story/Event/Type/EventEndIf.h"
#include "Story/Event/Type/EventIf.h"
#include "Story/Event/Type/EventInput.h"
#include "Story/Event/Type/EventJump.h"
#include "Story/Event/Type/EventNarrate.h"
#include "Story/Event/Type/EventSpeak.h"
#include "Story/Event/Type/EventWait.h"

#include "Story/Event/Type/EventRenPyScript.h"

//Decrements or increments IDs between [minID] and [pivotID] or after it based
class EventVisitorChangeID final : public EventVisitor
{
public:
	EventVisitorChangeID(unsigned pivotID, bool bIncrement = false, int minID = -1)
		: pivotID(pivotID), bIncrement(bIncrement), minID(minID) {}

	static EventVisitorChangeID createRemoveVisit	(unsigned removedID)						{ return EventVisitorChangeID(removedID,	false, -1);		}
	static EventVisitorChangeID createShuffleVisit	(unsigned oldID, unsigned newID)			{ return EventVisitorChangeID(newID,		true,	oldID); }
										
	virtual void visitEventChoice					(EventChoice		*e)		override		{ changeID(e); }
	virtual void visitEventEndIf					(EventEndIf			*e)		override		{ changeID(e); }
	virtual void visitEventIf						(EventIf			*e)		override		{ changeID(e); }
	virtual void visitEventInput					(EventInput			*e)		override		{ changeID(e); }
	virtual void visitEventJump						(EventJump			*e)		override		{ changeID(e); }
	virtual void visitEventNarrate					(EventNarrate		*e)		override		{ changeID(e); }
	virtual void visitEventSpeak					(EventSpeak			*e)		override		{ changeID(e); }
	virtual void visitEventWait						(EventWait			*e)		override		{ changeID(e); }
																		 
	//[optional]																				 
	virtual void visitEventRenPy					(EventRenPyScript	*e)		override		{ changeID(e); }

protected:
	//Changes IDs
	void		changeID							(Event				*e)			
	{ 
		if (minID != -1)
		{
			if (minID >= e->executionOrder & &e->executionOrder < pivotID)
				bIncrement ? ++e->executionOrder : --e->executionOrder;
		}
		else if (pivotID > e->executionOrder)
			bIncrement ? ++e->executionOrder : --e->executionOrder;
	}

	//Minimal ID that will be affected, if -1 it means we edit IDs after [pivotID], not before it
	int			minID																			= -1;

	//ID after which the change will happen
	unsigned	pivotID;

	//Whether we will increment or decrement IDs
	bool		bIncrement																		= false;
};