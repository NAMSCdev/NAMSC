#include "Novel/Action/Audio/ActionAudioSetSounds.h"

#include "Novel/Data/Scene.h"

ActionAudioSetSounds::ActionAudioSetSounds(Event* const parentEvent) noexcept
	: ActionAudio(parentEvent)
{
}

//If you add/remove a member field, remember to update these
//  MEMBER_FIELD_SECTION_CHANGE BEGIN

void swap(ActionAudioSetSounds& first, ActionAudioSetSounds& second) noexcept
{
	using std::swap;
	//Static cast, because no check is needed and it's faster
	swap(dynamic_cast<ActionAudio&>(first), dynamic_cast<ActionAudio&>(second));
	swap(first.sounds, second.sounds);
	swap(first.onRun_, second.onRun_);
}

ActionAudioSetSounds::ActionAudioSetSounds(Event* const parentEvent, const AudioSettings& audioSettings, const std::unordered_map<QString, Sound>& sounds)
	: ActionAudio(parentEvent, audioSettings),
	sounds(sounds)
{
	errorCheck(true);
}

//deleted
//ActionAudioSetSounds::ActionAudioSetSounds(const ActionAudioSetSounds& obj) noexcept
//	: ActionAudio(obj.parentEvent, obj.audioSettings_), 
//	sounds(obj.sounds), 
//	onRun_(obj.onRun_)
//{
//}

//deleted
//bool ActionAudioSetSounds::operator==(const ActionAudioSetSounds& obj) const noexcept
//{
//	if (this == &obj) return true;
//
//	return ActionAudio::operator==(obj) &&
//		   sounds == obj.sounds;
//}

//deleted
//void ActionAudioSetSounds::setOnRunListener(std::function<void(const Event* const parentEvent, const std::unordered_map<QString, Sound>* const sounds)> onRun) noexcept
//{
//	onRun_ = onRun;
//}

void ActionAudioSetSounds::serializableLoad(QDataStream& dataStream)
{
	ActionAudio::serializableLoad(dataStream);
	uint soundsSize;
	dataStream >> soundsSize;
	for (uint i = 0; i != soundsSize; ++i)
	{
		Sound sound;
		dataStream >> sound;
		sounds.emplace(sound.name, std::move(sound));
	}
	errorCheck();
}

void ActionAudioSetSounds::serializableSave(QDataStream& dataStream) const
{
	ActionAudio::serializableSave(dataStream);
	dataStream << sounds.size();
	for (const std::pair<const QString, Sound>& sound : sounds)
		dataStream << sound.second;
}

//  MEMBER_FIELD_SECTION_CHANGE END

ActionAudioSetSounds::ActionAudioSetSounds(ActionAudioSetSounds&& obj) noexcept
	: ActionAudio(obj.parentEvent)
{
	swap(*this, obj);
}

//deleted
//ActionAudioSetSounds& ActionAudioSetSounds::operator=(ActionAudioSetSounds obj) noexcept
//{
//	if (this == &obj) return *this;
//
//	swap(*this, obj);
//
//	return *this;
//}

void ActionAudioSetSounds::acceptVisitor(ActionVisitor* visitor)
{
	visitor->visitActionAudioSetSounds(this);
}

NovelLib::SerializationID ActionAudioSetSounds::getType() const noexcept
{
	return NovelLib::SerializationID::ActionAudioSetSounds;
}