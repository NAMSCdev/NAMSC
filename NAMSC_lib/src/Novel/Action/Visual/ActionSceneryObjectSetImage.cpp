#include "Novel/Action/Visual/ActionSceneryObjectSetImage.h"

#include "Novel/Data/Asset/AssetManager.h"
#include "Novel/Data/Scene.h"

ActionSceneryObjectSetImage::ActionSceneryObjectSetImage(Event* const parentEvent) noexcept
	: ActionSceneryObject(parentEvent)
{
}

//If you add/remove a member field, remember to update these
//  MEMBER_FIELD_SECTION_CHANGE BEGIN

void swap(ActionSceneryObjectSetImage& first, ActionSceneryObjectSetImage& second) noexcept
{
	using std::swap;
	//Static cast, because no check is needed and it's faster
	swap(static_cast<ActionSceneryObject&>(first), static_cast<ActionSceneryObject&>(second));
	swap(first.assetImageName_, second.assetImageName_);
	swap(first.assetImage_,     second.assetImage_);
	swap(first.onRun_,          second.onRun_);
}

ActionSceneryObjectSetImage::ActionSceneryObjectSetImage(Event* const parentEvent, const QString& sceneryObjectName, const QString& assetImageName, SceneryObject* sceneryObject, AssetImage* assetImage)
	: ActionSceneryObject(parentEvent, sceneryObjectName, sceneryObject),
	assetImageName_(assetImageName), 
	assetImage_(assetImage)
{
	if (!assetImage_)
		assetImage_ = AssetManager::getInstance().getAssetImageSceneryObject(assetImageName_);
	errorCheck(true);
}

ActionSceneryObjectSetImage::ActionSceneryObjectSetImage(const ActionSceneryObjectSetImage& obj) noexcept
	: ActionSceneryObject(obj.parentEvent, obj.sceneryObjectName_, obj.sceneryObject_), 
	assetImageName_(obj.assetImageName_),
	assetImage_(obj.assetImage_), 
	onRun_(obj.onRun_)
{
}

bool ActionSceneryObjectSetImage::operator==(const ActionSceneryObjectSetImage& obj) const noexcept
{
	if (this == &obj) return true;

	return	ActionSceneryObject::operator==(obj)   &&
			assetImageName_ == obj.assetImageName_;// &&
			//assetImage_     == obj.assetImage_;
}

void ActionSceneryObjectSetImage::setOnRunListener(std::function<void(const Event* const parentEvent, const SceneryObject* const sceneryObject, const QImage* const image)> onRun) noexcept
{
	onRun_ = onRun;
}

void ActionSceneryObjectSetImage::serializableLoad(QDataStream& dataStream)
{
	ActionSceneryObject::serializableLoad(dataStream);
	dataStream >> assetImageName_;

	if (!assetImageName_.isEmpty())
		assetImage_ = AssetManager::getInstance().getAssetImageSceneryObject(assetImageName_);
	errorCheck();
}

void ActionSceneryObjectSetImage::serializableSave(QDataStream& dataStream) const
{
	ActionSceneryObject::serializableSave(dataStream);
	dataStream << assetImageName_;
}

//  MEMBER_FIELD_SECTION_CHANGE END

ActionSceneryObjectSetImage::ActionSceneryObjectSetImage(ActionSceneryObjectSetImage&& obj) noexcept
	: ActionSceneryObject(obj.parentEvent)
{
	swap(*this, obj);
}

ActionSceneryObjectSetImage& ActionSceneryObjectSetImage::operator=(ActionSceneryObjectSetImage obj) noexcept
{
	if (this == &obj) return *this;

	swap(*this, obj);

	return *this;
}

QString ActionSceneryObjectSetImage::getAssetImageName() const noexcept
{
	return assetImageName_;
}

const AssetImage* ActionSceneryObjectSetImage::getAssetImage() const noexcept
{
	return assetImage_;
}

AssetImage* ActionSceneryObjectSetImage::getAssetImage() noexcept 
{
	return assetImage_;
}

void ActionSceneryObjectSetImage::setAssetImage(const QString& assetImageName, AssetImage* assetImage) noexcept
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

void ActionSceneryObjectSetImage::acceptVisitor(ActionVisitor* visitor)
{ 
	visitor->visitActionSceneryObjectSetImage(this); 
}

NovelLib::SerializationID ActionSceneryObjectSetImage::getType() const noexcept 
{ 
	return NovelLib::SerializationID::ActionSetBackground; 
}