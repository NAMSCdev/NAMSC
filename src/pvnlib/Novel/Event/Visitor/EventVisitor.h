#pragma once

/// Forward declaration of all Events for the EventVisitor
class EventChoice;
class EventEndIf;
class EventIf;
class EventInput;
class EventJump;
class EventDialogue;
class EventWait;
// [optional]
//class EventRenPyScript;

/// Base class of a Visitor for Events
/// It is not the abstract class, like it should be, but is defaulting to doing nothing and allowing for the overload
class EventVisitor
{
public:	
	virtual void visitEventChoice(EventChoice*)     {}
	virtual void visitEventEndIf(EventEndIf*)       {}
	virtual void visitEventIf(EventIf*)             {}
	virtual void visitEventInput(EventInput*)       {}
	virtual void visitEventJump(EventJump*)         {}
	virtual void visitEventDialogue(EventDialogue*) {}
	virtual void visitEventWait(EventWait*)         {}

	// [optional]
	//virtual void visitEventRenPy(EventRenPyScript*) {}
};