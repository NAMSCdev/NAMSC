#include "Novel/Action/Visual/ActionCharacterSetVoice.h"

#include "Novel/Data/Novel.h"
#include "Novel/Data/Scene.h"

ActionCharacterSetVoice::ActionCharacterSetVoice(Event* const parentEvent) noexcept
	: ActionCharacter(parentEvent)
{
}

//If you add/remove a member field, remember to update these
//  MEMBER_FIELD_SECTION_CHANGE BEGIN

void swap(ActionCharacterSetVoice& first, ActionCharacterSetVoice& second) noexcept
{
	using std::swap;
	//Static cast, because no check is needed and it's faster
	swap(static_cast<ActionCharacter&>(first), static_cast<ActionCharacter&>(second));
	swap(first.voiceName_, second.voiceName_);
	swap(first.voice_,     second.voice_);
	swap(first.onRun_,     second.onRun_);
}

ActionCharacterSetVoice::ActionCharacterSetVoice(Event* const parentEvent, const QString& characterName, const QString& voiceName, Character* character, Voice* voice)
	: ActionCharacter(parentEvent, characterName, character), 
	voiceName_(voiceName), 
	voice_(voice)
{
	if (!voice_)
		voice_ = Novel::getInstance().getVoice(voiceName_);
	errorCheck(true);
}

//deleted
//ActionCharacterSetVoice::ActionCharacterSetVoice(const ActionCharacterSetVoice& obj) noexcept
//	: ActionCharacter(obj.parentEvent, obj.characterName_, obj.character_),
//	voiceName_(obj.voiceName_),
//	voice_(obj.voice_), 
//	onRun_(obj.onRun_)
//{
//}

//deleted
//bool ActionCharacterSetVoice::operator==(const ActionCharacterSetVoice& obj) const noexcept
//{
//	if (this == &obj) return true;
//
//	return ActionCharacter::operator==(obj) &&
//		   voiceName_ == obj.voiceName_;//     &&
//		   //voice_     == obj.voice_;
//}

void ActionCharacterSetVoice::setOnRunListener(std::function<void(const Event* const parentEvent, const Character* const character, const Voice* const voice)> onRun) noexcept
{
	onRun_ = onRun;
}

void ActionCharacterSetVoice::serializableLoad(QDataStream& dataStream)
{
	ActionCharacter::serializableLoad(dataStream);
	dataStream >> voiceName_;

	voice_ = Novel::getInstance().getVoice(voiceName_);
	errorCheck();
}

void ActionCharacterSetVoice::serializableSave(QDataStream& dataStream) const
{
	ActionCharacter::serializableSave(dataStream);
	dataStream << voiceName_;
}

//  MEMBER_FIELD_SECTION_CHANGE END

ActionCharacterSetVoice::ActionCharacterSetVoice(ActionCharacterSetVoice&& obj) noexcept
	: ActionCharacter(obj.parentEvent)
{
	swap(*this, obj);
}

//deleted
//ActionCharacterSetVoice& ActionCharacterSetVoice::operator=(ActionCharacterSetVoice obj) noexcept
//{
//	if (this == &obj) return *this;
//
//	swap(*this, obj);
//
//	return *this;
//}

void ActionCharacterSetVoice::acceptVisitor(ActionVisitor* visitor)
{
	visitor->visitActionCharacterSetVoice(this);
}

QString ActionCharacterSetVoice::getVoiceName() const noexcept
{
	return voiceName_;
}

const Voice* ActionCharacterSetVoice::getVoice() const noexcept
{
	return voice_;
}

Voice* ActionCharacterSetVoice::getVoice() noexcept 
{ 
	return voice_; 
}

void ActionCharacterSetVoice::setVoice(const QString& voiceName, Voice* voice) noexcept
{
	if (voice)
	{
		if (voice->name != voiceName)
		{
			qCritical() << NovelLib::ErrorType::VoiceInvalid << "Voice's name missmatch (voiceName=\"" + voiceName + "\", voice->name=\"" + voice->name + "\")";
			return;
		}
	}
	else voice = Novel::getInstance().getVoice(voiceName);
	
	if (!voice)
	{
		qCritical() << NovelLib::ErrorType::VoiceMissing << "Voice \"" + voiceName + "\" does not exist";
		return;
	}
	voiceName_ = voiceName;
	voice_     = voice;
	errorCheck(true);
}

NovelLib::SerializationID ActionCharacterSetVoice::getType() const noexcept 
{ 
	return NovelLib::SerializationID::ActionSetBackground; 
}