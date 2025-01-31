#include "pvnLib/Novel/Action/Action.h"

#include "pvnLib/Novel/Data/Scene.h"

Action::~Action() = default;

// If you add/remove a member field to this class, remember to update these
//  MEMBER_FIELD_SECTION_CHANGE BEGIN

void swap(Action& first, Action& second) noexcept
{
	using std::swap;
}

Action::Action(Event* const parentEvent) noexcept
	: parentEvent(parentEvent)
{
}

void Action::serializableLoad(QDataStream& dataStream)
{
}

void Action::serializableSave(QDataStream& dataStream) const
{
	dataStream << getType();
}

//  MEMBER_FIELD_SECTION_CHANGE END

Action::Action(Action&& obj) noexcept
	: Action(obj.parentEvent)
{
	swap(*this, obj);
}

bool Action::errorCheck(bool bComprehensive) const
{
	bool bError = false;

	//auto errorChecker = [this](bool bComprehensive)
	//{
	//};

	//bError |= NovelLib::catchExceptions(errorChecker, bComprehensive);
	
	//Only leafs should report, but if needed for further debug, uncomment it
	//if (bError)
	//	qDebug() << "Error occurred in Action::errorCheck of Scene \"" + parentEvent->parentScene->name + "\" Event" << parentEvent->getIndex();

	return bError;
}

void Action::ensureResourcesAreLoaded()
{
}

void Action::run()
{
	ensureResourcesAreLoaded();
}

void Action::update() 
{
}

void Action::end() 
{
}

void Action::syncWithSave()
{
}