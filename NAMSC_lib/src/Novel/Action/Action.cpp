#include "Novel/Action/Action.h"

#include "Novel/Data/Scene.h"

Action::Action(Event* const parentEvent, Scene* const parentScene) noexcept
	: parentEvent_(parentEvent), parentScene_(parentScene)
{
}

Action::~Action() = default;

Action& Action::operator=(const Action& obj) noexcept
{ 
	if (this == &obj) return *this;

	return *this;
}

bool Action::operator==(const Action& obj) const noexcept
{
	return true;
}

bool Action::checkForErrors(bool bComprehensive) const
{
	bool bError = false;

	//static auto errorChecker = [&](bool bComprehensive)
	//{
	//};

	//bError |= NovelLib::catchExceptions(errorChecker, bComprehensive);
	
	//Only leafs should report, but if needed for further debug, uncomment it
	//if (bError)
	//	qDebug() << "Error occurred in Action::checkForErrors of Scene \"" << parentScene_->name << "\" Event " << parentEvent_->getIndex();

	return bError;
}

void Action::run()
{
	ensureResourcesAreLoaded();
}

/// Some Actions are designed to update things and should be called frequently until the end of the Event

void Action::update() 
{
}

void Action::end() 
{
}

void Action::serializableLoad(QDataStream& dataStream)
{
	dataStream;
}

void Action::serializableSave(QDataStream& dataStream) const
{
	dataStream << getType();
}