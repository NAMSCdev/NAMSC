#include "Novel/Event/EventAll.h"

#include "Novel/Data/Scene.h"

bool Event::errorCheck(bool bComprehensive) const
{
	bool bError = false;
	for (const std::shared_ptr<Action>& action : actions_)
		bError |= action->errorCheck(bComprehensive);

	auto errorChecker = [this](bool bComprehensive)
	{
		if (bComprehensive)
			for (auto it = parentScene->events_.cbegin(); it != parentScene->events_.cend(); ++it)
				if (!(*it)->label.isEmpty() && ((*it)->label == label) && ((*it).get() != this))
				{
					qCritical() << NovelLib::ErrorType::NameDuplicate << "Duplicate labels \"" + label + "\" for Event" << getIndex() << "and Event" << (*it)->getIndex() << "in Scene \"" + parentScene->name + "\"";
					break;
				}
	};

	bError |= NovelLib::catchExceptions(errorChecker, bComprehensive);
	//if (bError)
	//	qDebug() << "An Error occurred in Event::errorCheck of Scene \"" + parentScene->name + "\" Event" << getIndex();

	return bError;
}

bool EventChoice::errorCheck(bool bComprehensive) const
{
	bool bError = Event::errorCheck(bComprehensive);

	for (const Choice& choice : choices_)
		bError |= choice.errorCheck(bComprehensive);

	//auto errorChecker = [this](bool bComprehensive)
	//{
	//};

	//bError |= NovelLib::catchExceptions(errorChecker, bComprehensive);
	if (bError)
		qDebug() << "An Error occurred in EventChoice::errorCheck of Scene \"" + parentScene->name + "\" Event" << getIndex();

	return bError;
}

bool EventDialogue::errorCheck(bool bComprehensive) const
{
	bool bError = Event::errorCheck(bComprehensive);

	for (const Sentence& sentence : sentences_)
		bError |= sentence.errorCheck(bComprehensive);

	//auto errorChecker = [this](bool bComprehensive)
	//{
	//};

	//bError |= NovelLib::catchExceptions(errorChecker, bComprehensive); 
	if (bError)
		qDebug() << "An Error occurred in EventDialogue::errorCheck of Scene \"" + parentScene->name + "\" Event" << getIndex();

	return bError;
}

bool EventEndIf::errorCheck(bool bComprehensive) const
{
	bool bError = Event::errorCheck(bComprehensive);

	auto errorChecker = [this](bool bComprehensive)
	{
		if (getIndex() <= partner_->getIndex())
		{
			qCritical() << NovelLib::ErrorType::General << "EventEndIf (" << getIndex() << ") has not a greater index that its partner EventIf (" << partner_->getIndex() << ')';
		}
	};

	bError |= NovelLib::catchExceptions(errorChecker, bComprehensive);
	if (bError)
		qDebug() << "An Error occurred in EventEndIf::errorCheck of Scene \"" + parentScene->name + "\" Event" << getIndex();

	return bError;
}

bool EventIf::errorCheck(bool bComprehensive) const
{
	bool bError = Event::errorCheck(bComprehensive);

	auto errorChecker = [this](bool bComprehensive)
	{
		//todo check condition
		return false;
	};

	bError |= NovelLib::catchExceptions(errorChecker, bComprehensive);
	if (bError)
		qDebug() << "An Error occurred in EventIf::errorCheck of Scene \"" + parentScene->name + "\" Event" << getIndex();

	return bError;
}

bool EventInput::errorCheck(bool bComprehensive) const
{
	bool bError = Event::errorCheck(bComprehensive);

	auto errorChecker = [this](bool bComprehensive)
	{
		//todo check if `regex` is valid
		//todo check if `logicalExpression` is valid
	};

	bError |= NovelLib::catchExceptions(errorChecker, bComprehensive);
	if (bError)
		qDebug() << "An Error occurred in EventInput::errorCheck of Scene \"" + parentScene->name + "\" Event" << getIndex();

	return bError;
}

bool EventJump::errorCheck(bool bComprehensive) const
{
	bool bError = Event::errorCheck(bComprehensive);

	auto errorChecker = [this](bool bComprehensive)
	{
		if (jumpToSceneName == "")
		{
			qCritical() << NovelLib::ErrorType::JumpInvalid << "EventJump is missing a jumpToSceneName";
			return;
		}
	};

	bError |= NovelLib::catchExceptions(errorChecker, bComprehensive);
	if (bError)
		qDebug() << "An Error occurred in EventJump::errorCheck of Scene \"" + parentScene->name + "\" Event" << getIndex();

	return bError;
}

bool EventWait::errorCheck(bool bComprehensive) const
{
	bool bError = Event::errorCheck(bComprehensive);

	//auto errorChecker = [this](bool bComprehensive)
	//{
	//};

	//bError |= NovelLib::catchExceptions(errorChecker, bComprehensive); 
	//if (bError)
	//	qDebug() << "An Error occurred in EventWait::errorCheck of Scene \"" + parentScene->name + "\" Event" << getIndex();

	return bError;
}