#include "Novel/Action/Visual/ActionSetBackground.h"

#include "Novel/Data/Scene.h"

ActionSetBackground::ActionSetBackground(Event* const parentEvent, Scene* const parentScene) noexcept
	: Action(parentEvent, parentScene)
{
}

ActionSetBackground::ActionSetBackground(Event* const parentEvent, Scene* const parentScene, const QString& assetImageName, const  TransitionType transitionType, double transitionTime)
	: Action(parentEvent, parentScene), assetImageName_(assetImageName), transitionType(transitionType), transitionTime(transitionTime)
{
	assetImage_ = AssetManager::getInstance().getAssetImageSceneryBackground(assetImageName_);

	//if (assetImage_ == nullptr)
	//	qCritical() << this << NovelLib::ErrorType::AssetImageMissing << "Background AssetImage \"" << assetImageName_ << "\" does not exist. Definition file might be corrupted";
	checkForErrors(true);
}

ActionSetBackground& ActionSetBackground::operator=(const ActionSetBackground& obj) noexcept
{
	if (this == &obj) return *this;

	Action::operator=(obj);
	//onRun_          = obj.onRun_;
	assetImageName_ = obj.assetImageName_;
	assetImage_     = obj.assetImage_;
	transitionType  = obj.transitionType;
	transitionTime  = obj.transitionTime;

	return *this;
}

bool ActionSetBackground::operator==(const ActionSetBackground& obj) const noexcept
{
	if (this == &obj) return true;

	return	Action::operator==(obj)                &&
			assetImageName_ == obj.assetImageName_ &&
			//assetImage_     == obj.assetImage_     &&
			transitionType  == obj.transitionType  &&
			transitionTime  == obj.transitionTime;
}

bool ActionSetBackground::checkForErrors(bool bComprehensive) const
{
	bool bError = Action::checkForErrors(bComprehensive);

	static auto errorChecker = [&](bool bComprehensive)
	{
		if (assetImage_ == nullptr)
		{
			bError = true;
			qCritical() << this << NovelLib::ErrorType::AssetImageInvalid << "No valid Background AssetImage assigned. Was it deleted and not replaced?";
			if (assetImageName_ == "")
				qCritical() << this << NovelLib::ErrorType::AssetImageMissing << "Background AssetImage \"" << assetImageName_ << "\" does not exist. Definition file might be corrupted";
		}
	};

	bError |= NovelLib::catchExceptions(errorChecker, bComprehensive); 
	if (bError)
		qDebug() << "Error occurred in ActionSetBackground::checkForErrors of Scene \"" << parentScene_->name << "\" Event " << parentEvent_->getIndex();

	return bError;
}


/// Sets a function pointer that is called (if not nullptr) after the ActionSetBackground's `void run()` allowing for data read

void ActionSetBackground::acceptVisitor(ActionVisitor* visitor) 
{
	visitor->visitActionSetBackground(this); 
}

void ActionSetBackground::setOnRunListener(std::function<void(Event* const parentEvent, Scene* const parentScene, QImage* background, ActionSetBackground::TransitionType transitionType, double transitionTime)> onRun) noexcept
{ 
	onRun_ = onRun;
}

void ActionSetBackground::setAssetImage(const QString& assetImageName) noexcept
{
	AssetImage* newAssetImage = nullptr;
	newAssetImage = AssetManager::getInstance().getAssetImageSceneryBackground(assetImageName);
	if (newAssetImage == nullptr)
		qCritical() << this << NovelLib::ErrorType::AssetImageMissing << "Background AssetImage \"" << assetImageName << "\" does not exist";
	else
	{
		assetImageName_ = assetImageName;
		assetImage_     = newAssetImage;
		checkForErrors(true);
	}
}

AssetImage* ActionSetBackground::getAssetImage() noexcept
{ 
	return assetImage_; 
}

const AssetImage* ActionSetBackground::getAssetImage() const noexcept 
{ 
	return assetImage_; 
}

QString ActionSetBackground::getAssetImageName() const noexcept
{ 
	return assetImageName_; 
}

NovelLib::SerializationID ActionSetBackground::getType() const noexcept 
{ 
	return NovelLib::SerializationID::ActionSetBackground; 
}

void ActionSetBackground::serializableLoad(QDataStream& dataStream)
{
	Action::serializableLoad(dataStream);
	dataStream >> assetImageName_ >> transitionType >> transitionTime;

	assetImage_ = AssetManager::getInstance().getAssetImageSceneryBackground(assetImageName_);
	//if (assetImage_ == nullptr)
	//	qCritical() << this << NovelLib::ErrorType::AssetImageMissing << "Background AssetImage \"" << assetImageName_ << "\" does not exist. Definition file might be corrupted";
	checkForErrors();
}

void ActionSetBackground::serializableSave(QDataStream& dataStream) const
{
	Action::serializableSave(dataStream);
	dataStream << assetImageName_ << transitionType << transitionTime;
}