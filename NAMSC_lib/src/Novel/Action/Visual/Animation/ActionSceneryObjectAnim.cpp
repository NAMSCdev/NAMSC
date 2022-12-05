#include "Novel/Action/Visual/Animation/ActionSceneryObjectAnim.h"

#include "Novel/Data/Scene.h"

template <class AnimNode>
ActionSceneryObjectAnim<AnimNode>::ActionSceneryObjectAnim(Event* const parentEvent, Scene* const parentScene) noexcept
	: ActionSceneryObject(parentEvent, parentScene)
{
}

template <class AnimNode>
ActionSceneryObjectAnim<AnimNode>::ActionSceneryObjectAnim(Event* const parentEvent, Scene* const parentScene, const QString& sceneryObjectName, const QString& assetAnimName, uint priority, uint startDelay, double speed, int timesPlayed, bool bStopAnimationAtEventEnd)
	: ActionSceneryObject(parentEvent, parentScene, sceneryObjectName), assetAnimName_(assetAnimName), priority(priority), startDelay(startDelay), speed(speed), timesPlayed(timesPlayed), bStopAnimationAtEventEnd(bStopAnimationAtEventEnd)
{
	//checkForErrors(true);
}

template <class AnimNode> 
ActionSceneryObjectAnim<AnimNode>& ActionSceneryObjectAnim<AnimNode>::operator=(const ActionSceneryObjectAnim<AnimNode>&obj) noexcept
{
	if (this == &obj)
		return *this;

	ActionSceneryObject::operator=(obj);
	assetAnimName_           = obj.assetAnimName_;
	assetAnim_               = obj.assetAnim_;
	startDelay               = obj.startDelay;
	speed                    = obj.speed;
	timesPlayed              = obj.timesPlayed;
	bStopAnimationAtEventEnd = obj.bStopAnimationAtEventEnd;

	return *this;
}

template <class AnimNode> 
bool ActionSceneryObjectAnim<AnimNode>::operator==(const ActionSceneryObjectAnim<AnimNode>& obj) const noexcept
{
	if (this == &obj)
		return *this;

	return	ActionSceneryObject::operator==(obj)                    &&
			assetAnimName_ == obj.assetAnimName_                    &&
			//assetAnim_     == obj.assetAnim_                        &&
			startDelay     == obj.startDelay                        &&
			speed          == obj.speed                             &&
			timesPlayed    == obj.timesPlayed                       &&
			bStopAnimationAtEventEnd == obj.bStopAnimationAtEventEnd;
}

template <class AnimNode>
bool ActionSceneryObjectAnim<AnimNode>::checkForErrors(bool bComprehensive) const
{
	bool bError = ActionSceneryObject::checkForErrors(bComprehensive);

	static auto errorChecker = [&](bool bComprehensive)
	{
		if (assetAnim_ == nullptr)
		{
			bError = true;
			qCritical() << this << NovelLib::ErrorType::AssetAnimInvalid << "No valid AnimAsset assigned. Was it deleted and not replaced?";
			if (assetAnimName_ != "")
				qCritical() << this << NovelLib::ErrorType::AssetAnimMissing << "AssetAnim \"" << assetAnimName_ << "\" does not exist or read. Definition file might be corrupted";
		}

		bError |= assetAnim_->checkForErrors(bComprehensive);
	};

	bError |= NovelLib::catchExceptions(errorChecker, bComprehensive); 
	//if (bError)
	//	qDebug() << "Error occurred in ActionSceneryObjectAnim::checkForErrors of Scene \"" << parentScene_->name << "\" Event " << parentEvent_->getIndex();

	return bError;
}

template <class AnimNode>
void ActionSceneryObjectAnim<AnimNode>::ensureResourcesAreLodaded()
{
	if (assetAnim_.isLoaded())
		assetAnim_.load();
}

//SetAssetAnim is defined in concrete ActionSceneryObjectAnims
template<typename AnimNode>
AssetAnim<AnimNode>* ActionSceneryObjectAnim<AnimNode>::getAssetAnim() noexcept
{ 
	return assetAnim_; 
}

template<typename AnimNode>
const AssetAnim<AnimNode>* ActionSceneryObjectAnim<AnimNode>::getAssetAnim() const noexcept
{ 
	return assetAnim_; 
}

template<typename AnimNode>
QString ActionSceneryObjectAnim<AnimNode>::getAssetAnimName() const noexcept
{
	return assetAnimName_; 
}

template<typename AnimNode>
void ActionSceneryObjectAnim<AnimNode>::serializableLoad(QDataStream& dataStream)
{
	ActionSceneryObject::serializableLoad(dataStream);
	dataStream >> assetAnimName_ >> startDelay >> speed >> timesPlayed >> bStopAnimationAtEventEnd;
	//assetAnim_ is loaded in a derived class
}

template<typename AnimNode>
void ActionSceneryObjectAnim<AnimNode>::serializableSave(QDataStream& dataStream) const
{
	ActionSceneryObject::serializableSave(dataStream);
	dataStream << assetAnimName_ << startDelay << speed << timesPlayed << bStopAnimationAtEventEnd;
}