#include "Novel/Data/Visual/Scenery/Character.h"

#include "Novel/Data/Novel.h"

//If you add/remove a member field, remember to update these
//  MEMBER_FIELD_SECTION_CHANGE BEGIN

void swap(Character& first, Character& second) noexcept
{
	using std::swap;
	//Static cast, because no check is needed and it's faster
	swap(static_cast<SceneryObject&>(first), static_cast<SceneryObject&>(second));
	swap(first.defaultVoiceName_, second.defaultVoiceName_);
	swap(first.defaultVoice_,     second.defaultVoice_);
}

Character::Character(const QString& name, const QString& assetImageName, bool bMirrored, const QPoint pos, const QSizeF scale, double rotationDegree, const QVarLengthArray<double, 4>& colorMultiplier, double alphaMultiplier, bool bVisible, const QString& defaultVoiceName, AssetImage* assetImage, Voice* defaultVoice)
	: SceneryObject(name, assetImageName, bMirrored, pos, scale, rotationDegree, colorMultiplier, alphaMultiplier, bVisible, assetImage),
	defaultVoiceName_(defaultVoiceName),
	defaultVoice_(defaultVoice)
{
	//if (!defaultVoiceName_.isEmpty())
	//defaultVoice_ = Novel::getInstance().getVoice(defaultVoiceName);
	errorCheck(true);
}

//defaulted
//Character::Character(const Character& obj) noexcept
//	: SceneryObject(obj.name, obj.assetImageName_, obj.bMirrored, obj.pos, obj.scale, obj.rotationDegree, obj.colorMultiplier, obj.alphaMultiplier, obj.bVisible, obj.assetImage_),
//	defaultVoiceName_(obj.defaultVoiceName_),
//	defaultVoice_(obj.defaultVoice_)
//{
//}

bool Character::operator==(const Character& obj) const noexcept
{
	if (this == &obj) return true;

	return	SceneryObject::operator==(obj)             &&
			defaultVoiceName_ == obj.defaultVoiceName_; //&&
			//defaultVoice_     == defaultVoice_;
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
	if (!defaultVoiceName_.isEmpty())  {defaultVoice_ = Novel::getInstance().getVoice(defaultVoiceName_);}

	errorCheck();
}

//  MEMBER_FIELD_SECTION_CHANGE END

//defaulted
//Character::Character(Character&& obj) noexcept
//	: Character()
//{
//	swap(*this, obj);
//}

//defaulted
//Character& Character::operator=(Character obj) noexcept
//{
//	if (this == &obj) return *this;
//
//	swap(*this, obj);
//
//	return *this;
//}

QString Character::getDefaultVoiceName() const noexcept
{
	return defaultVoiceName_;
}

const Voice* Character::getDefaultVoice() const noexcept
{
	return defaultVoice_;
}

Voice* Character::getDefaultVoice() noexcept
{
	return defaultVoice_; 
}

void Character::setDefaultVoice(const QString& defaultVoiceName, Voice* defaultVoice) noexcept
{
	if (defaultVoice)
	{
		if (defaultVoice->name != defaultVoiceName)
		{
			qCritical() << NovelLib::ErrorType::VoiceInvalid << "Voice's name missmatch (defaultVoiceName=\"" + defaultVoiceName + "\", defaultVoice->name=\"" + defaultVoice->name + "\")";
			return;
		}
	}
	else defaultVoice = Novel::getInstance().getVoice(defaultVoiceName);

	if (!defaultVoice)
	{
		qCritical() << NovelLib::ErrorType::VoiceMissing << "Voice \"" + defaultVoiceName + "\" does not exist";
		return;
	}
	defaultVoiceName_ = defaultVoiceName;
	defaultVoice_     = defaultVoice;
	errorCheck(true);
}