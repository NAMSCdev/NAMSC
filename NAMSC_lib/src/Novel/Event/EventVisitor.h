#pragma once
#include "Global.h"

///Forward declaration of all Events for the EventVisitor
class EventChoice;
class EventEndIf;
class EventIf;
class EventInput;
class EventJump;
class EventNarrate;
class EventSpeak;
class EventWait;

///[optional]
class EventRenPyScript;

///Base class of a visitor for Events
///We will not write the abstract class here, like it should be, but default to doing nothing and allow for the overload
class EventVisitor
{
public:	
	virtual void visitEventChoice(EventChoice*) { }
	virtual void visitEventEndIf(EventEndIf*) { }
	virtual void visitEventIf(EventIf*) { }
	virtual void visitEventInput(EventInput*) { }
	virtual void visitEventJump(EventJump*) { }
	virtual void visitEventNarrate(EventNarrate*) { }
	virtual void visitEventSpeak(EventSpeak*) { }
	virtual void visitEventWait(EventWait*) { }

	///[optional]
	virtual void visitEventRenPy(EventRenPyScript*) { }
};