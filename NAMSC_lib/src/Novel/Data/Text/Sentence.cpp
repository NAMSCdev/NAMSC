#include "Novel/Data/Text/Sentence.h"

#include "Novel/Data/Novel.h"
#include "Novel/Data/Scene.h"

Sentence::Sentence(Event* const parentEvent, Scene* const parentScene) noexcept
	: parentEvent_(parentEvent), parentScene_(parentScene)
{
}

Sentence::Sentence(Event* const parentEvent, Scene* const parentScene, const Translation& text, const QString& displayedName, const QString& characterName, const QString& voiceName, const QString& assetImageName, double cpsMultiplier, uint cpsOverwrite, bool bEndWithInput, uint waitBeforeContinueTime)
	: parentEvent_(parentEvent), parentScene_(parentScene), text(text), displayedName(displayedName), characterName(characterName), voiceName_(voiceName), assetImageName_(assetImageName), cpsMultiplier(cpsMultiplier), cpsOverwrite(cpsOverwrite), bEndWithInput(bEndWithInput), waitBeforeContinueTime(waitBeforeContinueTime)
{
}

Sentence& Sentence::operator=(Sentence obj) noexcept
{
	if (this == &obj) return *this;

	std::swap(this->text,                   obj.text);
	std::swap(this->displayedName,          obj.displayedName);
	std::swap(this->characterName,          obj.characterName);
	std::swap(this->assetImageName_,        obj.assetImageName_);
	std::swap(this->assetImage_,            obj.assetImage_);
	std::swap(this->voiceName_,             obj.voiceName_);
	std::swap(this->voice_,                 obj.voice_);
	std::swap(this->cpsMultiplier,          obj.cpsMultiplier);
	std::swap(this->cpsOverwrite,           obj.cpsOverwrite);
	std::swap(this->bEndWithInput,          obj.bEndWithInput);
	std::swap(this->waitBeforeContinueTime, obj.waitBeforeContinueTime);

	return *this;
}

bool Sentence::operator==(const Sentence& obj) const noexcept
{
	if (this == &obj) return true;

	return	text                   == obj.text                  &&
			displayedName          == obj.displayedName         &&
			characterName          == obj.characterName         &&
			assetImageName_        == obj.assetImageName_       &&
			voiceName_             == obj.voiceName_	        &&
			cpsMultiplier          == obj.cpsMultiplier         &&
			cpsOverwrite           == obj.cpsOverwrite	        &&
			bEndWithInput          == obj.bEndWithInput	        &&
			waitBeforeContinueTime == obj.waitBeforeContinueTime;
}

bool Sentence::checkForErrors(bool bComprehensive) const
{
	bool bError = false;
	static auto errorChecker = [&](bool bComprehensive)
	{
		if (assetImage_ == nullptr)
		{
			bError = true;
			qCritical() << this << NovelLib::ErrorType::AssetImageInvalid << "No valid Sprite AssetImage assigned. Was it deleted and not replaced?";
			if (assetImageName_ == "")
				qCritical() << this << NovelLib::ErrorType::AssetImageMissing << "Sprite AssetImage \"" << assetImageName_ << "\" does not exist. Definition file might be corrupted";
		}
		if (parentScene_->scenery.getDisplayedCharacter(characterName) == nullptr)
		{
			bError = true;
			qCritical() << this << NovelLib::ErrorType::CharacterInvalid << "No valid Character assigned. Was it deleted and not replaced?";
			if (characterName != "")
				qCritical() << this << NovelLib::ErrorType::CharacterMissing << "Character \"" << characterName << "\" does not exist. Definition file might be corrupted";
		}
		if (voice_ == nullptr)
		{
			bError = true;
			qCritical() << this << NovelLib::ErrorType::VoiceInvalid << "No valid Voice assigned. Was it deleted and not replaced?";
			if (voiceName_ != "")
				qCritical() << this << NovelLib::ErrorType::VoiceMissing << "Voice \"" << voiceName_ << "\" does not exist. Definition file might be corrupted";
		}
	};

	if (NovelLib::catchExceptions(errorChecker, bComprehensive) || text.checkForErrors(bComprehensive))
		qDebug() << "An Error occurred in Sentence::checkForErrors of Scene \"" << parentScene_->name << "\" Event " << parentEvent_->getIndex();

	return bError;
}

void Sentence::setAssetImage(const QString& assetImageName) noexcept
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

AssetImage* Sentence::getAssetImage() noexcept
{ 
	return assetImage_; 
}

const AssetImage* Sentence::getAssetImage() const noexcept
{ 
	return assetImage_; 
}

QString Sentence::getAssetImageName() const noexcept
{
	return assetImageName_; 
}

void Sentence::setVoice(const QString& voiceName) noexcept
{
	Voice* newVoice = nullptr;
	newVoice = Novel::getInstance().getVoice(voiceName);
	if (newVoice == nullptr)
		qCritical() << this << NovelLib::ErrorType::VoiceMissing << "Voice \"" << voiceName << "\" does not exist";
	else
	{
		voiceName_ = voiceName;
		voice_     = newVoice;
		checkForErrors(true);
	}
}

Voice* Sentence::getVoice() noexcept
{
	return voice_;
}

const Voice* Sentence::getVoice() const noexcept
{
	return voice_; 
}

QString Sentence::getVoiceName() const noexcept
{ 
	return voiceName_;
}

void Sentence::serializableLoad(QDataStream& dataStream)
{
	dataStream >> text >> displayedName >> characterName >> assetImageName_ >> voiceName_ >> cpsMultiplier >> cpsOverwrite >> bEndWithInput >> waitBeforeContinueTime;

	voice_ = Novel::getInstance().getVoice(voiceName_);
}

void Sentence::serializableSave(QDataStream& dataStream) const
{
	dataStream << text << displayedName << characterName << voiceName_ << assetImageName_ << cpsMultiplier << cpsOverwrite << bEndWithInput << waitBeforeContinueTime;
}