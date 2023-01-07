#include "Novel/Data/Visual/Scenery/Character.h"

#include "Novel/Data/Novel.h"

Character::Character(const QString& name, const QString& assetImageName, const QPoint pos, const QSizeF scale, double rotationDegree, const QVarLengthArray<double, 4>& colorMultiplier, double alphaMultiplier, bool bVisible, const QString& defaultVoiceName)
	: SceneryObject(name, assetImageName, pos, scale, rotationDegree, colorMultiplier, alphaMultiplier, bVisible), defaultVoiceName_(defaultVoiceName)
{
	//defaultVoice_ = Novel::getInstance().getVoice(defaultVoiceName);
	checkForErrors(true);
}

Character& Character::operator=(Character obj) noexcept
{
	if (this == &obj) return *this;

	std::swap(this->name,              obj.name);
	std::swap(this->assetImageName_,   obj.assetImageName_);
	std::swap(this->assetImage_,       obj.assetImage_);
	std::swap(this->pos,               obj.pos);
	std::swap(this->scale,             obj.scale);
	std::swap(this->rotationDegree,    obj.rotationDegree);
	std::swap(this->colorMultiplier,   obj.colorMultiplier);
	std::swap(this->alphaMultiplier,   obj.alphaMultiplier);
	std::swap(this->bVisible,          obj.bVisible);
	std::swap(this->defaultVoiceName_, obj.defaultVoiceName_);
	std::swap(this->defaultVoice_,     obj.defaultVoice_);

	return *this;
}

bool Character::operator==(const Character& obj) const noexcept
{
	if (this == &obj) return true;

	return	SceneryObject::operator==(obj)             &&
			defaultVoiceName_ == obj.defaultVoiceName_; //&&
			//defaultVoice_     == defaultVoice_;
}

bool Character::checkForErrors(bool bComprehensive) const
{
	bool bError = SceneryObject::checkForErrors(bComprehensive);

	static auto errorChecker = [&](bool bComprehensive)
	{
		//Check if the name is undefined
		//if (defaultVoiceName_ == "")
		//{
		//	bError = true;
		//	qCritical() << NovelLib::ErrorType::VoiceInvalid << "No Voice assigned. Was it deleted and not replaced?";
		//}
		//Check if there is a Voice with this name in the Novel's container 
		//else if (Novel::getInstance().getVoice(defaultVoiceName_) == nullptr)
		//{
		//	bError = true;
		//	qCritical() << NovelLib::ErrorType::VoiceMissing << "Voice \"" + defaultVoiceName_ + "\" does not exist. Definition file might be corrupted";
		//}
	};

	bError |= NovelLib::catchExceptions(errorChecker, bComprehensive); 
	if (bError)
		qDebug() << "An Error occurred in Character::checkForErrors (object's name: \"" + name + "\")";

	return bError;
}

void Character::setDefaultVoice(const QString& defaultVoiceName, Voice* voice) noexcept
{
	if (voice != nullptr)
	{
		defaultVoiceName_ = defaultVoiceName;
		defaultVoice_     = voice;
		checkForErrors(true);
		return;
	}

	Voice* newVoice = nullptr;
	newVoice = Novel::getInstance().getVoice(defaultVoiceName);
	if (newVoice == nullptr)
		qCritical() << NovelLib::ErrorType::VoiceMissing << "Voice \"" + defaultVoiceName + "\" does not exist";
	else
	{
		defaultVoiceName_ = defaultVoiceName;
		defaultVoice_     = newVoice;
		checkForErrors(true);
	}
}

Voice* Character::getDefaultVoice() noexcept
{
	return defaultVoice_; 
}

const Voice* Character::getDefaultVoice() const noexcept
{ 
	return defaultVoice_; 
}

QString Character::getDefaultVoiceName() const noexcept
{ 
	return defaultVoiceName_; 
}

void Character::serializableSave(QDataStream& dataStream) const
{
	SceneryObject::serializableSave(dataStream);
	dataStream << defaultVoiceName_;
}

void Character::serializableLoad(QDataStream& dataStream)
{
	SceneryObject::serializableLoad(dataStream);
	dataStream >> defaultVoiceName_;
	defaultVoice_ = Novel::getInstance().getVoice(defaultVoiceName_);

	checkForErrors();
}