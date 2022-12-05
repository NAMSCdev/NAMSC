#include "Novel/Action/Visual/ActionSceneryObjectSetImage.h"

#include "Novel/Data/Asset/AssetManager.h"
#include "Novel/Data/Scene.h"

ActionSceneryObjectSetImage::ActionSceneryObjectSetImage(Event* const parentEvent, Scene* const parentScene) noexcept
	: ActionSceneryObject(parentEvent, parentScene)
{
}

ActionSceneryObjectSetImage::ActionSceneryObjectSetImage(Event* const parentEvent, Scene* const parentScene, const QString& sceneryObjectName, const QString& assetImageName) 
	: ActionSceneryObject(parentEvent, parentScene, sceneryObjectName), assetImageName_(assetImageName)
{
	assetImage_ = AssetManager::getInstance().getAssetImageSceneryObject(assetImageName_);
	//if (assetImage_ == nullptr)
	//	qCritical() << this << NovelLib::ErrorType::AssetImageMissing << "Sprite AssetImage \"" << assetImageName_ << "\" does not exist. Definition file might be corrupted";
	checkForErrors(true);
}

ActionSceneryObjectSetImage& ActionSceneryObjectSetImage::operator=(const ActionSceneryObjectSetImage& obj) noexcept
{
	if (this == &obj) return *this;

	ActionSceneryObject::operator=(obj);
	//onRun_          = obj.onRun_;
	assetImageName_ = obj.assetImageName_;
	assetImage_     = obj.assetImage_;

	return *this;
}

bool ActionSceneryObjectSetImage::operator==(const ActionSceneryObjectSetImage& obj) const noexcept
{
	if (this == &obj) return true;

	return	ActionSceneryObject::operator==(obj)   &&
			assetImageName_ == obj.assetImageName_;// &&
			//assetImage_     == obj.assetImage_;
}

bool ActionSceneryObjectSetImage::checkForErrors(bool bComprehensive) const
{
	bool bError = ActionSceneryObject::checkForErrors(bComprehensive);

	static auto errorChecker = [&](bool bComprehensive)
	{
		if (assetImage_ == nullptr)
		{
			bError = true;
			qCritical() << this << NovelLib::ErrorType::AssetImageInvalid << "No valid Sprite AssetImage assigned. Was it deleted and not replaced?";
			if (assetImageName_ == "")
				qCritical() << this << NovelLib::ErrorType::AssetImageMissing << "Sprite AssetImage \"" << assetImageName_ << "\" does not exist. Definition file might be corrupted";
		}
	};

	bError |= NovelLib::catchExceptions(errorChecker, bComprehensive); 
	if (bError)
		qDebug() << "Error occurred in ActionSceneryObjectSetImage::checkForErrors of Scene \"" << parentScene_->name << "\" Event " << parentEvent_->getIndex();

	return bError;
}

void ActionSceneryObjectSetImage::run()
{
}

void ActionSceneryObjectSetImage::setOnRunListener(std::function<void(Event* const parentEvent, Scene* const parentScene, SceneryObject* sceneryObject, QImage* image)> onRun) noexcept
{ 
	onRun_ = onRun;
}

void ActionSceneryObjectSetImage::setAssetImage(const QString& assetImageName) noexcept
{
	AssetImage* newAssetImage = nullptr;
	newAssetImage = AssetManager::getInstance().getAssetImageSceneryObject(assetImageName);
	if (newAssetImage == nullptr)
		qCritical() << this << NovelLib::ErrorType::AssetImageMissing << "Sprite AssetImage \"" << assetImageName << "\" does not exist";
	else
	{
		assetImageName_ = assetImageName;
		assetImage_     = newAssetImage;
		checkForErrors(true);
	}
}

AssetImage* ActionSceneryObjectSetImage::getAssetImage() noexcept 
{
	return assetImage_;
}

const AssetImage* ActionSceneryObjectSetImage::getAssetImage() const noexcept 
{
	return assetImage_; 
}

QString ActionSceneryObjectSetImage::getAssetImageName() const noexcept
{ 
	return assetImageName_; 
}

void ActionSceneryObjectSetImage::acceptVisitor(ActionVisitor* visitor)
{ 
	visitor->visitActionSceneryObjectSetImage(this); 
}

/// Needed for Serialization, to know the class of an object about to be Serialization loaded
/// \return NovelLib::SerializationID corresponding to the class of a serialized object

NovelLib::SerializationID ActionSceneryObjectSetImage::getType() const noexcept 
{ 
	return NovelLib::SerializationID::ActionSetBackground; 
}

void ActionSceneryObjectSetImage::ensureResourcesAreLoaded()
{
	ActionSceneryObject::ensureResourcesAreLoaded();

	if (assetImage_->isLoaded())
		assetImage_->load();
}

void ActionSceneryObjectSetImage::serializableLoad(QDataStream& dataStream)
{
	ActionSceneryObject::serializableLoad(dataStream);
	dataStream >> assetImageName_;

	assetImage_ = AssetManager::getInstance().getAssetImageSceneryObject(assetImageName_);
//	if (assetImage_ == nullptr)
	checkForErrors();
}

void ActionSceneryObjectSetImage::serializableSave(QDataStream& dataStream) const
{
	ActionSceneryObject::serializableSave(dataStream);
	dataStream << assetImageName_;
}