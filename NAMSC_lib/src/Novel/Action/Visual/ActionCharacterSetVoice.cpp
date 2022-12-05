#include "Novel/Action/Visual/ActionCharacterSetVoice.h"

#include "Novel/Data/Novel.h"
#include "Novel/Data/Scene.h"

ActionCharacterSetVoice::ActionCharacterSetVoice(Event* const parentEvent, Scene* const parentScene) noexcept
	: ActionCharacter(parentEvent, parentScene)
{
}

ActionCharacterSetVoice::ActionCharacterSetVoice(Event* const parentEvent, Scene* const parentScene, const QString& characterName, const QString& voiceName)
	: ActionCharacter(parentEvent, parentScene, characterName), voiceName_(voiceName)
{
	voice_ = Novel::getInstance().getVoice(voiceName_);
	//if (voice_ == nullptr)
	//	qCritical() << this << NovelLib::ErrorType::VoiceMissing << "Voice \"" << voiceName_ << "\" does not exist. Definition file might be corrupted";
	checkForErrors(true);
}

ActionCharacterSetVoice& ActionCharacterSetVoice::operator=(const ActionCharacterSetVoice& obj) noexcept
{
	if (this == &obj) return *this;

	ActionCharacter::operator=(obj);
	//onRun_     = obj.onRun_;
	voiceName_ = obj.voiceName_;
	voice_     = obj.voice_;

	return *this;
}

bool ActionCharacterSetVoice::operator==(const ActionCharacterSetVoice& obj) const noexcept
{
	if (this == &obj) return true;

	return	ActionCharacter::operator==(obj) &&
			voiceName_ == obj.voiceName_;//     &&
			//voice_     == obj.voice_;
}

bool ActionCharacterSetVoice::checkForErrors(bool bComprehensive) const
{
	bool bError = ActionCharacter::checkForErrors(bComprehensive);

	static auto errorChecker = [&](bool bComprehensive)
	{
		if (voice_ == nullptr)
		{
			bError = true;
			qCritical() << this << NovelLib::ErrorType::VoiceInvalid << "No valid Voice assigned. Was it deleted and not replaced?";
			if (voiceName_ != "")
				qCritical() << this << NovelLib::ErrorType::VoiceMissing << "Voice \"" << voiceName_ << "\" does not exist. Definition file might be corrupted";
		}
	};

	bError |= NovelLib::catchExceptions(errorChecker, bComprehensive); 
	if (bError)
		qDebug() << "Error occurred in ActionCharacterSetVoice::checkForErrors of Scene \"" << parentScene_->name << "\" Event " << parentEvent_->getIndex();
	
	return bError;
}

void ActionCharacterSetVoice::run()
{
	ActionCharacter::run();

	character_->setDefaultVoice(voiceName_);

	if (onRun_)
		onRun_(parentEvent_, parentScene_, character_, voice_);
}

void ActionCharacterSetVoice::setOnRunListener(std::function<void(Event* const parentEvent, Scene* const parentScene, Character* character, Voice* voice)> onRun) noexcept
{
	onRun_ = onRun;
}

void ActionCharacterSetVoice::acceptVisitor(ActionVisitor* visitor)
{
	visitor->visitActionCharacterSetVoice(this);
}

const Voice* ActionCharacterSetVoice::getVoice() const noexcept
{
	return voice_;
}

Voice* ActionCharacterSetVoice::getVoice() noexcept 
{ 
	return voice_; 
}

QString ActionCharacterSetVoice::getVoiceName() const noexcept 
{
	return voiceName_;
}

void ActionCharacterSetVoice::setVoice(const QString& voiceName) noexcept
{
	Voice* newVoice = nullptr;
	newVoice = Novel::getInstance().getVoice(voiceName);
	if (newVoice == nullptr)
		qCritical() << this << NovelLib::ErrorType::VoiceMissing << "Voice \"" << voiceName << "\" does not exist";
	else
	{
		voiceName_ = voiceName;
		voice_ = newVoice;
		checkForErrors(true);
	}
}

NovelLib::SerializationID ActionCharacterSetVoice::getType() const noexcept 
{ 
	return NovelLib::SerializationID::ActionSetBackground; 
}

void ActionCharacterSetVoice::serializableLoad(QDataStream& dataStream)
{
	ActionCharacter::serializableLoad(dataStream);
	dataStream >> voiceName_;

	voice_ = Novel::getInstance().getVoice(voiceName_);
	//if (voice_ == nullptr)
	//	qCritical() << this << NovelLib::ErrorType::VoiceMissing << "Voice \"" << voiceName_ << "\" does not exist. Definition file might be corrupted";
	checkForErrors();
}

void ActionCharacterSetVoice::serializableSave(QDataStream& dataStream) const
{
	ActionCharacter::serializableSave(dataStream);
	dataStream << voiceName_;
}