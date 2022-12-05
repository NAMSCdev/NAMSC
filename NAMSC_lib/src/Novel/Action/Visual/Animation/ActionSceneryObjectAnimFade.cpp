#include "Novel/Action/Visual/Animation/ActionSceneryObjectAnimFade.h"

#include "Novel/Data/Scene.h"

ActionSceneryObjectAnimFade::ActionSceneryObjectAnimFade(Event* const parentEvent, Scene* const parentScene) noexcept
	: ActionSceneryObjectAnim(parentEvent, parentScene)
{
}

ActionSceneryObjectAnimFade::ActionSceneryObjectAnimFade(Event* const parentEvent, Scene* const parentScene, const QString& sceneryObjectName, uint priority, uint startDelay, bool bStopAnimationAtEventEnd, uint duration, bool bAppear)
	: ActionSceneryObjectAnim(parentEvent, parentScene, sceneryObjectName, "", priority, startDelay, 1.0, 1, bStopAnimationAtEventEnd), duration(duration), bAppear(bAppear)
{
	checkForErrors(true);
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
		qDebug() << "Error occurred in ActionSceneryObjectAnimFade::checkForErrors of Scene \"" << parentScene_->name << "\" Event " << parentEvent_->getIndex();

	return bError;
}

void ActionSceneryObjectAnimFade::run()
{
}

void ActionSceneryObjectAnimFade::setOnRunListener(std::function<void(Event* const parentEvent, Scene* const parentScene, SceneryObject* sceneryObject, uint priority, uint startDelay, double speed, int timesPlayed, bool bStopAnimationAtEventEnd, uint duration, bool bAppear)> onRun) noexcept
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