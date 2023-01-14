#include "Novel/Action/Visual/ActionSetBackground.h"

#include "Novel/Data/Scene.h"

ActionSetBackground::ActionSetBackground(Event* const parentEvent) noexcept
	: Action(parentEvent)
{
}

//If you add/remove a member field, remember to update these
//  MEMBER_FIELD_SECTION_CHANGE BEGIN

void swap(ActionSetBackground& first, ActionSetBackground& second) noexcept
{
	using std::swap;
	//Static cast, because no check is needed and it's faster
	swap(static_cast<Action&>(first), static_cast<Action&>(second));
	swap(first.assetImageName_, second.assetImageName_);
	swap(first.transitionType,  second.transitionType);
	swap(first.transitionTime,  second.transitionTime);
	swap(first.assetImage_,     second.assetImage_);
	swap(first.onRun_,          second.onRun_);
}

ActionSetBackground::ActionSetBackground(Event* const parentEvent, const QString& assetImageName, const TransitionType transitionType, uint transitionTime, AssetImage* assetImage)
	: Action(parentEvent),
	assetImageName_(assetImageName), 
	transitionType(transitionType), 
	transitionTime(transitionTime), 
	assetImage_(assetImage)
{
	if (!assetImage_)
		assetImage_ = AssetManager::getInstance().getAssetImageSceneryBackground(assetImageName_);

	errorCheck(true);
}

//deleted
//ActionSetBackground::ActionSetBackground(const ActionSetBackground& obj) noexcept
//	: Action(obj.parentEvent), assetImageName_(obj.assetImageName_), 
//	assetImage_(obj.assetImage_),
//	transitionType(obj.transitionType), 
//	transitionTime(obj.transitionTime), 
//	onRun_(obj.onRun_)
//{
//}

//deleted
//bool ActionSetBackground::operator==(const ActionSetBackground& obj) const noexcept
//{
//	if (this == &obj) return true;
//
//	return Action::operator==(obj) &&
//		   assetImageName_ == obj.assetImageName_ &&
//		   //assetImage_     == obj.assetImage_     &&
//		   transitionType == obj.transitionType &&
//		   transitionTime == obj.transitionTime;
//}

void ActionSetBackground::setOnRunListener(std::function<void(const Event* const parentEvent, const QImage* const background, const ActionSetBackground::TransitionType& transitionType, const uint& transitionTime)> onRun) noexcept
{
	onRun_ = onRun;
}

void ActionSetBackground::serializableLoad(QDataStream& dataStream)
{
	Action::serializableLoad(dataStream);
	dataStream >> assetImageName_ >> transitionType >> transitionTime;

	assetImage_ = AssetManager::getInstance().getAssetImageSceneryBackground(assetImageName_);
	errorCheck();
}

void ActionSetBackground::serializableSave(QDataStream& dataStream) const
{
	Action::serializableSave(dataStream);
	dataStream << assetImageName_ << transitionType << transitionTime;
}

//  MEMBER_FIELD_SECTION_CHANGE END

ActionSetBackground::ActionSetBackground(ActionSetBackground&& obj) noexcept
	: Action(obj.parentEvent)
{
	swap(*this, obj);
}

//deleted
//ActionSetBackground& ActionSetBackground::operator=(ActionSetBackground obj) noexcept
//{
//	if (this == &obj) return *this;
//
//	swap(*this, obj);
//
//	return *this;
//}

void ActionSetBackground::acceptVisitor(ActionVisitor* visitor) 
{
	visitor->visitActionSetBackground(this); 
}

QString ActionSetBackground::getAssetImageName() const noexcept
{
	return assetImageName_;
}

const AssetImage* ActionSetBackground::getAssetImage() const noexcept
{
	return assetImage_;
}

AssetImage* ActionSetBackground::getAssetImage() noexcept
{
	return assetImage_;
}

void ActionSetBackground::setAssetImage(const QString& assetImageName, AssetImage* assetImage) noexcept
{
	if (assetImage)
	{
		if (assetImage->name != assetImageName)
		{
			qCritical() << NovelLib::ErrorType::AssetImageInvalid << "AssetImage's name missmatch (assetImageName=\"" + assetImageName + "\", assetImage->name=\"" + assetImage->name + "\")";
			return;
		}
	}
	else assetImage = AssetManager::getInstance().getAssetImageSceneryObject(assetImageName);

	if (!assetImage)
	{
		qCritical() << NovelLib::ErrorType::AssetImageMissing << "Sprite AssetImage \"" + assetImageName + "\" does not exist";
		return;
	}
	assetImageName_ = assetImageName;
	assetImage_     = assetImage;
	errorCheck(true);
}

NovelLib::SerializationID ActionSetBackground::getType() const noexcept 
{ 
	return NovelLib::SerializationID::ActionSetBackground; 
}