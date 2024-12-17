#pragma once
#include "pvnLib/Novel/Action/Visual/ActionSceneryObject.h"

#include "pvnLib/Novel/Data/Asset/AssetAnim.h"
#include "pvnLib/Novel/Data/Visual/Animation/AnimatorSceneryObjectInterface.h"

///Creates AnimatorSceneryObject and adds it to the Scenery, which will perform some Animation on a SceneryObject
template<typename AnimNode>
class ActionSceneryObjectAnim : public ActionSceneryObject
{
public:
	/// \param sceneryObject Copies the SceneryObject pointer. It's okay to leave it as nullptr, as it will be loaded later. This is a very minor optimization 
	/// \param assetAnim Copies the AssetAnim pointer. It's okay to leave it as nullptr, as it will be loaded later. This is a very minor optimization 
	/// \param priority Animations can be queued, this is the priority in the queue (lower number equals higher priority)
	/// \param startDelay In milliseconds
	/// \param speed Animation speed multiplier
	/// \param Remember to copy the description to the constructor parameter description as well, if it changes
	/// \param timesPlayed `-1` means infinite times
	/// \exception Error Couldn't find the SceneryObject named `sceneryObjectName`
	explicit ActionSceneryObjectAnim(Event* const parentEvent, const QString& sceneryObjectName = "", const QString& assetAnimName = "", uint priority = 0, uint startDelay = 0, double speed = 1.0, int timesPlayed = 1, bool bFinishAnimationAtEventEnd = false, SceneryObject* sceneryObject = nullptr, AssetAnim<AnimNode>* assetAnim = nullptr)
		: ActionSceneryObject(parentEvent, sceneryObjectName, sceneryObject),
		assetAnimName_(assetAnimName),
		priority(priority),
		startDelay(startDelay),
		speed(speed),
		timesPlayed(timesPlayed),
		bFinishAnimationAtEventEnd(bFinishAnimationAtEventEnd),
		assetAnim_(assetAnim)
	{
	}

	bool operator==(const ActionSceneryObjectAnim<AnimNode>& obj) const noexcept
	{
		if (this == &obj)
			return true;

		return assetAnimName_             == obj.assetAnimName_             &&
			   priority                   == obj.priority                   &&
			   startDelay                 == obj.startDelay                 &&
			   speed                      == obj.speed                      &&
			   timesPlayed                == obj.timesPlayed                &&
			   bFinishAnimationAtEventEnd == obj.bFinishAnimationAtEventEnd;
	}

	bool operator!=(const ActionSceneryObjectAnim<AnimNode>& obj) const noexcept = default;
	//Makes it abstract
	virtual ~ActionSceneryObjectAnim() = 0;

	void swapPrivate(ActionSceneryObjectAnim& second) noexcept
	{
		using std::swap;
		swap(this->assetAnimName_, second.assetAnimName_);
		swap(this->assetAnim_,     second.assetAnim_);
		swap(this->animator_,      second.animator_);
	}

	/// \exception Error `sceneryObject_`/`assetAnim_` is invalid
	/// \return Whether an Error has occurred
	virtual bool errorCheck(bool bComprehensive = false) const override
	{
		bool bError = ActionSceneryObject::errorCheck(bComprehensive);

		auto errorChecker = [this](bool bComprehensive)
		{
			if (assetAnim_ == nullptr)
			{
				qCritical() << NovelLib::ErrorType::AssetAnimInvalid << "No valid AnimAsset assigned. Was it deleted and not replaced?";
				if (!assetAnimName_.isEmpty())
					qCritical() << NovelLib::ErrorType::AssetAnimMissing << "AssetAnim \"" + assetAnimName_ + "\" does not exist or read. Definition file might be corrupted";
			}
			else assetAnim_->errorCheck(bComprehensive);
		};

		bError |= NovelLib::catchExceptions(errorChecker, bComprehensive);
		//if (bError)
		//	qDebug() << "Error occurred in ActionSceneryObjectAnim::errorCheck of Scene \"" + parentEvent->parentScene->name + "\" Event" << parentEvent->getIndex();

		return bError;
	}

	void ensureResourcesAreLodaded()
	{
		if (assetAnim_->isLoaded())
			assetAnim_->load();
	}

	QString getAssetAnimName()                const noexcept
	{
		return assetAnimName_;
	}
	
	const AssetAnim<AnimNode>* getAssetAnim() const noexcept
	{
		return assetAnim_;
	}
	
	AssetAnim<AnimNode>* getAssetAnim()       noexcept
	{
		return assetAnim_;
	}

	//SetAssetAnim is defined in concrete ActionSceneryObjectAnims
	virtual void setAssetAnim(const QString& assetAnimName, AssetAnim<AnimNode>* assetAnim = nullptr) noexcept = 0;

	//[Meta] Remember to copy the description to the constructor (and all delegating) parameter description as well, if it changes
	/// Animations can be queued, this is the priority in the queue (lower number equals higher priority)
	uint priority   = 0;

	//[Meta] Remember to copy the description to the constructor (and all delegating) parameter description as well, if it changes
	/// In milliseconds
	uint startDelay = 0;

	//[Meta] Remember to copy the description to the constructor (and all delegating) parameter description as well, if it changes
	/// Animation speed multiplier
	double speed    = 1.0;

	//[Meta] Remember to copy the description to the constructor (and all delegating) parameter description as well, if it changes
	/// `-1` means infinite times
	int timesPlayed = 1;

	bool bFinishAnimationAtEventEnd = false;

protected:
	QString	             assetAnimName_ = "";
	AssetAnim<AnimNode>* assetAnim_     = nullptr;

private:
	/// Tracking pointer for the created Animator, so we know what to remove in `void end()`
	AnimatorSceneryObjectInterface<AnimNode>* animator_ = nullptr;

public:
	//---SERIALIZATION---
	/// Loading an object from a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to read from
	virtual void serializableLoad(QDataStream& dataStream) override
	{
		ActionSceneryObject::serializableLoad(dataStream);
		dataStream >> assetAnimName_ >> priority >> startDelay >> speed >> timesPlayed >> bFinishAnimationAtEventEnd;
		//assetAnim_ is loaded in a derived class
	}

	/// Saving an object to a binary file
	/// \param dataStream Stream (presumably connected to a QFile) to save to
	virtual void serializableSave(QDataStream& dataStream) const override
	{
		ActionSceneryObject::serializableSave(dataStream);
		dataStream << assetAnimName_ << priority << startDelay << speed << timesPlayed << bFinishAnimationAtEventEnd;
	}
};

template <class AnimNode>
ActionSceneryObjectAnim<AnimNode>::~ActionSceneryObjectAnim() = default;

template<typename AnimNode>
void swap(ActionSceneryObjectAnim<AnimNode>& first, ActionSceneryObjectAnim<AnimNode>& second) noexcept
{
	using std::swap;
	//Static cast, because no check is needed and it's faster
	swap(static_cast<ActionSceneryObject&>(first), static_cast<ActionSceneryObject&>(second));
	swap(first.priority,                   second.priority);
	swap(first.startDelay,                 second.startDelay);
	swap(first.speed,                      second.speed);
	swap(first.timesPlayed,                second.timesPlayed);
	swap(first.bFinishAnimationAtEventEnd, second.bFinishAnimationAtEventEnd);
	first.swapPrivate(second);
}