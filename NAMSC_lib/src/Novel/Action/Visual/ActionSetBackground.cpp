#include "Novel/Action/Visual/ActionSetBackground.h"

#include "Novel/Data/Scene.h"

ActionSetBackground::ActionSetBackground(Event* const parentEvent) noexcept
	: Action(parentEvent)
{
}

ActionSetBackground::ActionSetBackground(Event* const parentEvent, const QString& assetImageName, const  TransitionType transitionType, double transitionTime)
	: Action(parentEvent), assetImageName_(assetImageName), transitionType(transitionType), transitionTime(transitionTime)
{
	assetImage_ = AssetManager::getInstance().getAssetImageSceneryBackground(assetImageName_);

	//if (assetImage_ == nullptr)
	//	qCritical() << NovelLib::ErrorType::AssetImageMissing << "Background AssetImage \"" + assetImageName_ + "\" does not exist. Definition file might be corrupted";
	checkForErrors(true);
}

ActionSetBackground::ActionSetBackground(const ActionSetBackground& obj) noexcept
	: Action(obj.parentEvent)
{
	//TODO: change to swap trick for more efficency
	*this = obj;
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
			qCritical() << NovelLib::ErrorType::AssetImageInvalid << "No valid Background AssetImage assigned. Was it deleted and not replaced?";
			if (assetImageName_ == "")
				qCritical() << NovelLib::ErrorType::AssetImageMissing << "Background AssetImage \"" + assetImageName_ + "\" does not exist. Definition file might be corrupted";
		}
	};

	bError |= NovelLib::catchExceptions(errorChecker, bComprehensive); 
	if (bError)
		qDebug() << "Error occurred in ActionSetBackground::checkForErrors of Scene \"" + parentEvent->parentScene->name + "\" Event" << parentEvent->getIndex();

	return bError;
}

Action* ActionSetBackground::clone() const
{
	ActionSetBackground* clone = new ActionSetBackground(*this);
	return clone;
}

void ActionSetBackground::acceptVisitor(ActionVisitor* visitor) 
{
	visitor->visitActionSetBackground(this); 
}

void ActionSetBackground::run()
{

}

void ActionSetBackground::setOnRunListener(std::function<void(Event* const parentEvent, QImage* background, ActionSetBackground::TransitionType transitionType, double transitionTime)> onRun) noexcept
{ 
	onRun_ = onRun;
}

void ActionSetBackground::setAssetImage(const QString& assetImageName) noexcept
{
	AssetImage* newAssetImage = nullptr;
	newAssetImage = AssetManager::getInstance().getAssetImageSceneryBackground(assetImageName);
	if (newAssetImage == nullptr)
		qCritical() << NovelLib::ErrorType::AssetImageMissing << "Background AssetImage \"" + assetImageName + "\" does not exist";
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
	//	qCritical() << NovelLib::ErrorType::AssetImageMissing << "Background AssetImage \"" + assetImageName_ + "\" does not exist. Definition file might be corrupted";
	checkForErrors();
}

void ActionSetBackground::serializableSave(QDataStream& dataStream) const
{
	Action::serializableSave(dataStream);
	dataStream << assetImageName_ << transitionType << transitionTime;
}