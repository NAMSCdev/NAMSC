#include "Novel/Action/Visual/Animation/ActionSceneryObjectAnimFade.h"

#include "Novel/Data/Scene.h"

ActionSceneryObjectAnimFade::ActionSceneryObjectAnimFade(Event* const parentEvent) noexcept
	: ActionSceneryObjectAnim(parentEvent)
{
}

ActionSceneryObjectAnimFade::ActionSceneryObjectAnimFade(Event* const parentEvent, const QString& sceneryObjectName, uint priority, uint startDelay, bool bStopAnimationAtEventEnd, uint duration, bool bAppear)
	: ActionSceneryObjectAnim(parentEvent, sceneryObjectName, "", priority, startDelay, 1.0, 1, bStopAnimationAtEventEnd), duration(duration), bAppear(bAppear)
{
	checkForErrors(true);
}

ActionSceneryObjectAnimFade::ActionSceneryObjectAnimFade(const ActionSceneryObjectAnimFade& obj) noexcept
	: ActionSceneryObjectAnim(obj.parentEvent)
{
	//TODO: change to swap trick for more efficency
	*this = obj;
}

ActionSceneryObjectAnimFade& ActionSceneryObjectAnimFade::operator=(const ActionSceneryObjectAnimFade& obj) noexcept
{
	if (this == &obj) return *this;

	ActionSceneryObjectAnim::operator=(obj);
	//onRun_             = obj.onRun_;
	duration           = obj.duration;
	bAppear            = obj.bAppear;

	return *this;
}

bool ActionSceneryObjectAnimFade::operator==(const ActionSceneryObjectAnimFade& obj) const noexcept
{
	if (this == &obj) return true;

	return	ActionSceneryObjectAnim::operator==(obj) &&
			duration != obj.duration                 &&
			bAppear  != obj.bAppear;           
}

bool ActionSceneryObjectAnimFade::checkForErrors(bool bComprehensive) const
{
	bool bError = ActionSceneryObjectAnim::checkForErrors(bComprehensive);

	//static auto errorChecker = [&](bool bComprehensive)
	//{
	//};

	//bError |= NovelLib::catchExceptions(errorChecker, bComprehensive);
	if (bError)
		qDebug() << "Error occurred in ActionSceneryObjectAnimFade::checkForErrors of Scene \"" + parentEvent->parentScene->name + "\" Event" << parentEvent->getIndex();

	return bError;
}

Action* ActionSceneryObjectAnimFade::clone() const
{
	ActionSceneryObjectAnimFade* clone = new ActionSceneryObjectAnimFade(*this);
	return clone;
}

void ActionSceneryObjectAnimFade::run()
{
}

void ActionSceneryObjectAnimFade::setOnRunListener(std::function<void(Event* const parentEvent, SceneryObject* sceneryObject, uint priority, uint startDelay, double speed, int timesPlayed, bool bStopAnimationAtEventEnd, uint duration, bool bAppear)> onRun) noexcept
{
	onRun_ = onRun;
}

NovelLib::SerializationID ActionSceneryObjectAnimFade::getType() const noexcept
{
	return NovelLib::SerializationID::ActionSceneryObjectAnimFade; 
}

void ActionSceneryObjectAnimFade::serializableLoad(QDataStream& dataStream)
{
	ActionSceneryObjectAnim::serializableLoad(dataStream);
	dataStream >> duration >> bAppear;
	checkForErrors();
}

void ActionSceneryObjectAnimFade::serializableSave(QDataStream& dataStream) const
{
	ActionSceneryObjectAnim::serializableSave(dataStream);
	dataStream << duration << bAppear;
}